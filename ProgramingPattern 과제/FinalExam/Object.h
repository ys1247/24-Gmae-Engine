#pragma once

// �⺻ Ŭ����
class Object {
public:
    virtual void OnCollisionEnter(Object& other) {
    }
};

// �Ļ� Ŭ������
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