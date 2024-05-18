#include <iostream>
#include <GLFW/glfw3.h>
#include <random>
#include <cmath>
#pragma comment(lib, "Opengl32.lib")

// GLFW 오류 발생 시 콘솔에 오류 메시지를 출력하는 함수
void errorCallback(int error, const char* description)
{
    std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

// 키보드 입력을 처리하는 함수, ESC 키를 누르면 창을 닫음
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// 초기화 함수, 현재는 아무 작업도 하지 않음
int initialize()
{

    return 0;
}

// 리소스 해제 함수, 현재는 아무 작업도 하지 않음
int release()
{
    return 0;
}

// 업데이트 함수, 현재는 아무 작업도 하지 않음
int update()
{
    return 0;
}

// 원주율(PI) 값을 정의
float M_PI = 3.141592f;

// 원을 그리는 함수
void drawCircle(float centerX, float centerY, float radius, int numSegments, int red, int green, int blue) {
    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬 모드로 그리기 시작
    glColor3ub(red, green, blue);  // 원의 색상 설정
    glVertex2f(centerX, centerY); // 원의 중심점 설정
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * float(i) / float(numSegments); // 각도 계산
        float x = radius * cosf(angle); // x 좌표 계산
        float y = radius * sinf(angle); // y 좌표 계산
        glVertex2f(centerX + x, centerY + y); // 원의 점 추가
    }
    glEnd(); // 그리기 종료
}

// 타원을 그리는 함수
void drawEllipse(float centerX, float centerY, float radius, int numSegments, int red, int green, int blue) {
    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬 모드로 그리기 시작
    glColor3ub(red, green, blue);  // 타원의 색상 설정
    glVertex2f(centerX, centerY); // 타원의 중심점 설정
    float angleInRadians = 45.0f * M_PI / 360.0f; // 45도 각도 계산
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * float(i) / float(numSegments); // 각도 계산
        float x = radius * cosf(angle); // x 좌표 계산
        float y = radius * sinf(angle) / 4; // y 좌표 계산 (타원 형태를 만들기 위해 /4 적용)
        glVertex2f(centerX + x, centerY + y); // 타원의 점 추가
    }

    glEnd(); // 그리기 종료
}

// 원 테두리를 그리는 함수
void drawCircleOutline(float centerX, float centerY, float radius, int numSegments, float lineWidth) {
    glLineWidth(lineWidth);  // 라인 두께 설정
    glBegin(GL_LINE_LOOP); // 라인 루프 모드로 그리기 시작
    glColor3f(1.0f, 0.5f, 0.0f);  // 주황색 테두리 색상 설정
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * float(i) / float(numSegments); // 각도 계산
        float x = radius * cosf(angle); // x 좌표 계산
        float y = radius * sinf(angle); // y 좌표 계산
        glVertex2f(centerX + x, centerY + y); // 원 테두리의 점 추가
    }
    glEnd(); // 그리기 종료
    glLineWidth(1.0f);  // 라인 두께를 기본값으로 재설정
}

// 사각형을 그리는 함수
void drawRectangle(float centerX, float centerY, float length)
{
    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬 모드로 그리기 시작
    glColor3ub(91, 155, 213); // 사각형의 색상 설정
    glVertex2f(centerX + (length / 2.5), centerY + (length / 2.5)); // 우측 상단 점
    glVertex2f(centerX - (length / 2.5), centerY + (length / 2.5)); // 좌측 상단 점
    glVertex2f(centerX - (length / 2.5), centerY - (length / 2.5)); // 좌측 하단 점
    glVertex2f(centerX + (length / 2.5), centerY - (length / 2.5)); // 우측 하단 점
    glEnd(); // 그리기 종료
}

