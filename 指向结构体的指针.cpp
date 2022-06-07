#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _friend{
	char name[32];
	char sex; // m - 男  f - 女
	int  age;
};

int main(void){
	struct _friend girl = {"小龙女", 'f', 18};

	struct _friend *my_girl = &girl;

	printf("小龙女的名字：%s, 性别：%s  年龄：%d\n", girl.name, girl.sex=='m'?"男":"女", girl.age);

	//指针访问结构体变量的成员，有两种方式
	//方式1. 直接解引
	printf("小龙女的名字：%s, 性别：%s  年龄：%d\n", (*my_girl).name, (*my_girl).sex=='m'?"男":"女", (*my_girl).age);

	//方式2. 直接使用指针访问  ->
	printf("小龙女的名字：%s, 性别：%s  年龄：%d\n", my_girl->name, my_girl->sex=='m'?"男":"女", my_girl->age);
	system("pause");
	return 0;
}