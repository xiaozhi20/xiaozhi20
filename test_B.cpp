#include <stdio.h>
#include "test.h"

int kkk = 100;

extern void test_B(){
	struct _pos pos;
	pos.x = 0;
	pos.y = 0;
	pos.w = 0;
	printf("����test_B.cpp => test_B() \n");
	test_A();
}
