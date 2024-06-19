#include "Object.h"
#include <GLFW/glfw3.h>
#include <iostream>

Object* objects[4];
float floorY = -0.0025f * 300;
float lastTime = 0.0f;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Player* player = static_cast<Player*>(objects[0]);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        player->jump(0.0f);
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        float jumpTime = glfwGetTime() - player->jumpStartTime;
        player->jump(jumpTime);
    }
}

void CheckCollisions() {
    Player* player = static_cast<Player*>(objects[0]);
    EnemyBlock* obstacle1 = static_cast<EnemyBlock*>(objects[1]);
    EnemyBlock* obstacle2 = static_cast<EnemyBlock*>(objects[2]);

    // 충돌 검사
    if (player->x + player->SIZE / 2 > obstacle1->x - obstacle1->SIZE / 2 &&
        player->x - player->SIZE / 2 < obstacle1->x + obstacle1->SIZE / 2 &&
        player->y + player->SIZE / 2 > obstacle1->y - obstacle1->SIZE / 2 &&
        player->y - player->SIZE / 2 < obstacle1->y + obstacle1->SIZE / 2) {
        player->OnCollisionEnter(*obstacle1);
    }

    if (player->x + player->SIZE / 2 > obstacle2->x - obstacle2->SIZE / 2 &&
        player->x - player->SIZE / 2 < obstacle2->x + obstacle2->SIZE / 2 &&
        player->y + player->SIZE / 2 > obstacle2->y - obstacle2->SIZE / 2 &&
        player->y - player->SIZE / 2 < obstacle2->y + obstacle2->SIZE / 2) {
        player->OnCollisionEnter(*obstacle2);
    }
}

void AdjustObjectPositions() {
    EnemyBlock* obstacle1 = static_cast<EnemyBlock*>(objects[1]);
    EnemyBlock* obstacle2 = static_cast<EnemyBlock*>(objects[2]);

    float obstacleSpeed = -0.5f;

    // 장애물 위치 설정 및 속도 설정
    obstacle1->x = 0.8f;
    obstacle2->x = 1.0f;

    obstacle1->vx = obstacleSpeed;
    obstacle2->vx = obstacleSpeed;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW 윈도우 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glClearColor(0.0f, 0.1176f, 0.39215f, 1.0f);

    // 객체 생성
    objects[0] = new Player(1.0f, 0.0f, 0.5f, 0.0f, 0.0f);
    objects[1] = new EnemyBlock(1.0f, true, 0.5f, 0.0f, 0.0f, 0.0f);
    objects[2] = new EnemyBlock(1.0f, false, 0.7f, 0.0f, 0.0f, 0.0f);
    objects[3] = new Floor();

    glfwSetKeyCallback(window, keyCallback);

    AdjustObjectPositions();

    lastTime = glfwGetTime();

    // 게임 루프
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float now = glfwGetTime();
        float deltaTime = now - lastTime;
        lastTime = now;

        CheckCollisions();

        for (int i = 0; i < 4; ++i) {
            objects[i]->update(deltaTime, floorY);
            objects[i]->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 객체 메모리 해제
    for (int i = 0; i < 4; ++i) {
        delete objects[i];
    }

    glfwTerminate();
    return 0;
}
