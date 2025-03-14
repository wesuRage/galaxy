#include "frontend/parser/printer/nodes/expressions/print_assignment.h"
#include "frontend/parser/printer/visited.h"
#include "frontend/ast/definitions.h"
#include "frontend/parser/printer/print_indent.h"
#include "frontend/parser/printer/print_ast.h"

void print_assignment(const AstNode *node, int depth, VisitedNodes *visited)
{
  AssignmentNode *assignment_data = (AssignmentNode *)node->data;

  if (assignment_data)
  {
    print_indent(depth + 1);
    printf("Left:\n");

    if (assignment_data->left)
    {
      print_ast_node(assignment_data->left, depth + 2, visited);
    }
    else
    {
      print_indent(depth + 2);
      printf("Left is NULL\n");
    }

    print_indent(depth + 1);
    printf("Value:\n");

    if (assignment_data->value)
    {
      print_ast_node(assignment_data->value, depth + 2, visited);
    }
    else
    {
      print_indent(depth + 2);
      printf("Value is NULL\n");
    }
  }
  else
  {
    print_indent(depth + 1);
    printf("Assignment data is NULL\n");
  }
}