#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "Object.h"



// 객체 생성
Player player;

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

int Physics()
{
    return 0;
}

int Initialize()
{
    return 0;
}

int Update()
{
    return 0;
}

int Render()
{
    // Render 함수 내부의 플레이어 객체 렌더링 부분 수정
    glColor3ub(255, 0, 0);  // 빨간색 설정
    glBegin(GL_QUADS);
    glVertex2f(-25.0f, -25.0f);  // 좌하단
    glVertex2f(25.0f, -25.0f);   // 우하단
    glVertex2f(25.0f, 25.0f);    // 우상단
    glVertex2f(-25.0f, 25.0f);   // 좌상단
    glEnd();

    // 테두리 그리기
    glColor3ub(255, 255, 255);  // 흰색 설정
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-25.0f, -25.0f);  // 좌하단
    glVertex2f(25.0f, -25.0f);   // 우하단
    glVertex2f(25.0f, 25.0f);    // 우상단
    glVertex2f(-25.0f, 25.0f);   // 좌상단
    glEnd();

    // Render 함수 내부에 추가
    glColor3ub(255, 200, 15);  // 황색 설정
    glBegin(GL_QUADS);
    glVertex2f(-400.0f, -100.0f);  // 좌하단
    glVertex2f(400.0f, -100.0f);   // 우하단
    glVertex2f(400.0f, -97.0f);    // 우상단
    glVertex2f(-400.0f, -97.0f);   // 좌상단
    glEnd();

    // Render 함수 내부에 추가
// 첫 번째 장애물 (높이 100cm)
    glColor3ub(0, 255, 0);  // 녹색 설정
    glBegin(GL_QUADS);
    glVertex2f(-100.0f, -100.0f);  // 좌하단
    glVertex2f(-50.0f, -100.0f);   // 우하단
    glVertex2f(-50.0f, 0.0f);      // 우상단
    glVertex2f(-100.0f, 0.0f);     // 좌상단
    glEnd();

    // 두 번째 장애물 (높이 300cm)
    glColor3ub(0, 255, 0);  // 녹색 설정
    glBegin(GL_QUADS);
    glVertex2f(100.0f, -300.0f);  // 좌하단
    glVertex2f(150.0f, -300.0f);  // 우하단
    glVertex2f(150.0f, 0.0f);     // 우상단
    glVertex2f(100.0f, 0.0f);     // 좌상단
    glEnd();

    return 0;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Physics();
        Update();
        Render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
