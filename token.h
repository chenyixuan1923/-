#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
using namespace std;
int p_ = 0;
typedef enum token_types {
	DELIMITER,//��ʾ�ָ���; | +-
	IDENTIFIER,//��ʾID��ʾ�� var hello
	KEYWORD,//�ؼ���
	SSTRING,//�ַ���
	CHARACTOR,//�ַ�
	NUMBER,//���ֳ���
	TYPE,//���� typedef int int32;��ôint32�ͱ���ʾΪTYPE

	PRECOMPILE,//Ԥ������ #define
	TEMP,//����
	SEMICOLON,//�ֺš�
	COMMA,  //����
	ASSIGNOP,//��ֵ

	SCANEOF,  //�ļ���β���

	LPRAEN,   //������
	RPRAEN,   //������
	LBLOCK,//���־ {
	RBLOCK,//���־ }

	INTLITERAL, //û��ɶ��˼

	/* �������� */
	OP_plus,  //��
	OP_minus, //��
	OP_multiply,//��
	OP_divide,//��
	OP_mod,//ģ

	/* ��ϵ���� */
	OP_lt,            // С��
	OP_gt,            // ����
	OP_eq,            // ����
	OP_le,            // С�ڵ���
	OP_ge,            // ���ڵ���
	OP_ne,            // ������

	/* �߼����� */
	OP_and,           // ��
	OP_or,            // ��
	OP_not,           // ��

	//$����
	OP_link,

	//#ɾ��һ���ַ�
	OP_delete,

	key_in,  // INPUT  
	key_out,      // PRINT  
	key_while,      // WHILE   
	key_if,         // IF  
	key_else,       // ELSE
	key_int,     //int
	key_real,     //ʵ��
	key_string   //�ַ���


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
token check_reserved();//�����ף�Ϊɶ��token
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
		else if (isalpha(in_char))//�ж��ַ�ch�Ƿ�ΪӢ����ĸ����ΪӢ����ĸ�����ط�0��Сд��ĸΪ2����д��ĸΪ1������������ĸ������0��
		{
			buffer_char(in_char);
			for (c = getchar(); isalnum(c) || c == '_'; c = getchar())//�ж��ַ�����c�Ƿ�Ϊ��ĸ�����֣������򷵻ط��㣬���򷵻��㡣
				buffer_char(c);
			ungetc(c, stdin);//��c�˻ص���������������Ҫ
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