// 사각형 테두리를 그리는 함수
void drawRectangleOutline(float centerX, float centerY, float length, float lineWidth)
{
    glLineWidth(lineWidth); // 라인 두께 설정
    glBegin(GL_LINE_LOOP); // 라인 루프 모드로 그리기 시작
    glColor3f(0.0f, 0.0f, 0.0f); // 검은색 테두리 색상 설정
    glVertex2f(centerX + (length / 2.5), centerY + (length / 2.5)); // 우측 상단 점
    glVertex2f(centerX - (length / 2.5), centerY + (length / 2.5)); // 좌측 상단 점
    glVertex2f(centerX - (length / 2.5), centerY - (length / 2.5)); // 좌측 하단 점
    glVertex2f(centerX + (length / 2.5), centerY - (length / 2.5)); // 우측 하단 점
    glEnd(); // 그리기 종료
    glLineWidth(1.0f); // 라인 두께를 기본값으로 재설정
}

// 별 모양을 그리는 함수
void drawStar()
{
    glColor3ub(255, 242, 0); // 노란색 설정
    glBegin(GL_TRIANGLES); // 삼각형 모드로 그리기 시작
    glVertex2f(0, 20); // 별 위쪽 점
    glVertex2f(-5, 7); // 별 왼쪽 위 점
    glVertex2f(5, 7); // 별 오른쪽 위 점
    glEnd(); // 그리기 종료

    glBegin(GL_TRIANGLES);
    glVertex2f(-5, 7); // 별 왼쪽 위 점
    glVertex2f(-14, 7); // 별 왼쪽 아래 점
    glVertex2f(-7, -2); // 별 왼쪽 중간 점
    glEnd(); // 그리기 종료

    glBegin(GL_TRIANGLES);
    glVertex2f(-7, -2); // 별 왼쪽 중간 점
    glVertex2f(-11, -12); // 별 가운데 아래 점
    glVertex2f(0, -6); // 별 정중앙 아래 점
    glEnd(); // 그리기 종료

    glBegin(GL_TRIANGLES);
    glVertex2f(0, -6); // 별 정중앙 아래 점
    glVertex2f(11, -12); // 별 가운데 아래 점
    glVertex2f(7, -2); // 별 오른쪽 중간 점
    glEnd(); // 그리기 종료

    glBegin(GL_TRIANGLES);
    glVertex2f(7, -2); // 별 오른쪽 중간 점
    glVertex2f(14, 7); // 별 오른쪽 아래 점
    glVertex2f(5, 7); // 별 오른쪽 위 점
    glEnd(); // 그리기 종료

    glBegin(GL_POLYGON); // 다각형 모드로 그리기 시작
    glVertex2f(5, 7); // 별 오른쪽 위 점
    glVertex2f(-5, 7); // 별 왼쪽 위 점
    glVertex2f(-7, -2); // 별 왼쪽 중간 점
    glVertex2f(0, -6); // 별 정중앙 아래 점
    glVertex2f(7, -2); // 별 오른쪽 중간 점
    glEnd(); // 그리기 종료

    glColor3f(0.0f, 0.0f, 0.0f); // 검은색 설정
    glBegin(GL_LINE_LOOP); // 라인 루프 모드로 그리기 시작 (별 외곽선)
    glVertex2f(5, 7); // 별 오른쪽 위 점
    glVertex2f(0, 20); // 별 위쪽 점
    glVertex2f(-5, 7); // 별 왼쪽 위 점
    glVertex2f(-14, 7); // 별 왼쪽 아래 점
    glVertex2f(-7, -2); // 별 왼쪽 중간 점
    glVertex2f(-11, -12); // 별 가운데 아래 점
    glVertex2f(0, -6); // 별 정중앙 아래 점
    glVertex2f(11, -12); // 별 가운데 아래 점
    glVertex2f(7, -2); // 별 오른쪽 중간 점
    glVertex2f(14, 7); // 별 오른쪽 아래 점
    glVertex2f(5, 7); // 별 오른쪽 위 점
    glEnd(); // 그리기 종료


}

