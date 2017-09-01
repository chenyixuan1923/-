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
int weightmax; //���Ȩֵ��
int weight;   //��ǰʶ���ַ���Ȩֵ��

typedef enum
{
	left2right,
	right2left
}associativity;

typedef struct
{
	int  number_;//������
	int  icp;    //���ȼ�
	int  isp;    //���ȼ�
	associativity ass;   //�����
	token op;  //������
}OPERATOR;

static const OPERATOR operators[] =
{
	{ 2, 17, 1, left2right, LPRAEN },     // ������  
	{ 2, 17, 17, left2right, RPRAEN },    // ������  
	{ 2, 12, 12, left2right, OP_plus },      // ��  
	{ 2, 12, 12, left2right, OP_minus },     // ��  
	{ 2, 13, 13, left2right, OP_multiply },  // ��  
	{ 2, 13, 13, left2right, OP_divide },    // ��  
	{ 2, 13, 13, left2right, OP_mod },       // ģ  
	{ 2, 10, 10, left2right, OP_lt },        // С��  
	{ 2, 10, 10, left2right, OP_gt },        // ����  
	{ 2, 9, 9, left2right, OP_eq },          // ����  
	{ 2, 9, 9, left2right, OP_ne },          // ������  
	{ 2, 10, 10, left2right, OP_le },        // С�ڵ���
	{ 2, 10, 10, left2right, OP_ge },        // ���ڵ���  
	/* �߼����� */
	{ 2, 5, 5, left2right, OP_and },         // �� 
	{ 2, 4, 4, left2right, OP_or },          // ��  
	{ 1, 15, 15, right2left, OP_not },       // ��  
	/* ��ֵ */
	// BASIC �и�ֵ��䲻���ڱ��ʽ��  
	//{ 2, 2, 2, right2left, oper_assignment },  // ��ֵ  
	/* ��С���ȼ� */
	//{ 2, 0, 0, right2left, oper_min }      // ջ��  
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

VARTANT memory[2000];//�ڴ��������

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
