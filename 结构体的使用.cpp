#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student {
	char name[16];
	int  age;
};

int main(void){
	struct student  s1, s2;

	printf("�������һ��ѧ����������\n");
	scanf_s("%s",s1.name, sizeof(s1.name));
	printf("�������һ��ѧ�������䣺\n");
	scanf("%d", &s1.age);

	printf("��һ��ѧ��������: %s, ����: %d\n", s1.name, s1.age);

	//�ṹ���С���ܣ��ṹ�����֮�����ֱ�Ӹ�ֵ
	//s2 = s1;
	memcpy(&s2,&s1, sizeof(struct student));
	printf("�ڶ���ѧ��������: %s, ����: %d\n", s2.name, s2.age);
	char c1[16]={"martin"}, c2[16];
	//c2 = c1; //���鲻��ֱ�Ӹ�ֵ

	system("pause");
	return 0;
}