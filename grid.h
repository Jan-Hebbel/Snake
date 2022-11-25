#ifndef CLION_SNAKE_GRID_H
#define CLION_SNAKE_GRID_H

#include <cmath>
#include <glm/glm.hpp>

namespace grid
{
    bool isAlmostEqual(float f1, float f2, float eps)
    {
        return abs(f1 - f2) < eps;
    }

    float toGrid(float value)
    {
        int sign = (value > 0) - (value < 0);
        float c = ceil(value * 10.0f) / 10.0f - (float)sign * 0.05f;
        float f = floor(value * 10.0f) / 10.0f - (float)sign * 0.05f;
        if (abs(c - value) <= abs(f - value))
        {
            return c;
        }
        else
        {
            return f;
        }
    }

    glm::vec3 toGridv3(glm::vec3 vec)
    {
        return {toGrid(vec.x), toGrid(vec.y), toGrid(vec.z)};
    }

    int toIntGrid(int value)
    {
        int sign = (value > 0) - (value < 0);
        int c = static_cast<int>(ceil(value / 10.0f)) * 10 - sign * 5;
        int f = static_cast<int>(floor(value / 10.0f)) * 10 - sign * 5;
        if (abs(c - value) <= abs(f - value))
        {
            return c;
        }
        else
        {
            return f;
        }
    }

    float toFloat(int value)
    {
        return static_cast<float>(value) / 100.0f;
    }

    bool isOnGrid(float coord)
    {
        return isAlmostEqual(toGrid(coord), coord, 0.005f);
    }
}


#endif //CLION_SNAKE_GRID_H
