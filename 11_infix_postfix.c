/*
Question 11: Implement Infix to postfix conversion and evaluate using stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure for stack
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

// Function to check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to check if stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Function to push an item to stack
void push(struct Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// Function to pop an item from stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack->items[stack->top--];
}

// Function to peek at top item of stack
char peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        return '\0';
    }
    return stack->items[stack->top];
}

// Function to check if character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to get precedence of operator
int getPrecedence(char ch) {
    switch (ch) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Function to convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack();
    int i, j = 0;
    
    for (i = 0; infix[i]; i++) {
        // If character is operand, add to output
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        }
        // If character is '(', push to stack
        else if (infix[i] == '(') {
            push(stack, infix[i]);
        }
        // If character is ')', pop and output until '(' is found
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) == '(') {
                pop(stack); // Remove '(' from stack
            }
        }
        // If character is operator
        else if (isOperator(infix[i])) {
            while (!isEmpty(stack) && peek(stack) != '(' && 
                   getPrecedence(peek(stack)) >= getPrecedence(infix[i])) {
                postfix[j++] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }
    
    // Pop all remaining operators from stack
    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
    }
    
    postfix[j] = '\0';
    free(stack);
}

// Function to evaluate postfix expression
int evaluatePostfix(char* postfix) {
    struct Stack* stack = createStack();
    int i;
    
    for (i = 0; postfix[i]; i++) {
        // If character is digit, push to stack
        if (isdigit(postfix[i])) {
            push(stack, postfix[i] - '0');
        }
        // If character is operator, pop two operands and perform operation
        else if (isOperator(postfix[i])) {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            
            switch (postfix[i]) {
                case '+': push(stack, operand1 + operand2); break;
                case '-': push(stack, operand1 - operand2); break;
                case '*': push(stack, operand1 * operand2); break;
                case '/': push(stack, operand1 / operand2); break;
                case '^': {
                    int result = 1;
                    for (int j = 0; j < operand2; j++) {
                        result *= operand1;
                    }
                    push(stack, result);
                    break;
                }
            }
        }
    }
    
    int result = pop(stack);
    free(stack);
    return result;
}

// Function to check if infix expression is valid
int isValidInfix(char* infix) {
    struct Stack* stack = createStack();
    int i;
    
    for (i = 0; infix[i]; i++) {
        if (infix[i] == '(') {
            push(stack, infix[i]);
        }
        else if (infix[i] == ')') {
            if (isEmpty(stack)) {
                free(stack);
                return 0;
            }
            pop(stack);
        }
    }
    
    int valid = isEmpty(stack);
    free(stack);
    return valid;
}

void displayMenu() {
    printf("\nInfix to Postfix Operations:\n");
    printf("1. Convert Infix to Postfix\n");
    printf("2. Evaluate Postfix Expression\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    int choice;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                fgets(infix, MAX_SIZE, stdin);
                infix[strcspn(infix, "\n")] = 0; // Remove newline
                
                if (!isValidInfix(infix)) {
                    printf("Invalid infix expression\n");
                    break;
                }
                
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;
                
            case 2:
                printf("Enter postfix expression: ");
                fgets(postfix, MAX_SIZE, stdin);
                postfix[strcspn(postfix, "\n")] = 0; // Remove newline
                
                printf("Result: %d\n", evaluatePostfix(postfix));
                break;
                
            case 3:
                printf("Exiting program\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
} 