#ifndef GENERATE_UNARY_BITWISE_NOT_H
#define GENERATE_UNARY_BITWISE_NOT_H

extern "C" {
  #include "frontend/ast/definitions.h"
}
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

llvm::Value *generate_unary_bitwise_not(UnaryBitwiseNotExpr *node, llvm::LLVMContext &Context, llvm::IRBuilder<> &Builder, llvm::Module &Module);

#endif // GENERATE_UNARY_BITWISE_NOT_H