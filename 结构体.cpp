#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�ṹ�����ǳ���Ա�Զ����һ�֡��������͡�
struct student {
	char name[16];
	int  age;
	char tel[12];
};

//�ṹ������ṹ������
struct _class{
	struct student  rock;
	struct student  martin;
	struct student  zsf;
};


int main(void){
	//�ṹ��ĳ�ʼ�� 
	//��ʽһ  �����ʱ���ʼ�����е�����
	struct student rock = {"Rock", 38, "******"};

	printf("rock ������: %s  ����: %d �绰: %s\n", rock.name, rock.age, rock.tel);

	//��ʽ��  �����ʱ�����ǿ���ָ����ʼ�������� VS/VC��֧�֣���gcc ��֧�ֵ�
	//struct student s1 ={.name="������",.age = 100};  

	//��ʽ��  ������ʼ��ÿһ������
	struct student s2;
	strcpy(s2.name, "���");
	s2.age = 40;
	s2.tel[0]='\0';

	printf("���������: %s  ����: %d �绰: %s\n", s2.name, s2.age, s2.tel);

	//�ṹ���к��нṹ��
	struct _class  c1={{"Rock", 38, "******"},{"Martin", 38, "18684518289"},{"������",100,""}};

	printf("c1�� martin ͬѧ������: %s  ����: %d �绰: %s\n", c1.martin.name, c1.martin.age, c1.martin.tel);

	system("pause");
	return 0;
}