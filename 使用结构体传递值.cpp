#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct programer{
	char  name[32];
	int   age;
	int   salary; 
};

//�β��ǽṹ�������ֵ����
struct programer add_salary(struct programer p, int num){
	p.salary += num;
	return p;
}

//�β�ʹ�ýṹ��ָ��
void add_salary1(struct programer *p, int num){
	if(!p) return ;
	p->salary += num;
}

//�β�ʹ������
void add_salary2(struct programer &p, int num){
	
	p.salary += num;
}

//�β��ǽṹ�������ֵ����,��������
struct programer& add_salary3(struct programer p, int num){
	p.salary += num;
	return p;
}

int main(void){
	struct programer xiaoniu;

	strcpy(xiaoniu.name, "Сţ");
	xiaoniu.age = 28;
	xiaoniu.salary = 20000;

	//�ṹ�������Ϊ������ֵ��ֵ����,��int �Ȼ�������һ��
	 //xiaoniu = add_salary(xiaoniu, 5000);

	//ָ�봫ֵ
	//add_salary1(&xiaoniu, 5000);

	//���ô�ֵ
	//add_salary2(xiaoniu, 10000);

	 //��������
	 xiaoniu = add_salary3(xiaoniu, 20000);

	printf("������ %s, ����: %d, нˮ: %d\n", xiaoniu.name, xiaoniu.age, xiaoniu.salary);

	system("pause");
	return 0;
}