#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student {
	char name[16];
	int  age;
};

int main(void){
	struct student s[2];

	printf("�������һ��ѧ����������\n");
	scanf_s("%s",s[0].name, sizeof(s[0].name));
	printf("�������һ��ѧ�������䣺\n");
	scanf("%d", &s[0].age);

	printf("��һ��ѧ��������: %s, ����: %d\n", s[0].name, s[0].age);

	//�ṹ���С���ܣ��ṹ�����֮�����ֱ�Ӹ�ֵ
	s[1] = s[0];
	memcpy(&s[1],&s[0], sizeof(struct student));
	printf("�ڶ���ѧ��������: %s, ����: %d\n", s[1].name, s[1].age);
	
	system("pause");
	return 0;
}