#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Render.hpp"

namespace tetris {

int play() {
    std::cerr << "[gamebox] {tetris} begin\n";
    int size_h = 420, size_w = 320;
    const float scale = 2.5;
    sf::RenderWindow window(sf::VideoMode(size_w, size_h), "Tetris");
    window.setSize(sf::Vector2u(size_w * scale, size_h * scale));

    const std::string backgroundPath = "assets/tetris/background.png";
    const std::string framePath = "assets/tetris/frame.png";
    const std::string tetrominoPath = "assets/tetris/tetromino.png";
    const std::string fontPath = "assets/cambria.ttc";

    const int height = 20;
    const int width = 10;
    Render Tetris(height, width);
    Tetris.load_assets(backgroundPath, framePath, tetrominoPath, fontPath);

    sf::Clock clock;

    float timer = 0, delay = 0.3;
    int scoreNum = 0;
    int dx = 0;

    while (window.isOpen()) {
        // Time
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Key
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    Tetris.tetromino_rotate();
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    dx = -1;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    dx = 1;
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    delay = 0;
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default:
                    break;
                }
            }
        }

        // Move
        Tetris.tetromino_move_x(dx);
        dx = 0;
        if (timer > delay) {
            Tetris.tetromino_move_y();
            timer = 0;
        }
        delay = 0.3;
        Tetris.check();

        // Draw
        window.clear(sf::Color::White);
        window.draw(Tetris);
        window.display();
    }
    std::cerr << "[gamebox] {tetris} end\n";

    return 0;
}

}  // namespace tetris
