#include <ctype.h>
#include <stdbool.h>
#include "tailored_stack.h"

void store_command_line_args_in_stack(int, char **, Stack *cont);
bool is_correct_prefix_expression(Stack *const);
Value evaluate_expression(Stack *const);
