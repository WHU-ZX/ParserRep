#include "ProgramAST.h"

ProgramAST::ProgramAST()
{
	this->dec_exp_ASTs = new vector<DecExpAST*>();
	this->func_define_ASTs = new vector<FuncDefineAST*>();
}

ProgramAST::~ProgramAST()
{
	for (int i = 0; i < this->dec_exp_ASTs->size(); i++)
	{
		delete this->dec_exp_ASTs->at(i);
	}
	delete this->dec_exp_ASTs;
	for (int i = 0; i < this->func_define_ASTs->size(); i++)
	{
		delete this->func_define_ASTs->at(i);
	}
	delete this->func_define_ASTs;
}

void ProgramAST::addDecExpAST(DecExpAST* ast)
{
	this->dec_exp_ASTs->push_back(ast);
}

void ProgramAST::addFuncDefineAST(FuncDefineAST* ast)
{
	this->func_define_ASTs->push_back(ast);
}

Value* ProgramAST::codegen() {

	InitializeJIT();

	InitializeModuleAndPassManager();

	if (TheModule) {
		cout << "\nAlu\n";
		cout << TheModule;
		cout << "\n";
	}

	if (TheJIT) {
		cout << "\nDeer.xl\n";
		cout << TheJIT;
		cout << "\n";
	}

	updateBB();

	for (int i = this->dec_exp_ASTs->size() - 1; i >= 0; i--)
	{
		this->dec_exp_ASTs->at(i)->codegen();
	}


	for (int i = this->func_define_ASTs->size() - 1; i >= 0; i--)
	{
		this->func_define_ASTs->at(i)->codegen();
	}
	

	auto H = TheJIT->addModule(std::move(TheModule));

	InitializeModuleAndPassManager();

	TheJIT->removeModule(H);

	return nullptr;

}
