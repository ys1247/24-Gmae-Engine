#include "MObject.h"
#include <GLFW/glfw3.h>

class Star : public MObject
{
public:
    Star(float posX, float posY, float R, float G, float B)
    {
        _posX = posX;
        _posY = posY;
        _red = R;
        _green = G;
        _blue = B;
    }

    ~Star() { }

    void update() { }

    void render()
    {
        glBegin(GL_TRIANGLES);
        glColor3f(_red, _green, _blue);

        glVertex2f(0 + _posX, 0.05 + _posY);
        glVertex2f(0 + _posX, -0.015 + _posY);
        glVertex2f(-0.030 + _posX, -0.040 + _posY);
        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex2f(0 + _posX, 0.050 + _posY);
        glVertex2f(0.030 + _posX, -0.040 + _posY);
        glVertex2f(0 + _posX, -0.015 + _posY);
        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex2f(0 + _posX, -0.015 + _posY);
        glVertex2f(0.040 + _posX, 0.015 + _posY);
        glVertex2f(-0.040 + _posX, 0.015 + _posY);
        glEnd();
    }

private:
    float _posX;
    float _posY;
    float _red;
    float _green;
    float _blue;
};
