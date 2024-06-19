#pragma once
#include "pch.h"

class Object {
public:
    float x, y;
    float vx, vy;
    float SIZE = 50.0f * 0.0025f;

    Object(float x = 0, float y = 0, float vx = 0, float vy = 0)
        : x(x), y(y), vx(vx), vy(vy) {}

    virtual void update(float deltaTime, float floorY) {
        x += vx * deltaTime;
        y += vy * deltaTime;
    }

    virtual void render() {}

    virtual void OnCollisionEnter(Object& other) {}
};

class Player : public Object {
public:
    float weight; // 오타 수정: weight
    float GRAVITY = 9.8f;
    float jumpSpeed = 5.0f;
    bool isJumping = false;
    float jumpStartTime = 0.0f;

    Player(float weight, float x = 0, float y = 0, float vx = 0, float vy = 0)
        : Object(x, y, vx, vy), weight(weight) {}

    void update(float deltaTime, float floorY) override {
        if (isJumping) {
            float jumpTime = glfwGetTime() - jumpStartTime;
            float jumpStrength = calculateJumpStrength(jumpTime);
            vy = jumpStrength;
            isJumping = false;
        }
        else {
            vy -= GRAVITY * deltaTime;
        }

        x += vx * deltaTime;
        y += vy * deltaTime;

        // 바닥과의 충돌 검사
        if (y - SIZE / 2 <= floorY) {
            y = floorY + SIZE / 2;
            vy = 0;
        }
    }

    void render() override {
        float halfSize = 0.0025f * 25.0f;
        float borderWidth = 0.0025f * 3.0f;

        // 플레이어의 외곽선 (53x53) 그리기
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(x - halfSize - borderWidth, y - halfSize - borderWidth);
        glVertex2f(x + halfSize + borderWidth, y - halfSize - borderWidth);
        glVertex2f(x + halfSize + borderWidth, y + halfSize + borderWidth);
        glVertex2f(x - halfSize - borderWidth, y + halfSize + borderWidth);
        glEnd();

        // 플레이어의 내부 사각형 (50x50) 그리기
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(x - halfSize, y - halfSize);
        glVertex2f(x + halfSize, y - halfSize);
        glVertex2f(x + halfSize, y + halfSize);
        glVertex2f(x - halfSize, y + halfSize);
        glEnd();
    }

    void jump(float jumpTime) {
        // 점프 메서드
        if (!isJumping && y - SIZE / 2 <= 0.0f) {
            isJumping = true;
            jumpStartTime = glfwGetTime();
        }
    }

    float calculateJumpStrength(float jumpTime) {
        // 점프 강도 계산 메서드
        const float maxJumpTime = 0.5f;
        jumpTime = std::min(jumpTime, maxJumpTime);
        float t = jumpTime / maxJumpTime;
        return jumpSpeed * (1.0f - t) + 8.0f * t;
    }

    void OnCollisionEnter(Object& other) override {
        // 플레이어와 충돌 발생 시 게임 종료
        std::cout << "Game Over!" << std::endl;
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
    }
};

class EnemyBlock : public Object {
public:
    float weight; // 오타 수정: weight
    bool isHigh;

    EnemyBlock(float weight, bool isHigh, float x = 0, float y = 0, float vx = 0, float vy = 0)
        : Object(x, y, vx, vy), weight(weight), isHigh(isHigh) {}

    void update(float deltaTime, float floorY) override {
        x += vx * deltaTime;

        // 화면 왼쪽으로 벗어난 경우 우측 끝으로 이동
        if (x < -1.0f - SIZE / 2) {
            x = 1.0f + SIZE / 2;
        }
    }

    void render() override {
        float width = 0.0025f * 50;
        float height = isHigh ? 0.0025f * 100.0f : 0.0025f * 300.0f;
        float bottomY = -1.0f + 0.25f + height / 2.0f;
        y = bottomY;

        // 적 블록 그리기
        glColor3ub(0, 255, 0);
        glBegin(GL_QUADS);
        glVertex2f(x - width / 2, y - height / 2);
        glVertex2f(x + width / 2, y - height / 2);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x - width / 2, y + height / 2);
        glEnd();
    }

    void OnCollisionEnter(Object& other) override {
        // 충돌 처리
    }
};

class Floor : public Object {
public:
    void update(float deltaTime, float floorY) override {
        // 바닥은 움직이지 않음
    }

    void render() override {
        // 바닥 그리기
        glColor3f(1.0f, 0.784f, 0.059f);
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.0025f * 300);
        glVertex2f(1.0f, -0.0025f * 300);
        glVertex2f(1.0f, -0.0025f * 400);
        glVertex2f(-1.0f, -0.0025f * 400);
        glEnd();
    }

    void OnCollisionEnter(Object& other) override {
        // 충돌 처리
    }
};
