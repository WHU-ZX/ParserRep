#include "AssignStmtAST.h"


AssignStmtAST::AssignStmtAST(VarNameAST* varNameAST, OperatorAST* operatorAST)//type = 0 
{
	this->type = 0;
	this->varNameAST = varNameAST;
	this->operatorAST = operatorAST;
}

AssignStmtAST::AssignStmtAST(VarNameAST* varNameAST, ExpAST* expAST)//type = 1
{
	this->type = 1;
	this->varNameAST = varNameAST;
	this->expAST = expAST;
}
Value* AssignStmtAST::codegen()
{
	Value* a;
	Value* b;
	Value* Val;
	switch (type)
	{
	case 1:
		a = varNameAST->codegen();
		b = expAST->codegen();
		if (a->getType() == b->getType()->getPointerTo()) {
			Val = Builder.CreateStore(b, a);
			Val->print(errs());
			cout << "\n";
		}
		return Val;
		break;
	default:
		break;
	}
	return nullptr;
}

AssignStmtAST::~AssignStmtAST()
{
	if (this->expAST != nullptr)
	{
		delete this->expAST;
	}
	if (this->varNameAST != nullptr)
	{
		delete this->varNameAST;
	}
	if (this->operatorAST != nullptr)
	{
		delete this->operatorAST;
	}
}