#pragma once
#include "AST.h"
class DecExpAST:public AST
{
public:
	int son = -1;//0 ��ʾ<var_dec>    1��ʾ  <struct_dec>

	/*c++�涨����һ����Ա����������Ϊ�麯�������������е�ͬ���������Զ���Ϊ�麯����
	��ˣ�����������������麯��ʱ�����Լӣ�Ҳ���Բ��ӣ�
	��ϰ����ÿһ����������ʱ����virtual, ʹ�������������*/
	virtual Value* codegen();
};

