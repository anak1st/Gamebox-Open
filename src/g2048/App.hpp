#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

#include "Render.hpp"

namespace g2048 {

int play() {
    std::cerr << "[gamebox] {2048} Begin\n";
    // game date
    int N = 4, width = 4, num = 40;
    // render data
    const int size_w = bound * 2 + N * size;
    const int size_h = size_w + board;
    const int scale = 2;

    sf::RenderWindow window(sf::VideoMode(size_w, size_h), "2048!");
    window.setSize(sf::Vector2u(size_w * scale, size_h * scale));

    Render G2048(N);
    const std::string cellsPath = "assets/g2048/cells.png";
    const std::string fontPath = "assets/cambria.ttc";
    G2048.load_assetss(cellsPath, fontPath);

    while (window.isOpen()) {
        sf::Event e;
        int d = -1;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    d = 0;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    d = 1;
                    break;
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    d = 2;
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    d = 3;
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default:
                    break;
                }
            }
        }

        if (d >= 0) {
            G2048.move_cells(d);
            d = -1;
        }

        window.clear(sf::Color::White);
        window.draw(G2048);
        window.display();
    }

    std::cerr << "[gamebox] {2048} end\n";
    return 0;
}

}  // namespace g2048
