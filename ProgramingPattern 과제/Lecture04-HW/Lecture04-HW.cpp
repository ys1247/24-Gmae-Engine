#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

float clearColorRed = 0.0f;
float clearColorGreen = 0.0f;
float clearColorBlue = 0.0f;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            clearColorRed = 1.0f; // 빨간색
        }
        else if (action == GLFW_RELEASE)
        {
            clearColorRed = 0.0f; // 원상 복구
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            clearColorGreen = 1.0f; // 녹색
        }
        else if (action == GLFW_RELEASE)
        {
            clearColorGreen = 0.0f; // 원상 복구
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    int leftMouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int rightMouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    if (leftMouseButtonState == GLFW_PRESS && rightMouseButtonState == GLFW_RELEASE)
    {
        clearColorGreen = 0.0f; // 녹색
        clearColorBlue = 1.0f; // 파란색
    }
    else if (rightMouseButtonState == GLFW_PRESS && leftMouseButtonState == GLFW_RELEASE)
    {
        clearColorRed = 1.0f; // 빨간색
        clearColorBlue = 1.0f; // 파란색
    }
    else if (leftMouseButtonState == GLFW_PRESS && rightMouseButtonState == GLFW_PRESS)
    {
        clearColorGreen = 1.0f; // 마젠타색
        clearColorBlue = 0.0f; // 파란색 원상 복구
    }
    else if (leftMouseButtonState == GLFW_RELEASE && rightMouseButtonState == GLFW_RELEASE)
    {
        clearColorBlue = 0.0f; // 파란색 원상 복구
    }
}



int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(clearColorRed, clearColorGreen, clearColorBlue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
