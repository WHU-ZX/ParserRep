#include "ClassProject.h"

LLVMContext TheContext;
std::unique_ptr<Module> TheModule;

std::map<std::string, AllocaInst*> NamedValues;
map<string, int*> testMap;
IRBuilder<> Builder(TheContext);

std::unique_ptr<KaleidoscopeJIT> TheJIT;

AllocaInst* CreateEntryBlockAlloca(Function* TheFunction,
	const std::string& VarName, zx::Type type) {
	if (type == zx::Type::INT) {
		IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
			TheFunction->getEntryBlock().begin());
		return std::move(TmpB.CreateAlloca(llvm::Type::getInt32Ty(TheContext), nullptr,
			VarName.c_str()));
	}
}

AllocaInst* CreateEntryBlockAlloca(Function* TheFunction,
	const std::string& VarName, llvm::Type* type) {
	IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
		TheFunction->getEntryBlock().begin());
	return TmpB.CreateAlloca(type, nullptr, VarName.c_str());
}

int testInt = 0;

void InitializeModule() {
	// Open a new module.
	TheModule = std::make_unique<Module>("my cool jit", TheContext);

	//Ϊ������JIT֧��
	TheModule->setDataLayout(TheJIT->getTargetMachine().createDataLayout());
}

Function* currentFun = nullptr;
FunctionType* currentFunType = nullptr;
BasicBlock* BB = nullptr;

std::unique_ptr<legacy::FunctionPassManager> TheFPM;

void InitializeModuleAndPassManager(void) {
	// Open a new module.
	TheModule = std::make_unique<Module>("my cool jit", TheContext);

	// ΪModule����JIT�����ݲ���
	TheModule->setDataLayout(TheJIT->getTargetMachine().createDataLayout());

	// Create a new pass manager attached to it.
	TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());

	// Do simple "peephole" optimizations and bit-twiddling optzns.
	TheFPM->add(createInstructionCombiningPass());
	// Reassociate expressions.
	TheFPM->add(createReassociatePass());
	// Eliminate Common SubExpressions.
	TheFPM->add(createGVNPass());
	// Simplify the control flow graph (deleting unreachable blocks, etc).
	TheFPM->add(createCFGSimplificationPass());

	TheFPM->doInitialization();
}

void InitializeJIT(void) {

	InitializeNativeTarget();
	InitializeNativeTargetAsmParser();
	InitializeNativeTargetAsmPrinter();

	TheJIT = std::make_unique<KaleidoscopeJIT>();
}

BasicBlock* updateBB()
{

	/*InitializeJIT();*/

	/*InitializeModule();*/
	/*InitializeModuleAndPassManager();*/
	

	currentFunType = FunctionType::get(llvm::Type::getVoidTy(TheContext),
		{ llvm::Type::getInt32Ty(TheContext) }, false);
	currentFun = Function::Create(currentFunType, Function::ExternalLinkage, "VarDec", *TheModule);
	BB = BasicBlock::Create(TheContext, "EntryBlock", currentFun);
	Builder.SetInsertPoint(BB);
	return BB;
}



