#include <stdio.h>

void test1();

struct _pos{
	int x;
	int y;
};


void test2(){
	struct _pos pos;
	pos.y = 0;

	printf("����test2.cpp =>test2 ...\n");
	printf("��Ҫ���� test1.cpp=>test1\n");
	test1();
}

