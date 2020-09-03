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

using namespace llvm;


std::string idToString(int id){
	switch(id){
		case 0: return "VoidTy";
						break;
		case 1: return "HalfTy";
						break;
		case 2: return "FloatTy";
						break;
		case 3: return "DoubleTy";
						break;
		case 4: return "X86_FP80Ty";
						break;
		case 5: return "FP128Ty";
						break;
		case 6: return "PPC_FP128Ty";
						break;
		case 7: return "LabelTy";
						break;
		case 8: return "MetadataTy";
						break;
		case 9: return "X86_MMXTy";
						break;
		case 10: return "TokenTy";
						break;
		case 11: return "IntegerTy";
						break;
		case 12: return "FunctionTy";
						break;
		case 13: return "StructTy";
						break;
		case 14: return "ArrayTy";
						break;
		case 15: return "PointerTy";
						break;
		case 16: return "VectorTy";
	}
	return "Unknown Type";
}

namespace {

bool run(Function &F){
    if (F.hasName()){
        outs() << "Function: " << F.getName() << '\n';

        for (auto I = F.begin(); I != F.end(); I++){
            BasicBlock& BB = *I;
            outs() << "\t" << "Basic Blocks: " << BB.getName() << '\n';

            int counter = 0;
            for(auto J = BB.begin(); J != BB.end(); J++){
                Instruction& II = *J;
                outs() << "\t\t" << counter << " Instruction:\t" << II.getOpcodeName();

                for(auto K = II.op_begin(); K != II.op_end(); K++){
                    Use& operand = *K;
                    std::string operandType = idToString(operand.get()->getType()->getTypeID());
                    
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

char PointerCheck::ID = 0;

static RegisterPass<PointerCheck> X("print-operand", "print operand",
                                                    false,
                                                    false);

// cmake . -B./dest && cmake --build ./dest
// opt -load ./dest/libLLVMPrintOperandType