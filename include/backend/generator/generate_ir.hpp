#ifndef GENERATE_IR_H
#define GENERATE_IR_H

#include <vector>
extern "C" {
  #include "frontend/ast/definitions.h"
}
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

std::vector<llvm::Value*> generate_ir(AstNode *node, llvm::LLVMContext &Context, llvm::Module &Module, llvm::IRBuilder<> &Builder);

#endif // GENERATE_IR_H