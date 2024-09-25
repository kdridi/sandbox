#include "ImageLoader.h"

#include <core/envVars/envVars.h>
#include <core/pathSolver/pathSolver.h>

#include <FreeImage.h>
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

bool updateTexture(sf::Texture &_texture, const Image &_image)
{
    sf::Vector2u size{_texture.getSize()};
    if (size.x != _image.getWidth() || size.y != _image.getHeight()) {
        spdlog::warn("Texture size does not match image size");
        return false;
    }

    std::vector<sf::Uint8> pixels(size.x * size.y * 4);
    sf::Color *sfColors = reinterpret_cast<sf::Color *>(pixels.data());

    for (unsigned int y = 0; y < size.y; ++y) {
        unsigned int py = y;

        for (unsigned int x = 0; x < size.x; ++x) {
            unsigned int pn = py * size.x + x;

            sf::Color &color = sfColors[pn];
            _image.getColorAt(x, y, color.r, color.g, color.b, color.a);
        }
    }

    _texture.update(pixels.data());

    return true;
}

std::unique_ptr<sf::Texture> createTexture(const Image &_image)
{
    std::unique_ptr<sf::Texture> texture{new sf::Texture()};
    if (!texture->create(_image.getWidth(), _image.getHeight())) {
        spdlog::warn("Could not create texture");
        return nullptr;
    }

    if (!updateTexture(*texture, _image)) {
        spdlog::warn("Could not update texture");
        return nullptr;
    }

    return texture;
}

std::unique_ptr<Image> getImage()
{
    const std::filesystem::path texturePath = PATH_SOLVER_SOLVE("assets/image_800x600.tga");
    spdlog::info("Loading texture from {}", texturePath.string());

    std::unique_ptr<Image> image{IMAGE_LOAD_TGA(texturePath)};
    return image;
}

std::unique_ptr<Image> getMergedImage()
{
    std::deque<std::unique_ptr<Image>> images;
    for (uint32_t i = 0;; ++i) {
        std::filesystem::path path{PATH_SOLVER_SOLVE("assets/layer_800x600_{:02}.tga", i + 1)};
        std::unique_ptr<Image> image{IMAGE_LOAD_TGA(path.string())};
        if (!image)
            break;
        images.push_back(std::move(image));
    }
    return Image::merge(std::move(images));
}

int main(int argc, const char *argv[], const char *env[])
{
    MODULES_START(argc, argv, env);

    auto home{ENV_VARS_GET("HOME")};
    if (!home) {
        spdlog::warn("HOME not set");
        return EXIT_FAILURE;
    }

    std::filesystem::path homePath = std::filesystem::absolute(*home);
    spdlog::info("HOME: \"{}\"", homePath.string());

    std::filesystem::path projectPath{homePath / ".config" / NAMESPACE / PROJECT_NAME};
    spdlog::info("projectPath: \"{}\"", projectPath.string());

    if (!std::filesystem::exists(projectPath)) {
        spdlog::info("Creating project path");
        std::filesystem::create_directories(projectPath);
    }

    // create the texture from the level definition
    // FREE_IMAGE_DUMP_TGA(PATH_SOLVER_SOLVE("assets/palette.tga"));

    std::unique_ptr<Image> image{getMergedImage()};
    if (!image)
        return EXIT_FAILURE;

    if (!image->save(projectPath / "merged.tga"))
        return EXIT_FAILURE;

    std::unique_ptr<sf::Texture> texture{createTexture(*image)};

    sf::Sprite sprite{*texture};
    sf::Vector2u size{texture->getSize()};

    // create the window
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Texture");

    // run the main loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                spdlog::info("Window closed");
                window.close();
            }
        }

        // draw the map
        window.clear(sf::Color::Yellow);
        window.draw(sprite);
        window.display();
    }

    spdlog::info("Application ended");

    return EXIT_SUCCESS;
}
