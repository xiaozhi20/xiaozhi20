#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _friend{
	char name[32];
	char sex; // m - ��  f - Ů
	int  age;
};

int main(void){
	struct _friend girl = {"С��Ů", 'f', 18};

	struct _friend *my_girl = &girl;

	printf("С��Ů�����֣�%s, �Ա�%s  ���䣺%d\n", girl.name, girl.sex=='m'?"��":"Ů", girl.age);

	//ָ����ʽṹ������ĳ�Ա�������ַ�ʽ
	//��ʽ1. ֱ�ӽ���
	printf("С��Ů�����֣�%s, �Ա�%s  ���䣺%d\n", (*my_girl).name, (*my_girl).sex=='m'?"��":"Ů", (*my_girl).age);

	//��ʽ2. ֱ��ʹ��ָ�����  ->
	printf("С��Ů�����֣�%s, �Ա�%s  ���䣺%d\n", my_girl->name, my_girl->sex=='m'?"��":"Ů", my_girl->age);
	system("pause");
	return 0;
}