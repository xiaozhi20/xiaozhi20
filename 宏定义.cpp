#include <stdio.h>
#include <stdlib.h>

#define  _width   1024
#define  ADDR     "中华人民共和国湖南\
省平江县"
#define MARTIN 王鹏程

#define SQUARE(x)   (x)*(x)
#define MAX(x,y)    x>y?x:y

int main(void){

	printf("width: %d\n", _width); // 宏展开相当于 printf("width: %d\n", 1024);
	printf("我的祖籍： %s\n", ADDR);
	//printf("我的名字: %s", MARTIN); // 宏展开相当于 printf("我的名字: %s", 王鹏程);

	int i = 10;
	int j = SQUARE(i);  // 宏展开  j = i*i;
	printf("j: %d\n", j);
	printf("MAX(i,j):%d\n", MAX(i, j)); //宏展开 printf("MAX(i,j):%d\n", i>j?i:j);
	int z = SQUARE(2+3);   // (2+3)*(2+3) = 25
	printf("z: %d\n", z);


	system("pause");
	return 0;
}