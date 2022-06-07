#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

//学生管理系统  比如：学生信息（学号，姓名，班级，电话，年龄）
struct student{
	char no[64];
	char name[64];
	int  class_no;
	char tel[16];
	int  age;
};


int main(void){
	/*char no[54][64];
	char name[54][64];
	int  class_no[54];
	char tel[54][16];
	int  age[54];

	char no2[64];
	char name2[64];
	int  class_no2;
	char tel2[16];
	int  age2;
	*/
	struct student martin;

	printf(".......\n");

	system("pause");
	return 0;
}