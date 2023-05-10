#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Data.hpp"

namespace g2048 {

constexpr int size = 100, bound = 10, board = 60;

class Render : public Data, public sf::Drawable, sf::Transformable {
private:
    sf::Font font;
    sf::Text title;
    mutable sf::Text number;

    sf::Texture cellsTexture;
    mutable sf::Sprite cells;

    int get_colour(int x) const {
        if (x >= 2048) {
            return 6;
        } else if (x >= 1024) {
            return 5;
        } else if (x >= 256) {
            return 4;
        } else if (x >= 64) {
            return 3;
        } else if (x >= 16) {
            return 2;
        } else if (x >= 2) {
            return 1;
        }
        return 0;
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cells.setTextureRect(
                    sf::IntRect(get_colour(mat[i][j]) * size, 0, size, size));
                cells.setPosition(j * size, i * size);
                cells.move(bound, board + bound);
                target.draw(cells, states);
                std::string s = std::to_string(mat[i][j]);
                if (mat[i][j] == 0) {
                    s = " ";
                }
                number.setString(s);
                number.setPosition(j * size, i * size);
                number.move(bound + 50 - s.size() * 9, board + bound + 30);
                target.draw(number, states);
            }
        }
        target.draw(title, states);
    }

public:
    using Data::Data;

    void load_assetss(const std::string &cellsPath, const std::string &fontPath) {
        if (!cellsTexture.loadFromFile(cellsPath) || !font.loadFromFile(fontPath)) {
            std::cerr << "[Gamebox] {2048} (error) asset load failed!\n";
        }
        cells.setTexture(cellsTexture);

        title.setString("2048");
        title.setFont(font);
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Black);
        title.setStyle(sf::Text::Bold | sf::Text::Italic);
        title.move(20, 20);

        number.setFont(font);
        number.setCharacterSize(28);
        number.setFillColor(sf::Color::White);
        number.setStyle(sf::Text::Bold);
    }
};

}  // namespace g2048
