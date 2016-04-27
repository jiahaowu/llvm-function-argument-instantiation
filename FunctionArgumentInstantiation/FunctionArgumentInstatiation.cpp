#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>

#include <stack>
#include <set>

using namespace llvm;

namespace {
struct FAI : public ModulePass {
    static char ID;
    FAI() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M) override;
    virtual bool runOnFunction(Function &F);
};
}

char FAI::ID = 0;
static RegisterPass<FAI> X("hello", "Function Argument Instantiation", false, false);

bool FAI::runOnModule(Module &M) {
    bool modified = false;
    std::vector<Function *> functions;
    for(Module::iterator FI = M.begin(); FI != M.end(); FI++) {
        if (!FI->isDeclaration()) {
            errs() << *FI << '\n';
            modified = runOnFunction(*FI);
        }
    }
    return modified;
}

bool FAI::runOnFunction(Function &F) {
    bool modified = false;
    int functionCallIndex = 1;
    for(Function::iterator block = F.begin(); block != F.end(); block++) {
        for(BasicBlock::iterator inst = block->begin(); inst != block->end(); inst++) {
            if(isa<CallInst>(inst)) {
                errs() << "found call #" << functionCallIndex++ << '\n';
                CallInst* callInst = dyn_cast<CallInst>(inst);
                Function *callee = callInst->getCalledFunction();

                std::set<int> constantArgs;
                int counting = 0;
                // processing caller arguments
                for (unsigned int i = 0; i < inst->getNumOperands(); ++i) {
                    if(isa<Constant>(inst->getOperand(i)) && !isa<Function>(inst->getOperand(i))) {
                        errs() << "found a constant argument\n";
                        errs() << *(inst->getOperand(i)) << '\n';
                        //constantArgs.insert(inst->getOperand(i));
                        constantArgs.insert(counting++);
                    }
                }

                if(!constantArgs.empty() && !callee->isDeclaration()) {
                    // Clone function
                    ValueToValueMapTy VMap;
                    Function* duplicateFunction = CloneFunction(callee, VMap, false);
                    duplicateFunction->setLinkage(GlobalValue::InternalLinkage);
                    callee->getParent()->getFunctionList().push_back(duplicateFunction);
                    CallInst *caller = dyn_cast<CallInst>(inst);
                    caller->setCalledFunction(duplicateFunction);
                    // step 6 Remove a formal argument from a cloned function, and add it as a local variable instead.
                    for(Function::arg_iterator arg = duplicateFunction->arg_begin(); arg != duplicateFunction->arg_end(); arg++) {
                        //errs() << 
                    }
                    modified = true;
                }

            }
        }
    }
    return modified;
}
