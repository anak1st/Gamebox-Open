#include "main.h"

int main() {
    std::cerr << "[gamebox] begin\n";

    int size_h = 400, size_w = 400;
    const float scale = 2;
    sf::RenderWindow window(sf::VideoMode(size_h, size_w), "Gamebox! by XiaFan");
    window.setSize(sf::Vector2u(size_h * scale, size_h * scale));

    const std::string backgroundPath = "assets/gamebox.png";
    const std::string fontPath = "assets/cambria.ttc";
    sf::Texture backgroundTexture;
    sf::Font font;
    if (!backgroundTexture.loadFromFile(backgroundPath) || !font.loadFromFile(fontPath)) {
        std::cerr << "[gamebox] (error) asset load failed!\n";
    }
    sf::Sprite background(backgroundTexture);

    sf::Text title, toplay, author;
    title.setFont(font);
    title.setString("Gamebox");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Magenta);
    title.setStyle(sf::Text::Bold | sf::Text::Italic);
    title.move(20, 20);

    toplay.setFont(font);
    toplay.setString("Press number to play game!");
    toplay.setCharacterSize(20);
    toplay.setFillColor(sf::Color::Green);
    toplay.setStyle(sf::Text::Bold);
    toplay.move(30, 75);

    author.setFont(font);
    author.setString("By XiaFan");
    author.setCharacterSize(20);
    author.setFillColor(sf::Color::Yellow);
    author.setStyle(sf::Text::Bold);
    author.move(270, 350);

    const int game_num = 3;
    std::vector<std::string> gamesName = {"Tetris", "Minesweeper", "2048"};
    std::vector<sf::Text> gameTitle(game_num);
    for (int i = 0; i < game_num; i++) {
        gameTitle[i].setFont(font);
        gameTitle[i].setString(std::to_string(i + 1) + " " + gamesName[i]);
        gameTitle[i].setCharacterSize(30);
        gameTitle[i].setFillColor(sf::Color::Black);
        gameTitle[i].setStyle(sf::Text::Bold);
        gameTitle[i].move(40, 110 + i * 40);
    }

    std::vector<bool> game(game_num, false);

    while (window.isOpen()) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        // int i = pos.y / scale;
        // int j = pos.x / scale;

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                case sf::Keyboard::Num1:
                    game[0] = true;
                    break;
                case sf::Keyboard::Num2:
                    game[1] = true;
                    break;
                case sf::Keyboard::Num3:
                    game[2] = true;
                    break;
                default:
                    break;
                }
            }
        }

        if (game[0]) {
            game[0] = false;
            tetris::play();
        }

        if (game[1]) {
            game[1] = false;
            mines::play();
        }

        if (game[2]) {
            game[2] = false;
            g2048::play();
        }

        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(title);
        window.draw(toplay);
        for (int i = 0; i < game_num; i++) {
            window.draw(gameTitle[i]);
        }
        window.draw(author);
        window.display();
    }
    std::cerr << "[gamebox] end";

    return 0;
}