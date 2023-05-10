#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "..\base.h"

namespace tetris {

namespace Shape {

constexpr int pos[7][4] = {
    1, 3, 5, 7,  // I
    2, 4, 5, 7,  // Z
    3, 5, 4, 6,  // S
    3, 5, 4, 7,  // T
    2, 3, 5, 7,  // L
    3, 5, 7, 6,  // J
    2, 3, 4, 5,  // O
};
constexpr int max = 7;

std::pair<int, int> get_shape(int shape, int i) {
    int num = Shape::pos[shape][i];
    return std::pair<int, int>(num % 2, num / 2);
}

}  // namespace Shape

namespace Colour {

constexpr int max = 7;

}  // namespace Colour

struct Tetromino {
    std::vector<std::pair<int, int>> pos;
    int shape;
    int colour;
    Tetromino() : pos(4), shape(0), colour(0) {}
};

class Data {
protected:
    std::vector<std::vector<int>> mat;
    Tetromino next, now, backup;
    Randomer<int> randomer_shape, randomer_colour;

    void tetromino_init(Tetromino &t) {
        t.shape = randomer_shape();
        t.colour = randomer_colour();
        for (int i = 0; i < 4; i++) {
            t.pos[i] = Shape::get_shape(t.shape, i);
        }
    }

    void next_tetromino() {
        now = next;
        for (auto &[x, y] : now.pos) {
            x++;
        }
        backup = now;
        tetromino_init(next);
    }

    bool chack_tetromino(Tetromino &t) {
        for (auto [x, y] : t.pos) {
            if (x < 0 || x >= width || y >= height) {
                return false;
            } else if (mat[y][x] != -1) {
                return false;
            }
        }
        return true;
    }

public:
    int height, width, score;

    Data(int height_, int width_)
        : height(height_),
          width(width_),
          mat(height_, std::vector<int>(width_, -1)),
          score(0),
          randomer_shape(0, Shape::max - 1),
          randomer_colour(0, Colour::max - 1) {
        tetromino_init(next);
        next_tetromino();
    }

    void clear() {
        for (auto &i : mat) {
            for (auto &j : i) {
                j = -1;
            }
        }
        score = 0;
        next_tetromino();
    }

    bool tetromino_move_x(int dx) {
        for (auto &[x, y] : now.pos) {
            x += dx;
        }
        if (chack_tetromino(now)) {
            backup.pos = now.pos;
            return true;
        } else {
            now.pos = backup.pos;
            return false;
        }
    }

    bool tetromino_move_y() {
        for (auto &[x, y] : now.pos) {
            y++;
        }
        if (chack_tetromino(now)) {
            backup.pos = now.pos;
            return true;
        } else {
            for (auto &[x, y] : backup.pos) {
                mat[y][x] = backup.colour;
            }
            next_tetromino();
            return false;
        }
    }

    bool tetromino_rotate() {
        auto [px, py] = now.pos[1];  // center of rotation
        for (auto &[x, y] : now.pos) {
            int nx = y - py;
            int ny = x - px;
            x = px - nx;
            y = py + ny;
        }
        if (chack_tetromino(now)) {
            backup.pos = now.pos;
            return true;
        } else {
            now.pos = backup.pos;
            return false;
        }
    }

    bool check_lines() {
        int res = 0;
        for (int i = height - 1, k = height - 1; i >= 0; i--) {
            int count = 0;
            for (int j = 0; j < width; j++) {
                if (mat[i][j] != -1) {
                    count++;
                }
                mat[k][j] = mat[i][j];
            }
            if (count < width) {
                k--;
            } else {
                res++;
            }
        }
        if (res > 0) {
            score += res;
            return true;
        } else {
            return false;
        }
    }
};

}  // namespace tetris
