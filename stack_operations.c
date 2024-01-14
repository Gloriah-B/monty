#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
/**
 * struct Stack - Stack data structure
 * @stack: Array representing the stack
 * @top: Index of the top element in the stack
 */
typedef struct Stack {
    int stack[STACK_SIZE];
    int top;
} Stack;
/**
 * push - Pushes an element onto the stack.
 * @stack: Pointer to the stack structure.
 * @value: The integer to be pushed onto the stack.
 * @line_number: The line number in the file.
 *
 * Description: This function pushes an integer value onto the stack.
 * If the value is not an integer or if no argument is given to push,
 * it prints an error message and exits with EXIT_FAILURE.
 */
void push(Stack *stack, const char *value, int line_number);
/**
 * pall - Prints all values on the stack.
 * @stack: Pointer to the stack structure.
 *
 * Description: This function prints all the integer values on the stack,
 * starting from the top of the stack. If the stack is empty,
 * it does not print anything.
 */
void pall(const Stack *stack);
int process_file(Stack *stack, const char *filename);
int main(int argc, char *argv[]);

void push(Stack *stack, const char *value, int line_number) {
    if (!value || *value == '\0') {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    char *endptr;
    long int num = strtol(value, &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    stack->top++;
    stack->stack[stack->top] = (int)num;
}

void pall(const Stack *stack) {
    int i;

    for (i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->stack[i]);
    }
}

int process_file(Stack *stack, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char opcode[256];
    char value[256];
    int line_number = 1;

    while (fscanf(file, "%s", opcode) != EOF) {
        if (strcmp(opcode, "push") == 0) {
            if (fscanf(file, "%s", value) != 1) {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                fclose(file);
                return EXIT_FAILURE;
            }
            push(stack, value, line_number);
        } else if (strcmp(opcode, "pall") == 0) {
            pall(stack);
        }

        line_number++;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Stack stack;
    stack.top = -1;

    if (process_file(&stack, argv[1]) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
