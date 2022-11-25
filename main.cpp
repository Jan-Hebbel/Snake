#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "stb_image.h"
#include "snake.h"
#include "snack.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

snake::Snake snek(snake::FORWARD, glm::vec2(0.05f, 0.05f), 0.5f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        snek.m_plannedDirection = snake::FORWARD;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        snek.m_plannedDirection = snake::BACKWARD;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        snek.m_plannedDirection = snake::LEFT;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        snek.m_plannedDirection = snake::RIGHT;
    }
}

int main()
{
    /* Initialize the library */
    /* glfwInit() returns GLFW_TRUE (1), if successful, else GLFW_FALSE (0) */
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    /* This is a must before initializing GLAD */
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    float cube[] = {
        -0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,

        -0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,

        -0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        -0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,
        -0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,

        0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,

        -0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,
        -0.05f, -0.05f,  0.05f,  0.0f, 0.2f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 0.2f, 0.0f,

        -0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f,  0.05f,  0.05f,  0.0f, 0.6f, 0.0f,
        -0.05f,  0.05f, -0.05f,  0.0f, 0.6f, 0.0f,
    };

    float snack[] = {
        -0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,

        -0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,

        -0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        -0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,
        -0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,

        0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,

        -0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,
        -0.05f, -0.05f,  0.05f,  0.2f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.2f, 0.0f, 0.0f,

        -0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
        0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f,  0.05f,  0.05f,  0.6f, 0.0f, 0.0f,
        -0.05f,  0.05f, -0.05f,  0.6f, 0.0f, 0.0f,
    };

    float board[] = {
        -1.0f, -1.0f, -1.0f, 0.2f, 0.2f, 0.2f, // bottom left
        1.0f, -1.0f, -1.0f, 0.2f, 0.2f, 0.2f, // bottom right
        -1.0f, -1.0f,  1.0f, 0.2f, 0.2f, 0.2f, // top left
        1.0f, -1.0f,  1.0f, 0.2f, 0.2f, 0.2f, // top right
        -1.0f, -1.0f,  1.0f, 0.2f, 0.2f, 0.2f, // top left
        1.0f, -1.0f, -1.0f, 0.2f, 0.2f, 0.2f, // bottom right
    };

    unsigned int vao[3];
    glGenVertexArrays(3, vao);

    unsigned int vbo1;
    glGenBuffers(1, &vbo1);
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int vbo2;
    glGenBuffers(1, &vbo2);
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(board), board, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int vbo3;
    glGenBuffers(1, &vbo3);
    glBindVertexArray(vao[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(snack), snack, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    /* create shader object which does everything shaders for us */
    Shader shader("../shader.vs", "../shader.fs");
    camera::Camera cam(glm::vec3(0.0f, 1.2f, 1.5f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -60.0f);

    /* set up random number generator for later use */
    snack::Snack snak = snack::Snack();

    /* variable that stops calling of changeDirections multiple times when its still the same grid position */
    glm::vec3 newPosition = grid::toGridv3(snek.m_positions.front());
    unsigned int blocker = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* calculate deltaTime */
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* rendering goes here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* activate shader */
        shader.use();

        /* draw snake */
        glm::mat4 view = cam.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::perspective(glm::radians(cam.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vao[0]);

        /* draw all snake segments in the vector */
        for (glm::vec3 pos : snek.m_positions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pos);
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /* draw extra segments at positions where snake changed direction so that snake doesnt have weird edges */
        for (auto element : snek.pdi_queue)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(element.pos.x, -0.95f, element.pos.y));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /* game over: */
        /* if snake runs off the board */
        if (snek.m_positions[0].x <= -0.96f
            || snek.m_positions[0].x >= 0.96f
            || snek.m_positions[0].z <= -0.96f
            || snek.m_positions[0].z >= 0.96f)
        {
            glfwSetWindowShouldClose(window, true);
        }
        /* if snake collides with itself */
        if (snek.collidesWithItself())
            glfwSetWindowShouldClose(window, true);

        /* draw board */
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* check if snake collides with snack and draw the snack */
        if (snek.collidesWithHead(snak.position))
        {
            snak = snack::Snack();
            while ((snak.position.x == 0.0f || snak.position.y == 0.0f)
                  || snek.collidesWithSnake(snak.position))
            {
                snak = snack::Snack();
            }
            snek.grow();
        }
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(snak.position.x, -0.95f, snak.position.y));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model2));

        /* move snake */
        glm::vec3 lastPosition = newPosition;
        snek.move(deltaTime);
        newPosition = grid::toGridv3(snek.m_positions.front());
        if (lastPosition != newPosition)
            blocker = 0;
        if (snek.isOnGrid() && blocker == 0)
        {
            ++blocker;
            snek.m_positions.front() = grid::toGridv3(snek.m_positions.front());
            snek.changeDirections();
        }

        glBindVertexArray(vao[2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, vao);
    glDeleteBuffers(1, &vbo1);

    glfwTerminate();
    return 0;
}
