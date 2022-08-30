//这里是一组测试用例
//比如说这样
#include <stdio.h>
//这里是一个注释
int i,j;//ok
int fun(int a, float b)
{
	//ok
	int m;//ok
	if (a>b) 
		m=a;
	else 
		m=b;
	return m;
}
float x,y;