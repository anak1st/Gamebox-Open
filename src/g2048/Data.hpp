#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "..\base.h"

namespace g2048 {

std::string title2048 = R"(   
   /\\\\\\\\\\         /\\\\\\\\               /\\\         /\\\\\\\\\\
  /\\\///////\\\      /\\\/////\\\            /\\\\\       /\\\///////\\\
  \///      \//\\\    /\\\    \//\\\         /\\\/\\\      \/\\\     \/\\\
             /\\\/    \/\\\     \/\\\       /\\\/\/\\\      \///\\\\\\\\\/
           /\\\//      \/\\\     \/\\\     /\\\/  \/\\\       /\\\///////\\\
         /\\\//         \/\\\     \/\\\   /\\\\\\\\\\\\\\\\   /\\\      \//\\\
        /\\\/            \//\\\    /\\\   \///////////\\\//   \//\\\      /\\\
       /\\\\\\\\\\\\\\\   \///\\\\\\\/              \/\\\      \///\\\\\\\\\/
       \///////////////     \\///////                \///        \\/////////
)";

class Data {
protected:
    std::vector<std::vector<int>> mat;
    Randomer<int> randomer;

public:
    int n, score;

    Data(int n_) : n(n_), mat(n_, std::vector<int>(n_)), randomer(0, n_ - 1), score(0) {
        rand_init(2);
    }

    void clear() {
        for (auto &i : mat) {
            for (auto &j : i) {
                j = 0;
            }
        }
    }

    void rand_init(int num) {
        for (int n = 0; n < num;) {
            int i = randomer();
            int j = randomer();
            if (mat[i][j] == 0) {
                mat[i][j] = 2;
                n++;
            }
        }
    }

    bool move_cells(int direction) {
        // 0 -> left
        // 1 -> right
        // 2 -> up
        // 3 -> down
        bool moved = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    int jj = j, kk = k;
                    if (direction % 2 == 1) {
                        jj = n - 1 - j;
                        kk = n - 1 - k;
                    }
                    auto first = mat[i].begin() + jj;
                    auto second = mat[i].begin() + kk;
                    if (direction >= 2) {
                        first = mat[jj].begin() + i;
                        second = mat[kk].begin() + i;
                    }
                    if (*first == 0 && *second != 0) {
                        std::swap(*first, *second);
                        moved = true;
                    }
                    if (*first != 0 && *second != 0) {
                        if (*first != *second) {
                            break;
                        }
                        *second = 0;
                        *first *= 2;
                        score = std::max(score, *first);
                        moved = true;
                    }
                }
            }
        }
        if (moved) {
            rand_init(1);
        }
        return moved;
    }
};
}  // namespace g2048
