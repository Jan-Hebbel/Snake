#ifndef CLION_SNAKE_SNACK_H
#define CLION_SNAKE_SNACK_H

#include <random>
#include <glm/glm.hpp>

#include "grid.h"

namespace snack
{
    class Snack
    {
    public:
        glm::vec2 position{};

        Snack()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(-95, 95);
            position = glm::vec2(grid::toFloat(grid::toIntGrid(distr(gen))), grid::toFloat(grid::toIntGrid(distr(gen))));
        }
    };
}

#endif //CLION_SNAKE_SNACK_H
