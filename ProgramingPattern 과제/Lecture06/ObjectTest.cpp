#include "ObjectTest.h"
#include <iostream>



ObjectTest::ObjectTest()
{
	std::cout << "생성되었다" << std::endl;
}
ObjectTest::~ObjectTest()
{
	std::cout << "소멸되었다" << std::endl;
}

void ObjectTest::print()
{
	std::cout << "화가난다" << std::endl;
}
