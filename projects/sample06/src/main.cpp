#include "Level.h"
#include "ParticleSystem.h"
#include "TileMap.h"

#include <core/pathSolver/pathSolver.h>

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

int main(int argc, const char *argv[], const char *envp[])
{
    MODULES_START(argc, argv, envp);

    // create the window
    sf::RenderWindow window(sf::VideoMode(16 * 64, 8 * 64), "Tilemap");

    // create the tilemap from the level definition
    const std::filesystem::path tileMapPath = PATH_SOLVER_SOLVE("assets/textures/icons.png");

    TileMap map;
    if (!map.load(tileMapPath.string(), sf::Vector2u(64, 64), level, 16, 8)) {
        spdlog::warn("Error while loading the tilemap at '{}'", tileMapPath.string());
        return EXIT_FAILURE;
    }

    // create the particle system
    ParticleSystem particles(1000);

    // create a clock to track the elapsed time
    sf::Clock clock;

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

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        // draw the map
        window.clear();
        window.draw(map);
        window.draw(particles);
        window.display();
    }

    spdlog::info("Application ended");

    return EXIT_SUCCESS;
}
