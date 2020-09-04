#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "llvm/IR/SymbolTableListTraits.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"

#include <string>
#include "Analysis.h"
#include <string>

using namespace llvm;

// 문제 상황
// 코드가 너저분함
// Instructoin 에 이름이 없음.
// -instnamer 패스를 적용해서 이름을 만들어야함. => Pass Manager를 사용해야한다.
// 이렇게 해야지 Todo1이 끝날 것 같습니다.

// no Name. no String
// no name basicBlock -> then naming
// no name instruction -> then naming
int name = 0;

int alloca_i = 0;

void makeConstrations(int opcode, Instruction* instruction){
	switch(opcode){
		case Instruction::Alloca:{
			// do something.
			auto token_alloca_i = new analysis::Token("alloca-" + std::to_string(alloca_i));
			auto variable_result = new analysis::Variable("[[variable-" + std::to_string(alloca_i) + "]]");
			auto cons = new analysis::ConsBinomial(token_alloca_i, variable_result, analysis::OperatorCode::in);
			alloca_i++;
			return;
		}
		case Instruction::Load:{
			// do something.
			return;
		}
		case Instruction::Store:{
			// do something.
			return;
		}
		case Instruction::BitCast:{
			// do something.
			return;
		}
		default:
			return;
	}
}

namespace {

// https://stackoverflow.com/questions/8721115/string-representation-of-llvmtype-structure
// std::string type_str;
// llvm::raw_string_ostream rso(type_str);

bool run(Function &F){
	// Clear Tokens, Variables, Constrations
	analysis::clear();
	name = 0;
	alloca_i = 0;
	if (F.hasName()) {
		outs() << "Function: " << F.getName() << '\n';

		for (auto I = F.begin(); I != F.end(); I++){
			BasicBlock* BB = &*I;
			if (BB->getName() == ""){
				BB->setName( "%"+ std::to_string(name));
				name++;
			};
			outs() << "\tBasic Blocks: " << BB->getName() << '\n';
			
			int counter = 0;
			for(auto J = BB->begin(); J != BB->end(); J++){
				Instruction* II = &*J;
				outs() << "\t\t" << counter << " Instruction:\t" << II->getOpcodeName(); 
				for(auto K = II->op_begin(); K != II->op_end(); K++){
					Use& operand = *K;
					Value* v = K->get();
					std::string operandType = analysis::idToString(operand.get()->getType()->getTypeID());
					StringRef name = v->getName();
					outs() << "\t name:" << name << "\t operand: " << operandType;
					outs() << "\t getOperandNo" << operand.getOperandNo();
				}

				makeConstrations(II->getOpcode(), II);

			outs() << '\n';
				counter++;
			}
			counter = 0;
		}
	}

	// Run Constartions
	analysis::run();

	for (auto i : analysis::getVariables()){
		outs() << i.toStringTokens();
	}
	outs() << "\n";
	return false;
}

struct PointerCheck : public FunctionPass {
	static char ID;
	PointerCheck() : FunctionPass(ID){}
	bool runOnFunction(Function &F) override { return run(F); }
};

}

/* Register Pass Legacy */
char PointerCheck::ID = 0;

static RegisterPass<PointerCheck> X("pointer-check", "Pointer Check",
																	false,
																	false);

// cmake . -B./dest && cmake --build ./dest
// opt -load ./dest/libLLVMPointerCheck.so < > /dev/null