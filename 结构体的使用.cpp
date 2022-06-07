#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student {
	char name[16];
	int  age;
};

int main(void){
	struct student  s1, s2;

	printf("请输入第一个学生的姓名：\n");
	scanf_s("%s",s1.name, sizeof(s1.name));
	printf("请输入第一个学生的年龄：\n");
	scanf("%d", &s1.age);

	printf("第一个学生的姓名: %s, 年龄: %d\n", s1.name, s1.age);

	//结构体的小秘密，结构体变量之间可以直接赋值
	//s2 = s1;
	memcpy(&s2,&s1, sizeof(struct student));
	printf("第二个学生的姓名: %s, 年龄: %d\n", s2.name, s2.age);
	char c1[16]={"martin"}, c2[16];
	//c2 = c1; //数组不能直接赋值

	system("pause");
	return 0;
}