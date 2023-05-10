#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

#include "Render.hpp"

namespace mines {

int play() {
    std::cerr << "[gamebox] {mines} begin\n";
    // game date
    int height = 12, width = 20, num = 40;
    // render data
    const int size_h = bound * 2 + height * size + board;
    const int size_w = bound * 2 + width * size;
    const int scale = 2;

    sf::RenderWindow window(sf::VideoMode(size_w, size_h), "Minesweeper!");
    window.setSize(sf::Vector2u(size_w * scale, size_h * scale));

    Render Mines(height, width, num);
    const std::string cellsPath = "assets/mines/cells.jpg";
    const std::string fontPath = "assets/cambria.ttc";

    Mines.load_assetss(cellsPath, fontPath);

    while (window.isOpen()) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int i = (pos.y / scale - bound - board) / size;
        int j = (pos.x / scale - bound) / size;

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::MouseButtonPressed && Mines.check({i, j})) {
                std::cerr << "[gamebox] {mines} click on: ";
                switch (e.key.code) {
                case sf::Mouse::Left:
                    Mines.click({i, j});
                    break;
                case sf::Mouse::Right:
                    Mines.flag({i, j});
                    break;
                default:
                    break;
                }
            }
            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                case sf::Keyboard::E:
                case sf::Keyboard::Q:
                    Mines.end();
                    break;
                case sf::Keyboard::R:
                    Mines.restart();
                default:
                    break;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(Mines);
        window.display();
    }

    std::cerr << "[gamebox] {mines} end\n";
    return 0;
}

}  // namespace mines