// 렌더링 함수
void render(float rotangle)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경색 설정 (흰색)
    glClear(GL_COLOR_BUFFER_BIT); // 색상 버퍼 지우기
    glRotatef(rotangle, 0, 0, 1); // z축 기준으로 rotangle 만큼 회전
    drawCircle(0, 0, 180, 180, 255, 217, 102); // 노란색 큰 원 그리기
    drawCircleOutline(0, 0, 180, 180, 3.0f); // 큰 원 외곽선 그리기 (두께 3.0)
    drawCircle(-90, 0, 70, 50, 255, 230, 153); // 작은 노란색 원 그리기
    glRotatef(45, 0, 0, 1); // z축 기준으로 45도 회전
    drawEllipse(0, -163, 50, 50, 255, 192, 0); // 타원 그리기
    glRotatef(-45, 0, 0, 1); // z축 기준으로 -45도 회전 (원래 상태로 돌아옴)
    glRotatef(-rotangle, 0, 0, 1); // z축 기준으로 -rotangle만큼 회전 (원래 상태로 돌아옴)

    glRotatef(rotangle / 2, 0, 0, 1); // z축 기준으로 rotangle/2 만큼 회전
    glTranslatef(400, 0, 0); // x축 방향으로 400만큼 이동
    glRotatef(rotangle * 3, 0, 0, 1); // z축 기준으로 rotangle*3 만큼 회전
    drawRectangle(0, 0, 100); // 사각형 그리기
    drawRectangleOutline(0, 0, 100, 2.0f); // 사각형 외곽선 그리기 (두께 2.0)
    glRotatef(-rotangle * 3, 0, 0, 1); // z축 기준으로 -rotangle*3 만큼 회전 (원래 상태로 돌아옴)
    glRotatef(rotangle * 10, 0, 0, 1); // z축 기준으로 rotangle*10 만큼 회전
    glTranslatef(140, 0, 0); // x축 방향으로 140만큼 이동
    glRotatef(rotangle * 10, 0, 0, 1); // z축 기준으로 rotangle*10 만큼 회전
    drawStar(); // 별 그리기
    glRotatef(-rotangle * 10, 0, 0, 1); // z축 기준으로 -rotangle*10 만큼 회전 (원래 상태로 돌아옴)
    glRotatef(-rotangle / 2, 0, 0, 1); // z축 기준으로 -rotangle/2 만큼 회전 (원래 상태로 돌아옴)
    glTranslatef(-540, 0, 0); // x축 방향으로 -540만큼 이동 (원래 위치로 돌아옴)
    glRotatef(-rotangle * 10, 0, 0, 1); // z축 기준으로 -rotangle*10 만큼 회전 (원래 상태로 돌아옴)
}

// 메인 함수
int main(void)
{
    // GLFW 초기화 및 창 생성
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 720, "Lecture-10", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // 현재 컨텍스트로 윈도우 설정
    glfwSetErrorCallback(errorCallback);  // GLFW 오류 콜백 함수 설정
    glfwSetKeyCallback(window, keyCallback);  // 키 이벤트 콜백 함수 설정
    double rd = 0.0f;  // 회전 각도 초기화
    initialize();  // 초기화 함수 호출
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapInterval(1);  // 수직 동기화 설정
        glViewport(0, 0, 1280, 720);  // 뷰포트 설정
        glMatrixMode(GL_PROJECTION);  // 투영 행렬 모드 설정
        glLoadIdentity();  // 현재 행렬을 단위 행렬로 초기화
        glOrtho(0, 1280, 0, 720, -1, 1);  // 2D 직교 좌표계 설정
        glMatrixMode(GL_MODELVIEW);  // 모델뷰 행렬 모드 설정
        glLoadIdentity();  // 현재 행렬을 단위 행렬로 초기화
        glTranslatef(1280 / 2, 720 / 2, 0);  // 화면 중앙으로 이동

        glfwPollEvents();  // 이벤트 처리
        update();  // 게임 상태 업데이트
        render(rd);  // 렌더링 함수 호출

        rd += 0.0133333f * 12.0f;  // 회전 각도 증가

        glfwSwapBuffers(window);  // 프론트와 백 버퍼를 교환하여 화면에 그림
    }

    release();  // 리소스 해제 함수 호출
    glfwTerminate();  // GLFW 종료
    return 0;
}