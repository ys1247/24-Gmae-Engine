#include <iostream>

enum ForeColour {
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

int main() {
    std::cout << "화면에 그림을 그리는 프로그램입니다.\n";
    std::cout << "학번: 202327026\n"; // 여기에 본인의 학번을 입력하세요
    std::cout << "이름: 박윤서\n"; // 여기에 본인의 이름을 입력하세요

    while (true) {
        std::cout << "\n화면에 그릴 물체코드를 입력하세요 (1-6) 또는 종료(0): ";
        int objectCode;
        std::cin >> objectCode;

        if (objectCode == 0) {
            std::cout << "프로그램을 종료합니다.\n";
            break; // 루프를 종료하고 프로그램을 종료합니다.
        }

        switch (objectCode) {
        case 1:
            std::cout << "\x1b[" << White << "m" << "■"; // 흰색 블록
            break;
        case 2:
            std::cout << "\x1b[" << Red << "m" << "■"; // 빨강색 블록
            break;
        case 3:
            std::cout << "\x1b[" << Green << "m" << "■"; // 녹색 블록
            break;
        case 4:
            std::cout << "\x1b[" << Yellow << "m" << "■"; // 노란색 블록
            break;
        case 5:
            std::cout << "\x1b[" << Cyan << "m" << "■"; // 청록색 블록
            break;
        case 6:
            std::cout << "\x1b[" << Magenta << "m" << "■"; // 마젠타색 블록
            break;
        default:
            std::cout << "잘못된 입력입니다. 다시 시도하세요.\n";
        }
    }

    return 0;
}
