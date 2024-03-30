#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool leftButtonDown = false;
bool rightButtonDown = false;
bool isDragging = false;
float previousClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        leftButtonDown = true;
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftButtonDown = false;
        if (!rightButtonDown)
            glClearColor(previousClearColor[0], previousClearColor[1], previousClearColor[2], previousClearColor[3]);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightButtonDown = true;
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Red
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightButtonDown = false;
        if (!leftButtonDown)
            glClearColor(previousClearColor[0], previousClearColor[1], previousClearColor[2], previousClearColor[3]);
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    if (leftButtonDown && rightButtonDown)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    else if (leftButtonDown)
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Magenta
    else if (rightButtonDown)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    else
        glClearColor(previousClearColor[0], previousClearColor[1], previousClearColor[2], previousClearColor[3]); // Restore previous color
}

int main(void) {
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
