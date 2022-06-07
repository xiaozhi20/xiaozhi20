#include <stdio.h>
#include <stdlib.h>
#include "test.h"


//程序员A的代码


int main(void){
	struct _pos  pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	pos.w = 0;
	
	printf("kkk: %d\n", kkk);

	test_A();
	test_B();
	system("pause");
}


void test_A(){
	printf("我是test_A.cpp => test_A() \n");
	{
		static int time=0;
		if(++time>5)return ;
	}
	test_B();
}