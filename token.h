#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
using namespace std;
int p_ = 0;
typedef enum token_types {
	DELIMITER,//标示分隔符; | +-
	IDENTIFIER,//标示ID标示符 var hello
	KEYWORD,//关键字
	SSTRING,//字符串
	CHARACTOR,//字符
	NUMBER,//数字常量
	TYPE,//类型 typedef int int32;那么int32就被标示为TYPE

	PRECOMPILE,//预编译行 #define
	TEMP,//保留
	SEMICOLON,//分号。
	COMMA,  //逗号
	ASSIGNOP,//赋值

	SCANEOF,  //文件结尾标记

	LPRAEN,   //左括号
	RPRAEN,   //右括号
	LBLOCK,//块标志 {
	RBLOCK,//块标志 }

	INTLITERAL, //没懂啥意思

	/* 算数运算 */
	OP_plus,  //加
	OP_minus, //减
	OP_multiply,//乘
	OP_divide,//除
	OP_mod,//模

	/* 关系运算 */
	OP_lt,            // 小于
	OP_gt,            // 大于
	OP_eq,            // 等于
	OP_le,            // 小于等于
	OP_ge,            // 大于等于
	OP_ne,            // 不等于

	/* 逻辑运算 */
	OP_and,           // 与
	OP_or,            // 或
	OP_not,           // 非

	//$连接
	OP_link,

	//#删除一个字符
	OP_delete,

	key_in,  // INPUT  
	key_out,      // PRINT  
	key_while,      // WHILE   
	key_if,         // IF  
	key_else,       // ELSE
	key_int,     //int
	key_real,     //实数
	key_string   //字符串


} token;

char token_buffer[100];

void clear_buffer()
{
	memset(token_buffer, 0, sizeof(token_buffer));
}

void buffer_char(char ch)
{
	token_buffer[p_] = ch;
	p_++;

}
void lexical_error(char)
{
	cout << "lexical_error!" << endl;
}
token check_reserved();//不明白？为啥是token
token get_token(void)
{
	int in_char, c;
	clear_buffer();
	if (feof(stdin))
		return SCANEOF;

	while ((in_char = getchar()) != EOF)
	{
		if (isspace(in_char))
			continue;
		else if (isalpha(in_char))//判断字符ch是否为英文字母，若为英文字母，返回非0（小写字母为2，大写字母为1）。若不是字母，返回0。
		{
			buffer_char(in_char);
			for (c = getchar(); isalnum(c) || c == '_'; c = getchar())//判断字符变量c是否为字母或数字，若是则返回非零，否则返回零。
				buffer_char(c);
			ungetc(c, stdin);//将c退回到输入流。理解很重要
			return check_reserved();
		}
		else if (isdigit(in_char))
		{
			buffer_char(in_char);
			for (c = getchar(); isdigit(c); c = getchar());
			buffer_char(c);
			ungetc(c, stdin);
			return INTLITERAL;
		}
		else if (in_char == '(')
			return LPRAEN;
		else if (in_char == ')')
			return RPRAEN;
		else if (in_char == ';')
			return SEMICOLON;
		else if (in_char == ',')
			return COMMA;
		else if (in_char == '+')
			return OP_plus;
		/*	else if (in_char == ':')
		{
		ungetc(c, stdin);
		lexical_error(in_char);
		*/
		else if (in_char == '=')
		{
			c = getchar();
			if (c == '=')
				return OP_eq;
			else
			{
				ungetc(c, stdin);
				return ASSIGNOP;
			}

		}
		else if (in_char == '-')
		{
			return OP_minus;
		}
		else if (in_char == '/')
		{
			c = getchar();
			if (c == '/')
			{
				while ((in_char = getchar()) != '\n');
			}
		}
		else if (in_char == '*')
		{
			return OP_multiply;
		}
		else if (in_char == '/')
		{
			return OP_divide;
		}
		else if (in_char == '%')
		{
			return OP_mod;
		}
		else if (in_char == '<')
		{
			c = getchar();

			if (c == '=')
				return OP_le;
			else if (c == '>')
			{
				return OP_ne;
			}
			else
			{
				ungetc(c, stdin);
				return OP_lt;
			}
		}
		else if (in_char == '>')
		{
			c = getchar();
			if (c == '=')
			{
				return OP_ge;
			}
			else
			{
				ungetc(c, stdin);
				return OP_gt;
			}
		}
		else if (in_char == '&')
		{
			c = getchar();
			if (c == '&')
			{
				return OP_and;
			}
			else lexical_error(in_char);
		}
		else if (in_char == '|')
		{
			c = getchar();
			if (c == '|')
			{
				return OP_or;
			}
			else lexical_error(in_char);
		}
		else if (in_char == '!')
		{
			return OP_not;
		}
		else if (in_char == '$')
		{
			return OP_link;
		}
		else if (in_char == '#')
		{
			return OP_delete;
		}
		else lexical_error(in_char);
	}
}
token check_reserved()
{
	if (!strcmp(token_buffer, "in"))
	{
		return key_in;
	}
	else if (!strcmp(token_buffer, "out"))
	{
		return key_out;
	}
	else if (!strcmp(token_buffer, "while"))
	{
		return key_while;
	}
	else if (!strcmp(token_buffer, "if"))
	{
		return key_if;
	}
	else if (!strcmp(token_buffer, "else"))
	{
		return key_else;
	}
	else if (!strcmp(token_buffer, "int"))
	{
		return key_int;
	}
	else if (!strcmp(token_buffer, "real"))
	{
		return key_real;
	}
	else if (!strcmp(token_buffer, "string"))
	{
		return key_string;
	}
	else return IDENTIFIER;
}