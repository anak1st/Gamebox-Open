#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Data.hpp"

namespace mines {

constexpr int size = 32, bound = 10;
constexpr int board = 80;

class Render : public Data, public sf::Drawable, public sf::Transformable {
private:
    sf::Texture cellsTexture;
    mutable sf::Sprite cells;
    sf::Font font;
    sf::Text title, mineNum, status;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cells.setTextureRect(sf::IntRect(vis[i][j] * size, 0, size, size));
                cells.setPosition(j * size, i * size);
                cells.move(bound, bound + board);
                target.draw(cells, states);
            }
        }
        target.draw(title);
        target.draw(mineNum);
        target.draw(status);
    }

public:
    using Data::Data;

    void load_assetss(const std::string &cellsPath, const std::string &fontPath) {
        if (!cellsTexture.loadFromFile(cellsPath) || !font.loadFromFile(fontPath)) {
            std::cerr << "[gamebox] {mines} (error) asset load failed!";
        }
        cells.setTexture(cellsTexture);

        title.setString("Minesweeper");
        title.setFont(font);
        title.setCharacterSize(24);
        title.setFillColor(sf::Color::Black);
        title.setStyle(sf::Text::Bold | sf::Text::Italic);
        title.move(20, 20);

        mineNum.setString("Mine num: " + std::to_string(num));
        mineNum.setFont(font);
        mineNum.setCharacterSize(24);
        mineNum.setFillColor(sf::Color::Black);
        mineNum.setStyle(sf::Text::Bold);
        mineNum.move(20, 50);

        status.setString(" ");
        status.setFont(font);
        status.setCharacterSize(24);
        status.setFillColor(sf::Color::Red);
        status.setStyle(sf::Text::Bold);
        status.move(200, 20);
    }

    void click(std::pair<int, int> p) {
        int res = change(p);
        if (res == 1) {
            status.setString("You Win!\nPress R to restart");
            std::cerr << "[gamebox] {mines} win\n";
            end();
        }
        if (res == 2) {
            status.setString("You Lose!\nPress R to Restart");
            std::cerr << "[gamebox] {mines} lose\n";
            end();
        }
    }

    void restart() {
        status.setString(" ");
        clear();
        std::cerr << "[gamebox] {mines} restart\n";
    }
};

}  // namespace mines
