/*
 * @Author: iku50 wizo.o@outlook.com
 * @Date: 2022-08-29 15:12:35
 * @LastEditors: iku50 wizo.o@outlook.com
 * @LastEditTime: 2022-09-08 19:10:56
 * @FilePath: /我的坚果云/AST/test.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*这里是
样*/
#include <stdio.h>
//这里是一个注释
int i, j;
int fu(int a, int b);
int fun(int a, float b)
{
	int m;
	fu(a, b);
	if (a > b)
		fu(a, b);
	else
	{
		m = b;
	}
	while (a > b)
	{
		a = b + 1;
		for (i = 0; i < 10; i)
		{
			j = i;
		}
		if(a=1) break;
	}
	for (i = 0; i < 10; i)
		j = i;
	return m;
}
float x, y;