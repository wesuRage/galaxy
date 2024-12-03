#ifndef PRINT_FUNCTION_H
#define PRINT_FUNCTION_H

#include "../../../ast/definitions.h"
#include "../visited.h"


void print_function(const AstNode *node, int depth, VisitedNodes *visited);

#endif // PRINT_FUNCTION_H
