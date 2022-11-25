#ifndef CLION_SNAKE_SNAKE_H
#define CLION_SNAKE_SNAKE_H

#include <glm/glm.hpp>
#include <vector>
#include <deque>

#include "grid.h"

namespace snake
{
    enum direction
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
    };

    /* pdi stands for position, direction, index */
    struct pdi
    {
        /* the position where the direction change took place */
        glm::vec2 pos;
        /* the new direction to move towards */
        direction dir;
        /* the index of the snake segment that needs to change direction next */
        int segment;
    };

    const unsigned int LENGTH = 1;

    class Snake
    {
    public:
        float m_speed;
        unsigned int m_length;
        std::vector<glm::vec3> m_positions;
        std::vector<direction> m_directions;
        direction m_plannedDirection{};
        std::deque<pdi> pdi_queue{};

        Snake(direction startingDirection, glm::vec2 startingPosition, float speed, unsigned int length = LENGTH)
        {
            m_speed = speed;
            m_length = length;
            m_positions.push_back(glm::vec3(startingPosition.x, -0.95f, startingPosition.y));
            m_directions.push_back(startingDirection);
        }

        void move(float deltaTime)
        {
            for (int i = 0; i < m_length; ++i)
            {
                m_positions[i] = m_positions[i] + m_speed * deltaTime * directionToVector(m_directions[i]);
            }
        }

        /* gets called once when snake is on grid */
        void changeDirections()
        {
            switch (m_directions.front())
            {
                case FORWARD:
                case BACKWARD:
                {
                    if (m_plannedDirection == LEFT || m_plannedDirection == RIGHT)
                    {
                        m_directions.front() = m_plannedDirection;
                        if (m_length > 1)
                        {
                            pdi_queue.push_back({
                                glm::vec2(
                                        grid::toGrid(m_positions.front().x),
                                        grid::toGrid(m_positions.front().z)
                                ),
                                m_plannedDirection,
                                1
                            });
                        }
                    }
                    break;
                }
                case LEFT:
                case RIGHT:
                {
                    if (m_plannedDirection == FORWARD || m_plannedDirection == BACKWARD)
                    {
                        m_directions.front() = m_plannedDirection;
                        if (m_length > 1)
                        {
                            pdi_queue.push_back({
                                glm::vec2(
                                        grid::toGrid(m_positions.front().x),
                                        grid::toGrid(m_positions.front().z)
                                ),
                                m_plannedDirection,
                                1
                            });
                        }
                    }
                    break;
                }
            }

            // snap positions to the grid
            for (unsigned int j = 1; j < m_length; ++j)
            {
                m_positions[j] = grid::toGridv3(m_positions[j]);
            }

            /* change tail directions */
            if (!pdi_queue.empty())
            {
                for (int i = 0; i < pdi_queue.size(); ++i)
                {
                    if ((pdi_queue[i].pos.x == grid::toGrid(m_positions[pdi_queue[i].segment].x))
                        && (pdi_queue[i].pos.y == grid::toGrid(m_positions[pdi_queue[i].segment].z)))
                    {
                        m_directions[pdi_queue[i].segment] = pdi_queue[i].dir;
                        pdi_queue[i].segment += 1;

                        if (pdi_queue[i].segment == m_length)
                        {
                            pdi_queue.pop_front();
                            --i;
                        }
                    }
                }
            }
        }

        void grow()
        {
            m_length += 1;
            m_positions.push_back(m_positions.back() - (directionToVector(m_directions.back()) / 10.0f));
            m_positions.back().y = -0.95f;
            m_directions.push_back(m_directions.back());
        }

        bool isOnGrid()
        {
            return (grid::isOnGrid(m_positions.front().x)) && (grid::isOnGrid(m_positions.front().z));
        }

        bool collidesWithHead(glm::vec2 p)
        {
            return (grid::isAlmostEqual(p.x, m_positions.front().x, 0.005f)
            && grid::isAlmostEqual(p.y, m_positions.front().z, 0.005f));
        }

        bool collidesWithSnake(glm::vec2 p)
        {
            bool result = false;
            for (auto &element : pdi_queue)
            {
                if (p.x == element.pos.x && p.y == element.pos.y)
                {
                    result = true;
                }
            }
            for (auto &pos : m_positions)
            {
                if (p.x == grid::toGrid(pos.x) && p.y == grid::toGrid(pos.z))
                {
                    result = true;
                }
            }
            return result;
        }

        bool collidesWithItself()
        {
            bool result = false;
            for (int i = 1; i < m_positions.size(); ++i)
            {
                if (glm::distance(m_positions.front(), m_positions[i]) < 0.05f)
                {
                    result = true;
                }
            }
            return result;
        }

    private:
        static glm::vec3 directionToVector(direction d)
        {
            switch(d)
            {
                case FORWARD:
                {
                    return {0.0f, 0.0f, -1.0f};
                }
                case BACKWARD:
                {
                    return {0.0f, 0.0f, 1.0f};
                }
                case LEFT:
                {
                    return {-1.0f, 0.0f, 0.0f};
                }
                case RIGHT:
                {
                    return {1.0f, 0.0f, 0.0f};
                }
                default:
                {
                    return {0.0f, 0.0f, 0.0f};
                }
            }
        }
    };
}

#endif //CLION_SNAKE_SNAKE_H
