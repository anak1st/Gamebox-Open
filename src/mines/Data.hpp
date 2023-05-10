#pragma once

#include <iostream>
#include <vector>

#include "..\base.h"

namespace mines {

constexpr int Empty = 0;
constexpr int Mine = 9;
constexpr int NotShow = 10;
constexpr int Flag = 11;

class Data {
protected:
    std::vector<std::vector<int>> mat, vis;
    Randomer<int> randomer;
    int remain;

    void dfs(std::pair<int, int> p) {
        auto [i, j] = p;
        vis[i][j] = mat[i][j];
        remain--;
        if (vis[i][j] != Empty) {
            return;
        }
        int di[] = {-1, 1, 0, 0};
        int dj[] = {0, 0, -1, 1};
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d];
            int nj = j + dj[d];
            if (check({ni, nj}) && (vis[ni][nj] == NotShow || vis[ni][nj] == Flag)) {
                dfs({ni, nj});
            }
        }
    }

public:
    int height, width, num;

    Data(int height_, int width_, int num_)
        : height(height_),
          width(width_),
          mat(height_, std::vector<int>(width_, Empty)),
          vis(height_, std::vector<int>(width_, NotShow)),
          num(num_),
          randomer(0, height_ * width_ - 1) {
        rand_init();
    }

    void clear() {
        for (auto &v : mat) {
            for (auto &u : v) {
                u = Empty;
            }
        }
        for (auto &v : vis) {
            for (auto &u : v) {
                u = NotShow;
            }
        }
        rand_init();
    }

    bool check(std::pair<int, int> p) {
        auto [i, j] = p;
        return (i >= 0 && i < height && j >= 0 && j < width);
    }

    void rand_init() {
        for (int n = 1; n <= num;) {
            int h = randomer() % height;
            int w = randomer() % width;
            if (mat[h][w] == Mine) {
                continue;
            }
            mat[h][w] = Mine;
            n++;
            for (int i = h - 1; i <= h + 1; i++) {
                for (int j = w - 1; j <= w + 1; j++) {
                    if (check({i, j}) && mat[i][j] != Mine) {
                        mat[i][j]++;
                    }
                }
            }
        }
        remain = height * width;
    }

    /**
     * @brief if click on mine ?
     *
     * @return 0 -> not changw
     * @return 1 -> Win
     * @return 2 -> Lose
     */
    int change(std::pair<int, int> p) {
        if (!check(p)) {
            return 0;
        }
        auto [i, j] = p;
        if (vis[i][j] == NotShow) {
            dfs({i, j});
            std::cerr << num << " " << remain << " " << vis[i][j] << "\n";
            // Win
            if (remain == num) {
                return 1;
            }
            // Lose
            if (vis[i][j] == Mine) {
                return 2;
            }
        }
        return 0;
    }

    void flag(std::pair<int, int> p) {
        if (!check(p)) {
            return;
        }
        auto [i, j] = p;
        if (vis[i][j] == Flag) {
            vis[i][j] = NotShow;
        } else if (vis[i][j] == NotShow) {
            vis[i][j] = Flag;
        }
    }

    void end() {
        vis = mat;
        std::cerr << "[gamebox] {mines} gameover\n";
    }
};

}  // namespace mines
