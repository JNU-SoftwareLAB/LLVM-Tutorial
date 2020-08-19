#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {

bool runBye(Function &F){
	if (F.hasName()) {
		errs() << "Bye: ";
		errs().write_escaped(F.getName()) << '\n';
	}
	return false;
}

struct LegacyBye : public FunctionPass {
	static char ID;
	LegacyBye() : FunctionPass(ID){}
	bool runOnFunction(Function &F) override { return runBye(); }
};

struct Bye : PassInfoMixin<Bye> {
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &){
		if (!runBye(F))
			return PreservedAnalyses::all();
		return PreservedAnalyses::none();
	}
};

}

/* Register Pass Legacy */
char LegacyBye::ID = 0;

static RegisterPass<LegacyBye> X("goodbye", "Good Bye World Pass",
																	false,
																	false);

/* Register Pass New */																	
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo 
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "ByePass", "v0.1",
    [](PassBuilder &PB) {
			PB.registerPipelineParsingCallback(
				[](StringRef PassName, FunctionPassManager &FPM,
					 ArrayRef<PassBuilder::PipelineElement>) { 
					if(PassName == "bye-pass"){
						FPM.addPass(Bye());
						return true;
					}
					return false;
				}
			);
		}
  };
}

/* Legacy PM Registration */
static RegisterStandardPasses RegisterBye(
		llvm::PassManagerBuilder::EP_VectorizerStart,
		[](const llvm::PassManagerBuilder &Builder,
			llvm::legacy::PassManagerBase &PM) { PM.add(new LegacyBye());});

/* New PM Registration */
llvm::PassPluginLibraryInfo getByePluginInfo(){
	return {LLVM_PLUGIN_API_VERSION, "Bye", LLVM_VERSION_STRING,
	[](PassBuilder &PB) {
		PB.registerVectorizerStartEPCallback(
			[](llvm::FunctionPassManager &PM,
				 llvm::PassBuilder::OptimizationLevel Level) {
					 PM.addPass(Bye());
				 });
		PB.registerPipelineParsingCallback(
			[](StringRef Name, llvm::FunctionPassManager &PM,
				 ArrayRef<llvm::PassBuilder::PipelineElement>){
					 if (Name == "goodbye") { 
						 PM.addPass(Bye());
						 return true;
					 }
					 return false;
				 });
	}};
}