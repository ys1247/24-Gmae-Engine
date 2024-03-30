//과제물 프로젝트명: Lecture04_HW
//idle : 화면색 검정색으로 clear
//마우스 오른쪽 KeyDown하면 : 빨간색
//마우스 오른쪽 KeyUp하면 : 원상복구
//마우스 왼쪽 KeyDown하면 : 녹색
//마우스 왼쪽 KeyUp하면 : 원상복구
//마우스 오른쪽 KeyDown하고 드래그 중이면 : 파랑색
//마우스 왼쪽 KeyDown하고 드래그 중이면 : 마젠타색

//https://www.glfw.org/
#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool leftButtonDown = false;
bool rightButtonDown = false;
bool isDragging = false;

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
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 녹색
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftButtonDown = false;
        if (!rightButtonDown)
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검정색
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightButtonDown = true;
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 빨간색
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightButtonDown = false;
        if (!leftButtonDown)
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검정색
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    if (leftButtonDown && rightButtonDown)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 파란색
    else if (leftButtonDown)
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 마젠타색
    else if (rightButtonDown)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 파란색
    else
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검정색
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
