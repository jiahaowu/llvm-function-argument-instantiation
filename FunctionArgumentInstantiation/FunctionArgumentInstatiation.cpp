#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>

#include <stack>
#include <set>

using namespace llvm;

namespace {
struct FAI : public FunctionPass {
    static char ID;
    FAI() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
        bool modified = false;
        int functionCallIndex = 1;
        for(Function::iterator block = F.begin(); block != F.end(); block++) {
            for(BasicBlock::iterator inst = block->begin(); inst != block->end(); inst++) {
                if(isa<CallInst>(inst)) {
                    errs() << "found call #" << functionCallIndex++ << '\n';
                    CallInst* callInst = dyn_cast<CallInst>(inst);
                    Function *callee = callInst->getCalledFunction();
                    for(Function::arg_iterator arg = callee->arg_begin(); arg != callee->arg_end(); arg++) {
                        errs() << "==> " << *arg << ' ';
                    }
                    errs() << '\n';

                    // processing caller arguments
                    for (unsigned int i = 0; i < inst->getNumOperands(); ++i) {
                        if(isa<Constant>(inst->getOperand(i))) {
                            errs() << "found a constant argument\n";
                        } 
                    }
                }
            }
        }
        return modified;
    }
};
}

char FAI::ID = 0;
static RegisterPass<FAI> X("hello", "Function Argument Instantiation", false, false);
