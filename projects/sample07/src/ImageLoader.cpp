#include "ImageLoader.h"

#include <FreeImage.h>
#include <spdlog/spdlog.h>

class FreeImageTGAImpl final : public Image {
public:
    FreeImageTGAImpl(FIBITMAP &_resource)
        : m_resource(_resource), m_width(FreeImage_GetWidth(&m_resource)), m_height(FreeImage_GetHeight(&m_resource))
    {
    }

    ~FreeImageTGAImpl()
    {
        FreeImage_Unload(&m_resource);
    }

private:
    virtual uint32_t getWidth() const override final
    {
        return m_width;
    }

    virtual uint32_t getHeight() const override final
    {
        return m_height;
    }

    virtual bool getColorAt(uint32_t _x, uint32_t _y, uint8_t &_r, uint8_t &_g, uint8_t &_b, uint8_t &_a) const override final
    {
        const RGBQUAD *color{at(_x, _y)};
        if (!color) {
            spdlog::warn("Could not get pixel at ({}, {})", _x, _y);
            return false;
        }

        _r = color->rgbRed;
        _g = color->rgbGreen;
        _b = color->rgbBlue;
        _a = color->rgbReserved;

        return true;
    }

    virtual bool setColorAt(uint32_t _x, uint32_t _y, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) override final
    {
        RGBQUAD *color{at(_x, _y)};
        if (!color) {
            spdlog::warn("Could not get pixel at ({}, {})", _x, _y);
            return false;
        }

        color->rgbRed = _r;
        color->rgbGreen = _g;
        color->rgbBlue = _b;
        color->rgbReserved = _a;

        return true;
    }

    virtual std::unique_ptr<Image> merge(const Image &_other) const override final
    {
        if (m_width != _other.getWidth() || m_height != _other.getHeight()) {
            spdlog::warn("Image sizes do not match");
            return nullptr;
        }

        FIBITMAP *merged = FreeImage_Allocate(m_width, m_height, 32);
        if (!merged) {
            spdlog::warn("Could not allocate image");
            return nullptr;
        }

        std::unique_ptr<Image> mergedImage{std::make_unique<FreeImageTGAImpl>(*merged)};

        RGBQUAD color, otherColor;
        for (unsigned int y = 0; y < m_height; ++y) {
            for (unsigned int x = 0; x < m_width; ++x) {
                if (!getColorAt(x, y, color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved))
                    return nullptr;

                if (!_other.getColorAt(x, y, otherColor.rgbRed, otherColor.rgbGreen, otherColor.rgbBlue, otherColor.rgbReserved))
                    return nullptr;

                if (color.rgbReserved == 0)
                    color = otherColor;

                if (!mergedImage->setColorAt(x, y, color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved))
                    return nullptr;
            }
        }

        return mergedImage;
    }

    virtual bool save(const std::filesystem::path &_filepath) const override final
    {
        return FreeImage_Save(FIF_TARGA, &m_resource, _filepath.string().c_str());
    }

    RGBQUAD *at_impl(uint32_t _x, uint32_t _y) const
    {
        RGBQUAD *pixels{reinterpret_cast<RGBQUAD *>(FreeImage_GetBits(&m_resource))};
        if (!pixels || _x >= m_width || _y >= m_height)
            return nullptr;
        return pixels + ((m_height - (_y + 1)) * m_width + _x);
    }

    const RGBQUAD *at(uint32_t _x, uint32_t _y) const { return at_impl(_x, _y); }
    RGBQUAD *at(uint32_t _x, uint32_t _y) { return at_impl(_x, _y); }

    FIBITMAP &m_resource;
    uint32_t m_width, m_height;
};

class FreeImageLoaderImpl : public ImageLoader {
public:
    FreeImageLoaderImpl()
    {
        FreeImage_Initialise();
    }

    ~FreeImageLoaderImpl()
    {
        FreeImage_DeInitialise();
    }

private:
    std::unique_ptr<Image> loadTGA(const std::filesystem::path &_filename) override final
    {
        FIBITMAP *image = FreeImage_Load(FIF_TARGA, _filename.string().c_str());
        if (!image) {
            spdlog::warn("Could not load texture at {}", _filename.string());
            return nullptr;
        }

        return std::make_unique<FreeImageTGAImpl>(*image);
    }
};

ImageLoader &ImageLoader::GetInstance()
{
    static FreeImageLoaderImpl instance;
    return instance;
}

std::unique_ptr<Image> Image::merge(std::deque<std::unique_ptr<Image>> _images, std::unique_ptr<Image> _base, bool _reverse)
{
    if (_images.empty()) {
        return _base;
    }

    auto next = [&]() -> std::unique_ptr<Image> {
        if (_reverse) {
            std::unique_ptr<Image> image{std::move(_images.back())};
            _images.pop_back();
            return image;
        } else {
            std::unique_ptr<Image> image{std::move(_images.front())};
            _images.pop_front();
            return image;
        }
    };

    while (!_images.empty() && !_base) {
        _base = next();
    }

    while (!_images.empty()) {
        std::unique_ptr<Image> image{next()};
        if (!image)
            continue;

        _base = _base->merge(*image);
    }

    return _base;
}
