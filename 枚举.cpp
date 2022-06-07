#include <stdio.h>
#include <stdlib.h>

//第一种，常用枚举定义方式
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
}s;  //第二种定义方式： 定义枚举类型时直接定义变量
*/

//第三种定义方式，省略枚举的名称
/*enum {
	Spring = 0,  //0
	Summer = 3,  //1
	Autumn,  //2
	Winter   //3
}s, s1; 
*/
int main(void){

	enum Season s;//使用枚举类型定义

	s = Spring;

	//s = 0;  不能把整数直接赋值给枚举变量
	//s = (enum Season)4;  强制类型转换会有风险，可能超出表达的范围
	enum Season s1;
	s1 = Winter;

	if(s1 == Winter){
		printf("当前季节是冬天\n");
	}

	printf("s: %d s1: %d\n", s, s1);
	printf("sizeof(enum Season): %d\n", sizeof(enum Season));
	
	system("pause");
	return 0;
}