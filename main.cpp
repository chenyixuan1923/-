#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include "token.h"
using namespace std;

#define stack_size 500

token get_token();
char hang_[20];
char c_;
int weightmax; //最高权值。
int weight;   //当前识别字符的权值。

typedef enum
{
	left2right,
	right2left
}associativity;

typedef struct
{
	int  number_;//操作数
	int  icp;    //优先级
	int  isp;    //优先级
	associativity ass;   //结合性
	token op;  //操作符
}OPERATOR;

static const OPERATOR operators[] =
{
	{ 2, 17, 1, left2right, LPRAEN },     // 左括号  
	{ 2, 17, 17, left2right, RPRAEN },    // 右括号  
	{ 2, 12, 12, left2right, OP_plus },      // 加  
	{ 2, 12, 12, left2right, OP_minus },     // 减  
	{ 2, 13, 13, left2right, OP_multiply },  // 乘  
	{ 2, 13, 13, left2right, OP_divide },    // 除  
	{ 2, 13, 13, left2right, OP_mod },       // 模  
	{ 2, 10, 10, left2right, OP_lt },        // 小于  
	{ 2, 10, 10, left2right, OP_gt },        // 大于  
	{ 2, 9, 9, left2right, OP_eq },          // 等于  
	{ 2, 9, 9, left2right, OP_ne },          // 不等于  
	{ 2, 10, 10, left2right, OP_le },        // 小于等于
	{ 2, 10, 10, left2right, OP_ge },        // 大于等于  
	/* 逻辑运算 */
	{ 2, 5, 5, left2right, OP_and },         // 与 
	{ 2, 4, 4, left2right, OP_or },          // 或  
	{ 1, 15, 15, right2left, OP_not },       // 非  
	/* 赋值 */
	// BASIC 中赋值语句不属于表达式！  
	//{ 2, 2, 2, right2left, oper_assignment },  // 赋值  
	/* 最小优先级 */
	//{ 2, 0, 0, right2left, oper_min }      // 栈底  
};
typedef enum
{
	var_null,
	var_double,
	var_string
}variant_type;

typedef char STRING[128];

typedef struct
{
	variant_type type;
	union{
		double i;
		STRING s;
	};
}VARTANT;

VARTANT memory[2000];//内存设多大合适

int main()
{
    freopen("in.txt", "r", stdin);
	while (feof(stdin))
	{
		weightmax = 0;
		while ((c_ = getchar()) != '\n')
		{
			ungetc(c_, stdin);
			switch (get_token())
			{
			case key_out:
			{
				weight = 4;
				if (weight > weightmax) weightmax = weight;
			}
			case key_in:
			{
				weight = 4;
				if (weight > weightmax) weightmax = weight;
			}
			case key_if:
			{
				weight = 2;
				if (weight > weightmax) weightmax = weight;
			}
			case key_else:
			{
				weight = 2;
				if (weight > weightmax) weightmax = weight;
			}
			case key_while:
			{
				weight = 3;
				if (weight > weightmax) weightmax = weight;
			}
			case key_int:
			{
				do_int();
			}
			case key_real:
			{
				weight = 1;
				if (weight > weightmax) weightmax = weight;
			}
			case key_string:
			{
				weight = 1;
				if (weight > weightmax) weightmax = weight;
			}
			}

		}
	}
	system("pause");
	return 0;
}
