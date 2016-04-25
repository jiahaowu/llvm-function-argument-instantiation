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
        return modified;
    }
};
}

char FAI::ID = 0;
static RegisterPass<FAI> X("hello", "Function Argument Instantiation", false, false);
