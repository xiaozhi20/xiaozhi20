#include <stdio.h>
#include <stdlib.h>

#define  _width   1024
#define  ADDR     "�л����񹲺͹�����\
ʡƽ����"
#define MARTIN ������

#define SQUARE(x)   (x)*(x)
#define MAX(x,y)    x>y?x:y

int main(void){

	printf("width: %d\n", _width); // ��չ���൱�� printf("width: %d\n", 1024);
	printf("�ҵ��漮�� %s\n", ADDR);
	//printf("�ҵ�����: %s", MARTIN); // ��չ���൱�� printf("�ҵ�����: %s", ������);

	int i = 10;
	int j = SQUARE(i);  // ��չ��  j = i*i;
	printf("j: %d\n", j);
	printf("MAX(i,j):%d\n", MAX(i, j)); //��չ�� printf("MAX(i,j):%d\n", i>j?i:j);
	int z = SQUARE(2+3);   // (2+3)*(2+3) = 25
	printf("z: %d\n", z);


	system("pause");
	return 0;
}