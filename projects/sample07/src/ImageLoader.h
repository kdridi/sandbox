#pragma once

#include <cstdint>
#include <deque>
#include <filesystem>
#include <memory>
#include <string>

class Image {
public:
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    virtual bool getColorAt(uint32_t _x, uint32_t _y, uint8_t &_r, uint8_t &_g, uint8_t &_b, uint8_t &_a) const = 0;
    virtual bool setColorAt(uint32_t _x, uint32_t _y, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) = 0;

public:
    virtual std::unique_ptr<Image> merge(const Image &_other) const = 0;
    virtual bool save(const std::filesystem::path &_filepath) const = 0;

public:
    static std::unique_ptr<Image> merge(std::deque<std::unique_ptr<Image>> _images, std::unique_ptr<Image> _base = nullptr, bool _reverse = false);
};

class ImageLoader {
public:
    static ImageLoader &GetInstance();

    virtual std::unique_ptr<Image> loadTGA(const std::filesystem::path &_filename) = 0;
};

#define IMAGE_LOAD_TGA(_filename) ImageLoader::GetInstance().loadTGA(_filename)
#define IMAGE_DUMP_TGA(_filename) IMAGE_LOAD_TGA(_filename)->dumpPixels()