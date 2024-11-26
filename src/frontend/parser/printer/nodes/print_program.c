#include "../../../../../include/parser/printer/nodes/print_program.h"
#include "../../../../../include/parser/printer/visited.h"
#include "../../../../../include/ast/definitions.h"

void print_program(const AstNode *node, int depth, VisitedNodes *visited) {
  print_indent(depth + 1);
  ProgramNode *program_data = (ProgramNode *)node->data;

  if (program_data && program_data->statements) {
      printf("Program has %zu statements\n", program_data->statement_count);
      for (size_t i = 0; i < program_data->statement_count; i++) {
          print_ast_node(program_data->statements[i], depth + 1, visited);
      }
  } else {
      printf("Value: (No statements or NULL data)\n");
  }
}