#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <random>

#include "MSList.h"
#include "Star.hpp"

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
    std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        moveFactor += 0.01f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scaleFactor += 0.1f;
    }
}

int main(void)
{
    //glfw라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    MSList<Star> starList; // Create an instance of MSList to hold stars
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disPos(-1.0f, 1.0f);
    std::uniform_real_distribution<float> disColor(0.0f, 1.0f);

    // Generate and add stars to the list
    for (int i = 0; i < 300; ++i) {
        float posX = disPos(gen);
        float posY = disPos(gen);
        float r = disColor(gen);
        float g = disColor(gen);
        float b = disColor(gen);
        Star* star = new Star(posX, posY, r, g, b); // Create a new star
        starList.push_back(star); // Add star to the list
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render stars
        for (int i = 0; i < starList.size(); ++i) {
            starList[i]->render(); // Render each star in the list
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
