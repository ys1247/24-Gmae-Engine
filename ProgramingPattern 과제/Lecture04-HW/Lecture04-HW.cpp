#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

#pragma comment(lib, "opengl32.lib")

int CursorXPos = 0;
int CursorYPos = 0;
bool isMouseMove = false;

enum class KEY_STATE
{
    NONE,
    PRESS,
    // DOWN,
    RELEASE,
    // END
};

std::vector<KEY_STATE> MouseStates;

void ErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW error: " << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        std::cout << key << " ÀÔ·ÂµÊ." << std::endl;
        glfwSetWindowShouldClose(window, 1);
    }
}

void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            MouseStates[0] = KEY_STATE::PRESS;
        else if (action == GLFW_RELEASE)
            MouseStates[0] = KEY_STATE::RELEASE;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
            MouseStates[1] = KEY_STATE::PRESS;
        else if (action == GLFW_RELEASE)
            MouseStates[1] = KEY_STATE::RELEASE;
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    isMouseMove = true;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 768, "Ghwa-jae Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // glfwSetWindowMonitor(window, monitor, 0, 0, 1280, 768, 1);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(ErrorCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseCallback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    MouseStates.resize(3, KEY_STATE::NONE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.f);

        if (MouseStates[0] == KEY_STATE::PRESS && isMouseMove)
            glClearColor(1.f, 0.f, 1.f, 1.f);
        else if (MouseStates[0] == KEY_STATE::PRESS)
            glClearColor(0.f, 1.f, 0.f, 1.f);

        if (MouseStates[1] == KEY_STATE::PRESS && isMouseMove)
            glClearColor(0.f, 0.f, 1.f, 1.f);
        else if (MouseStates[1] == KEY_STATE::PRESS)
            glClearColor(1.f, 0.f, 0.f, 1.f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        std::cout << isMouseMove << std::endl;

        isMouseMove = false;
    }

    glfwTerminate();
    return 0;
}