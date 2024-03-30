#include <iostream>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")

bool isMouseMove = false;
double CursorXPos = 0.0;
double CursorYPos = 0.0;

enum class KEY_STATE {
    NONE,
    PRESS,
    RELEASE
};

KEY_STATE MouseStates[2] = { KEY_STATE::NONE, KEY_STATE::NONE };

void ErrorCallback(int error, const char* description) {
    std::cerr << "GLFW error: " << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        std::cout << key << " 키가 눌렸습니다." << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void MouseCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        MouseStates[0] = KEY_STATE::PRESS;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        MouseStates[0] = KEY_STATE::RELEASE;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        MouseStates[1] = KEY_STATE::PRESS;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        MouseStates[1] = KEY_STATE::RELEASE;
    }
}

void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    CursorXPos = xpos;
    CursorYPos = ypos;
    isMouseMove = true;
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    window = glfwCreateWindow(1280, 768, "Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(ErrorCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.f);

        if (MouseStates[0] == KEY_STATE::PRESS && isMouseMove) {
            glClearColor(1.f, 0.f, 1.f, 1.f);
        }
        else if (MouseStates[0] == KEY_STATE::PRESS) {
            glClearColor(0.f, 1.f, 0.f, 1.f);
        }

        if (MouseStates[1] == KEY_STATE::PRESS && isMouseMove) {
            glClearColor(0.f, 0.f, 1.f, 1.f);
        }
        else if (MouseStates[1] == KEY_STATE::PRESS) {
            glClearColor(1.f, 0.f, 0.f, 1.f);
        }

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
