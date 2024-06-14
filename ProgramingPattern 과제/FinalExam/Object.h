#pragma once

// 기본 클래스
class Object {
public:
    virtual void OnCollisionEnter(Object& other) {
    }
};

// 파생 클래스들
class Player : public Object {
public:
    void OnCollisionEnter(Object& other) override {

    }
};


class EnemyBlock : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }
};

class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }
};

class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }
};


int PhysicsAABB(Object A, Object B)
{
    return 0;
}