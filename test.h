//#pragma once    //第一种 文件只包含一次
#ifndef TEST_H    //第二种 #ifndef 和 #endif 包围的代码只包含一次
#define TEST_H


#include <stdio.h>

struct _pos{
	int x;
	int y;
	int z;
	int w;
};

void test_A();
void test_B();

extern int kkk;
#endif