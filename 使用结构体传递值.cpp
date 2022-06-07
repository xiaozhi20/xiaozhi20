#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct programer{
	char  name[32];
	int   age;
	int   salary; 
};

//形参是结构体变量，值传递
struct programer add_salary(struct programer p, int num){
	p.salary += num;
	return p;
}

//形参使用结构体指针
void add_salary1(struct programer *p, int num){
	if(!p) return ;
	p->salary += num;
}

//形参使用引用
void add_salary2(struct programer &p, int num){
	
	p.salary += num;
}

//形参是结构体变量，值传递,返回引用
struct programer& add_salary3(struct programer p, int num){
	p.salary += num;
	return p;
}

int main(void){
	struct programer xiaoniu;

	strcpy(xiaoniu.name, "小牛");
	xiaoniu.age = 28;
	xiaoniu.salary = 20000;

	//结构体变量做为参数传值是值传递,和int 等基本类型一样
	 //xiaoniu = add_salary(xiaoniu, 5000);

	//指针传值
	//add_salary1(&xiaoniu, 5000);

	//引用传值
	//add_salary2(xiaoniu, 10000);

	 //返回引用
	 xiaoniu = add_salary3(xiaoniu, 20000);

	printf("姓名： %s, 年龄: %d, 薪水: %d\n", xiaoniu.name, xiaoniu.age, xiaoniu.salary);

	system("pause");
	return 0;
}