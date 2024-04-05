#pragma comment(lib, "Opengl32.lib") // OpenGL 라이브러리 링크

#include <GLFW/glfw3.h> // GLFW 라이브러리 헤더 파일 포함
#include <iostream>

bool mouseRightButtonPressed = false; // 마우스 오른쪽 버튼이 눌려 있는지 여부를 나타내는 변수
bool mouseLeftButtonPressed = false; // 마우스 왼쪽 버튼이 눌려 있는지 여부를 나타내는 변수
double lastMouseX = 0.0; // 이전 마우스 커서의 X 위치
double lastMouseY = 0.0; // 이전 마우스 커서의 Y 위치
double starPositionX = 0.0; // 별의 X 위치
double starPositionY = 0.0; // 별의 Y 위치
double scaleFactor = 1.0; // 확대/축소 비율
double viewportWidth = 1280.0; // 뷰포트 너비
double viewportHeight = 768.0; // 뷰포트 높이

// GLFW 에러 콜백 함수
void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW 에러: " << description << std::endl;
}

// 키 입력 콜백 함수
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE); // ESC 키가 눌렸을 때 창을 닫음
    }
}

// 마우스 버튼 입력 콜백 함수
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            mouseLeftButtonPressed = true; // 마우스 왼쪽 버튼이 눌렸을 때 플래그를 true로 설정
            glfwGetCursorPos(window, &lastMouseX, &lastMouseY); // 현재 마우스 커서의 위치를 저장
        }
        else if (action == GLFW_RELEASE)
        {
            mouseLeftButtonPressed = false; // 마우스 왼쪽 버튼이 떼어졌을 때 플래그를 false로 설정
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            mouseRightButtonPressed = true; // 마우스 오른쪽 버튼이 눌렸을 때 플래그를 true로 설정
            glfwGetCursorPos(window, &lastMouseX, &lastMouseY); // 현재 마우스 커서의 위치를 저장
        }
        else if (action == GLFW_RELEASE)
        {
            mouseRightButtonPressed = false; // 마우스 오른쪽 버튼이 떼어졌을 때 플래그를 false로 설정
        }
    }
}

// 마우스 휠 스크롤 콜백 함수
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    scaleFactor += yoffset * 0.1; // 스크롤 방향에 따라 확대/축소 비율 조절
    scaleFactor = std::max(scaleFactor, 0.1); // 최소 확대/축소 비율 설정
}

// 마우스 커서 이동 콜백 함수
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (mouseLeftButtonPressed)
    {
        double deltaX = xpos - lastMouseX; // X 방향 이동량 계산
        double deltaY = ypos - lastMouseY; // Y 방향 이동량 계산

        // 별의 위치 업데이트 (윈도우 크기에 대해 정규화)
        starPositionX += deltaX / viewportWidth;
        starPositionY -= deltaY / viewportHeight;

        // 화면 경계를 벗어나지 않도록 제한
        starPositionX = std::max(-1.0, std::min(starPositionX, 1.0));
        starPositionY = std::max(-1.0, std::min(starPositionY, 1.0));

        lastMouseX = xpos; // 현재 마우스 커서의 위치를 이전 위치로 갱신
        lastMouseY = ypos;
    }
    else if (mouseRightButtonPressed)
    {
        double deltaX = xpos - lastMouseX; // X 방향 이동량 계산
        double deltaY = ypos - lastMouseY; // Y 방향 이동량 계산

        // 별의 위치 업데이트 (윈도우 크기에 대해 정규화)
        double starCenterX = starPositionX + 0.25; // 별의 중점 X 위치
        double starCenterY = starPositionY - 0.25; // 별의 중점 Y 위치
        double scale = (deltaX > 0) ? 1.1 : 0.9; // 우측 드래그는 확대, 좌측 드래그는 축소

        starPositionX -= (xpos - starCenterX) / viewportWidth * (scale - 1.0);
        starPositionY += (ypos - starCenterY) / viewportHeight * (scale - 1.0);

        scaleFactor *= scale; // 확대/축소 비율 업데이트

        // 화면 경계를 벗어나지 않도록 제한
        starPositionX = std::max(-1.0, std::min(starPositionX, 1.0));
        starPositionY = std::max(-1.0, std::min(starPositionY, 1.0));

        lastMouseX = xpos; // 현재 마우스 커서의 위치를 이전 위치로 갱신
        lastMouseY = ypos;
    }
}

// 렌더링 함수
int render()
{
    glBegin(GL_TRIANGLES);
    // 첫 번째 삼각형
    // 점1
    glColor3f(1.0f, 1.0f, 1.0f); // 흰색으로 색상 설정
    glVertex2f(0.0f, 0.5f); // 첫 번째 정점
    // 점2
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.5f, -0.5f); // 두 번째 정점
    // 점3
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, 0.5f); // 세 번째 정점

    // 두 번째 삼각형
    // 점1
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.5f); // 첫 번째 삼각형과 같은 첫 번째 정점 사용
    // 점2
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.5f, 0.5f); // 두 번째 정점
    // 점3
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, -0.5f); // 두 번째 정점

    // 내부 삼각형
    // 점1
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.9f); // 첫 번째 정점

    // 점2
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.18f, 0.4f); // 두 번째 정점
    // 점3
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.18f, 0.4f); // 세 번째 정점

    glEnd();

    return 0;
}

// 메인 함수
int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetScrollCallback(window, scrollCallback); // 스크롤 콜백 함수 등록

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 보라색 배경 설정
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(starPositionX, starPositionY, 0.0f); // 별의 위치에 따라 이동
        glScalef(scaleFactor, scaleFactor, 1.0); // 확대/축소 적용
        render(); // 삼각형 렌더링
        glPopMatrix();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
