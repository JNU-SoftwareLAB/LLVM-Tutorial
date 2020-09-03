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

namespace {

// https://stackoverflow.com/questions/8721115/string-representation-of-llvmtype-structure
// std::string type_str;
// llvm::raw_string_ostream rso(type_str);

bool run(Function &F){
	if (F.hasName()) {
		outs() << "Function: " << F.getName() << '\n';

		for (auto I = F.begin(); I != F.end(); I++){
			BasicBlock& BB = *I;
			outs() << "\tBasic Blocks: " << BB.getName() << '\n';
			
			int counter = 0;
			for(auto J = BB.begin(); J != BB.end(); J++){
				Instruction& II = *J;
				outs() << "\t\t" << counter << " Instruction:\t" << II.getOpcodeName(); 

				for(auto K = II.op_begin(); K != II.op_end(); K++){
					Use& operand = *K;
					std::string operandType = analysis::idToString(operand.get()->getType()->getTypeID());
					outs() << "\t operand: " << operandType;
				}

			outs() << '\n';
				counter++;
			}
			counter = 0;
		}
	}
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