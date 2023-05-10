#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Data.hpp"

namespace tetris {

constexpr int left_bound = 245;

class Render : public Data, public sf::Drawable, public sf::Transformable {
private:
    sf::Texture backgroundTexture, tetrominoTexture, frameTexture;
    sf::Sprite background, frame;
    mutable sf::Sprite tetromino;
    sf::Font font;
    sf::Text mainTitle, scoreTitle, scoreT;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(background, states);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (mat[i][j] == -1) continue;
                tetromino.setTextureRect(sf::IntRect(mat[i][j] * 18, 0, 18, 18));
                tetromino.setPosition(j * 18, i * 18);
                tetromino.move(28, 31);
                target.draw(tetromino, states);
            }
        }

        for (const auto &[x, y] : now.pos) {
            tetromino.setTextureRect(sf::IntRect(now.colour * 18, 0, 18, 18));
            tetromino.setPosition(x * 18, y * 18);
            tetromino.move(28, 31);
            target.draw(tetromino, states);
        }

        for (const auto &[x, y] : next.pos) {
            tetromino.setTextureRect(sf::IntRect(next.colour * 18, 0, 18, 18));
            tetromino.setPosition(x * 18, y * 18);
            tetromino.move(left_bound, 80);
            target.draw(tetromino, states);
        }

        target.draw(frame, states);
        target.draw(mainTitle, states);
        target.draw(scoreTitle, states);
        target.draw(scoreT, states);
    }

public:
    using Data::Data;

    void load_assets(const std::string &backgroundPath, const std::string &framePath,
                     const std::string &tilesPath, const std::string &fontPath) {
        if (!backgroundTexture.loadFromFile(backgroundPath) ||
            !frameTexture.loadFromFile(framePath) ||
            !tetrominoTexture.loadFromFile(tilesPath) || !font.loadFromFile(fontPath)) {
            std::cerr << "[gamebox] {tetris} (error) asset load failed!\n";
        }

        background.setTexture(backgroundTexture);
        frame.setTexture(frameTexture);
        tetromino.setTexture(tetrominoTexture);

        mainTitle.setString("Tetris");
        mainTitle.setFont(font);
        mainTitle.setCharacterSize(24);
        mainTitle.setFillColor(sf::Color::Black);
        mainTitle.setStyle(sf::Text::Bold | sf::Text::Italic);
        mainTitle.move(left_bound, 10);

        scoreTitle.setString("Score:");
        scoreTitle.setFont(font);
        scoreTitle.setCharacterSize(24);
        scoreTitle.setFillColor(sf::Color::Black);
        scoreTitle.setStyle(sf::Text::Bold);
        scoreTitle.move(left_bound, 200);

        scoreT.setString("0");
        scoreT.setFont(font);
        scoreT.setCharacterSize(24);
        scoreT.setFillColor(sf::Color::Red);
        scoreT.setStyle(sf::Text::Bold);
        scoreT.move(left_bound, 250);
    }

    void check() {
        if (check_lines()) {
            std::string s = std::to_string(score);
            scoreT.setString(s);
            std::cerr << "[gamebox] {tetris} score " << score << "\n";
        }
    }
};

}  // namespace tetris