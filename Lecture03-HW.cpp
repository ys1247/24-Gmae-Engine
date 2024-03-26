#include <iostream>

enum ForeColour
{
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

using namespace std;

void DrawBlock()
{
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            cout << "■";
        }
        cout << "\n";
    }
    cout << "\x1b[0m";
}

int main()
{
    const int WHITE_MASK = 0b1;
    const int RED_MASK = 0b10;
    const int GREEN_MASK = 0b100;
    const int YELLOW_MASK = 0b1000;
    const int CYAN_MASK = 0b10000;
    const int MAGENTA_MASK = 0b100000;
    const int EXIT_FLAG = 64;

    cout << "화면에 그림을 그리는 프로그램입니다.\n";
    cout << "학번 : 202327026\n";
    cout << "이름 : 박윤서\n\n";

    // 콘솔 가상 터미널 시퀀스
    // \x1b[39m

    while (true)
    {
        cout << "화면에 그릴 물체코드를 입력하세요 : ";

        int input = 0;
        cin >> input;

        if (input > 64 || input < 0)
        {
            cout << "올바른 코드를 입력하세요.\n";
            continue;
        }
        if (input == EXIT_FLAG)
        {
            cout << "종료";
            break;
        }
        if (input & WHITE_MASK)
        {
            cout << "\x1b[" << (int)White << "m";
            DrawBlock();
        }
        if (input & RED_MASK)
        {
            cout << "\x1b[" << (int)Red << "m";
            DrawBlock();
        }
        if (input & GREEN_MASK)
        {
            cout << "\x1b[" << (int)Green << "m";
            DrawBlock();
        }
        if (input & YELLOW_MASK)
        {
            cout << "\x1b[" << (int)Yellow << "m";
            DrawBlock();
        }
        if (input & CYAN_MASK)
        {
            cout << "\x1b[" << (int)Cyan << "m";
            DrawBlock();
        }
        if (input & MAGENTA_MASK)
        {
            cout << "\x1b[" << (int)Magenta << "m";
            DrawBlock();
        }
    }
}