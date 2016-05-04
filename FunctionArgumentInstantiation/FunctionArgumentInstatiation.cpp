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
#include <llvm/Transforms/Utils/BasicBlockUtils.h>
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
            modified = runOnFunction(*FI);
            errs() << *FI << '\n';
        }
    }
    return modified;
}

bool FAI::runOnFunction(Function &F) {
    bool modified = false;
    int functionCallIndex = 1;
    for(Function::iterator block = F.begin(); block != F.end(); block++) {
        for(BasicBlock::iterator inst = block->begin(); inst != block->end();inst++) {
            Instruction * Inst = inst;
            errs() << *inst << " *****************\n";
            if(isa<CallInst>(Inst)) {
                CallInst* callInst = dyn_cast<CallInst>(Inst);
                errs() << "found call #" << functionCallIndex++ << '\n';
                Function *callee = callInst->getCalledFunction();
                ValueToValueMapTy VMap;
                if(callee->isDeclaration()) {
                    continue;
                }
                std::set<int> constantArgs;
                //Inst->eraseFromParent();
                // processing caller arguments
                Function::arg_iterator arg = callee->arg_begin();
                std::vector<Value*> Args;
                errs() <<"number of args is: " << callInst->getNumArgOperands() << "\n";
                for (unsigned int i = 0; i < callInst->getNumArgOperands(); ++i) {
                    if(isa<Constant>(callInst->getArgOperand(i))) {
                        //errs() << *(inst->getOperand(i)) << '\n';
                        errs() << "I found a constant argument index is: " << i << "\n";
                        //constantArgs.insert(inst->getOperand(i));
                        constantArgs.insert(i);
                        Constant *temp = cast<Constant>(callInst->getArgOperand(i));
                        VMap[arg] = temp;
                    }
                    else{
                        //errs() << "copy argument index: " << i << "\n";
                        Args.push_back(callInst->getArgOperand(i));
                    }
                    arg++;
                }
                //errs() << Args.size() << "\n";
                if(!constantArgs.empty() && !callee->isDeclaration()) {
                    // Clone function
                    Function* duplicateFunction = CloneFunction(callee, VMap, false);
                    duplicateFunction->setLinkage(GlobalValue::InternalLinkage);
                    callee->getParent()->getFunctionList().push_back(duplicateFunction);
                    //duplicateFunction->setLinkage(callee->getLinkage());
                    //callInst->setCalledFunction(duplicateFunction); 
                    Instruction * New;
                    New = CallInst::Create(duplicateFunction, Args, "", Inst);
                    cast<CallInst>(New)->setCallingConv(callee->getCallingConv());
                    cast<CallInst>(New)->setAttributes(callee->getAttributes());
                    if(callInst->isTailCall())cast<CallInst>(New)->setTailCall();
                    New->setDebugLoc(Inst->getDebugLoc());	
                    New->takeName(Inst);
                    //Inst->eraseFromParent();
                    Args.clear();
                    ReplaceInstWithInst(inst->getParent()->getInstList(), inst, cast<CallInst>(New));
                    //Inst->replaceAllUsesWith(New);
                    //Inst->getParent()->getInstList().insert(Inst,New);
                    //errs() << "before: " << callInst->getNumArgOperands() << "\n";
                    //Inst->eraseFromParent();
                    /*
                    CallInst * temp = dyn_cast<CallInst>(New);
                    //callee = temp->getCalledFunction();
                    errs() << "now: " << temp->getNumArgOperands() <<"\n";
                    */
                    // step 6 Remove a formal argument from a cloned function, and add it as a local variable instead.
                    /*
                    for(Function::arg_iterator arg = callee->arg_begin(); arg != callee->arg_end(); arg++) {
                        errs() <<"process argument No. " <<arg->getArgNo() << '\n';
                        // if this argument is used as constant at callsite, do the following:
                        if(constantArgs.find(arg->getArgNo()) != constantArgs.end()) {
                            errs() << "processing " << arg->getName() << '\n';
                            auto entry = duplicateFunction->begin()->begin();
                            AllocaInst *alloc = new AllocaInst(arg->getType(), arg->getName(), entry);
                            alloc->setAlignment(4);
                            Value *value = inst->getOperand(arg->getArgNo());
                            StoreInst *storeInst = new StoreInst(value, alloc, false, entry);
                            storeInst->setAlignment(4);
                            LoadInst *load = new LoadInst(alloc, "", false, entry);
                            load->setAlignment(4);
                            arg->replaceAllUsesWith(load);
                        }
                    }
                    */
                    modified = true;
                }
                //errs() << "end of a call\n";
            }
            //errs() << *inst << " next\n";
        }
    }
    return modified;
}
