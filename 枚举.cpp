#include <stdio.h>
#include <stdlib.h>

//��һ�֣�����ö�ٶ��巽ʽ
enum Season{
	Spring = 0,  //0
	Summer,  //1
	Autumn,  //2
	Winter=100   //3
};

/*
enum Season{
	Spring,  //0
	Summer,  //1
	Autumn,  //2
	Winter   //3
}s;  //�ڶ��ֶ��巽ʽ�� ����ö������ʱֱ�Ӷ������
*/

//�����ֶ��巽ʽ��ʡ��ö�ٵ�����
/*enum {
	Spring = 0,  //0
	Summer = 3,  //1
	Autumn,  //2
	Winter   //3
}s, s1; 
*/
int main(void){

	enum Season s;//ʹ��ö�����Ͷ���

	s = Spring;

	//s = 0;  ���ܰ�����ֱ�Ӹ�ֵ��ö�ٱ���
	//s = (enum Season)4;  ǿ������ת�����з��գ����ܳ������ķ�Χ
	enum Season s1;
	s1 = Winter;

	if(s1 == Winter){
		printf("��ǰ�����Ƕ���\n");
	}

	printf("s: %d s1: %d\n", s, s1);
	printf("sizeof(enum Season): %d\n", sizeof(enum Season));
	
	system("pause");
	return 0;
}