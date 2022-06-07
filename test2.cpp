#include <stdio.h>

void test1();

struct _pos{
	int x;
	int y;
};


void test2(){
	struct _pos pos;
	pos.y = 0;

	printf("我是test2.cpp =>test2 ...\n");
	printf("我要调用 test1.cpp=>test1\n");
	test1();
}

