#include "ExpAST.h"
#include "VarNameAST.h"

ExpAST::ExpAST(ExpAST* left, OperatorAST* operatorAST)//��Ŀ
{
	this->left = left;
	this->operatorAST= operatorAST;
	this->type = 0;
}

ExpAST::ExpAST(ExpAST* left, ExpAST* right, OperatorAST* operatorAST)//˫Ŀ
{
	this->left = left;
	this->right = right;
	this->operatorAST = operatorAST;
	this->type = 1;
}

void ExpAST::setStructName(string name)
{
	this->structName = name;
}

ExpAST::ExpAST(ValAST* valAST)//<val>
{
	this->valAST = valAST;
	this->type = 2;
}

ExpAST::ExpAST(VarNameAST* varNameAST)//<var_name>
{
	this->varNameAST = varNameAST;
	this->type = 3;
}

ExpAST::ExpAST(FuncCallStmtAST* funcCallStmtAST)
{
	this->funcCallStmtAST = funcCallStmtAST;
	this->type = 4;
}

void ExpAST::setType(zx::Type expType)
{
	this->expType = expType;
}

void ExpAST::setFinalToType(zx::Type type)
{
	this->finalToType = type;
}

void ExpAST::setPointerNum(int num)
{
	this->pointerNum = num;
}

ExpAST::~ExpAST()
{
	if (this->left != nullptr)
	{
		this->left = left;
	}
	if (this->right != nullptr)
	{
		this->right = right;
	}
	if (this->valAST != nullptr)
	{
		this->valAST = valAST;
	}
	if (this->varNameAST != nullptr)
	{
		this->varNameAST = varNameAST;
	}
	if (this->operatorAST != nullptr)
	{
		delete this->operatorAST;
	}
	if (this->funcCallStmtAST != nullptr)
	{
		delete this->funcCallStmtAST;
	}
}

Value* ExpAST::codegen() {
	Value* LVar;
	Value* RVar;
	Value* Val;
	AllocaInst* allo;
	ConstantFP* LVarV;
	bool BothIsInterger;
	if (left != NULL) {
		LVar = left->codegen();
	}
	if (right != NULL) {
		RVar = right->codegen();
	}
	switch (type)
	{
	case 0:
		break;
	case 1:
		switch (operatorAST->op)
		{
		case Op::ADD:
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateAdd(LVar, RVar);
				Val->print(errs());
				std::cout << "\n";
				return Val;
			}
			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFAdd(LVar, RVar);
			Val->print(errs());
			std::cout << "\n";
			return Val;
		case Op::MINUS:
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateSub(LVar, RVar);
				Val->print(errs());
				cout << "\n";
				return Val;
			}
			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFSub(LVar, RVar);
			Val->print(errs());
			cout << "\n";
			return Val;
		case Op::STAR:
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateMul(LVar, RVar);
				Val->print(errs());
				cout << "\n";
				return Val;
			}
			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}


			//���ڳ˷��ͳ�����Val�����errs()��ʱ����ʮ����������16λ16������
			//��IEEE��������׼���㣨��ϵͳ�����������д�ķ����������������16����������������ȷ���
			//���廻���Ѿ�д����IEEEConvert��Ŀ
			Val = Builder.CreateFMul(LVar, RVar, "multmp");
			Val->print(errs());
			cout << "\n";
			return Val;
		case Op::DIVIDE://�����������int���ͣ�ҲҪת����

			BothIsInterger = true;

			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}

			Val = Builder.CreateFDiv(LVar, RVar);
			Val->print(errs());
			cout << "\n";

			//���ڳ˷��ͳ�����Val�����errs()��ʱ����ʮ����������16λ16������
			//��IEEE��������׼���㣨��ϵͳ�����������д�ķ����������������16����������������ȷ���
			//���廻���Ѿ�д����IEEEConvert��Ŀ
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				Val = Builder.CreateFPToSI(Val, IntegerType::get(TheContext, 32));
				Val->print(errs());
				cout << "\n";
			}
			return Val;
		case Op::MORE:
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				//Val = Builder.CreateMul(LVar, RVar);
				//Val = Builder.CreateICm
				//Val->print(errs());
				Val = Builder.CreateICmpSGT(LVar, RVar);
				Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
				cout << "\n";
				return Val;
			}
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFCmpUGT(LVar, RVar);

			break;
		case Op::MOREOREQ:
			break;
		case Op::LESS:
			break;
		case Op::LESSOREQ:
			break;
		case Op::EQ:
			break;
		case Op::NEQ:
			break;
		case Op::AND:
			break;
		case Op::OR:
			break;
		case Op::NOT:
			break;
		default:
			break;
		}
		break;
	case 2:
		return valAST->codegen();
	case 3:
		/*return NamedValues[varNameAST->codegenStr()];*/
		allo = NamedValues[varNameAST->codegenStr()];
		Val = Builder.CreateLoad(allo);
		Val->print(errs());
		cout << "\n";
		return Val;
		break;
	default:
		break;
	}
	return nullptr;
}

string ExpAST::codegenStr() {
	switch (type)
	{
	case 3:
		return varNameAST->codegenStr();

	default:
		break;
	}
}