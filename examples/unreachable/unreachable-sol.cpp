#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include<string>
#include<map>
#include<vector>
using namespace llvm;

void dfs (StringRef current
	  , std::set<StringRef>& bbList
	  , std::map<StringRef,std::set<StringRef>&>& graph) {
  
  auto search = bbList.find(current);
  if ( search != bbList.end() ) {
    bbList.erase ( search );

    auto pair = graph.find( current );
    
    if (pair != graph.end()) {
      std::set<StringRef> toBBList = pair->second;
      
      for (auto it = toBBList.begin(); it != toBBList.end(); ++it ) {
	dfs ( *it, bbList, graph );
      }
    }
    
  }
}

namespace {

class MyUnreachablePass : public PassInfoMixin<MyUnreachablePass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    StringRef funcName = F.getName();

    std::set<StringRef> allBBs;
    std::map<StringRef,std::set<StringRef>&> flowGraph;

    StringRef entry = F.getEntryBlock().getName();

    for (auto I =F.begin(); I != F.end(); ++I) {
      BasicBlock& BB = *I;

      StringRef currentBB = BB.getName();
      
      allBBs.insert(currentBB);

      unsigned successorCnt = BB.getTerminator()->getNumSuccessors();

      std::set<StringRef>* bbListPtr = new std::set<StringRef>();
      flowGraph.insert ( { currentBB, *bbListPtr } );
      
      for (unsigned i = 0; i < successorCnt; ++i) {
	bbListPtr->insert(BB.getTerminator()->getSuccessor(i)->getName());
      }
    }

    dfs ( entry, allBBs, flowGraph );

    std::set<StringRef>::const_iterator q;
    for (q = allBBs.begin(); q != allBBs.end(); q++) {
      outs() << *q << "\n";
    }

    return PreservedAnalyses::all();
  }
};
}

extern "C" ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "MyUnreachablePass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "my-unreachable") {
            FPM.addPass(MyUnreachablePass());
            return true;
          }
          return false;
        }
      );
    }
  };
}
