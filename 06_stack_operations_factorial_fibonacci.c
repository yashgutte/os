/*
Question 6: WAP to implement following by using stack 
a. Factorial of a given number
b. Generation of Fibonacci series
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Stack implementation
struct Stack {
    int data[MAX_SIZE];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

int isFull(struct Stack* s) {
    return s->top == MAX_SIZE - 1;
}

void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++s->top] = value;
}

int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[s->top--];
}

// Factorial using stack
int factorial(int n) {
    struct Stack s;
    initStack(&s);
    int result = 1;

    // Push numbers from n to 1 onto stack
    for (int i = n; i > 0; i--) {
        push(&s, i);
    }

    // Pop and multiply
    while (!isEmpty(&s)) {
        result *= pop(&s);
    }

    return result;
}

// Fibonacci series using stack
void fibonacci(int n) {
    struct Stack s;
    initStack(&s);
    
    // Initialize first two numbers
    push(&s, 1);
    push(&s, 0);

    printf("Fibonacci series up to %d terms: ", n);
    
    for (int i = 0; i < n; i++) {
        int a = pop(&s);
        int b = pop(&s);
        
        printf("%d ", a);
        
        // Push next number and previous number
        push(&s, a);
        push(&s, a + b);
    }
    printf("\n");
}

void displayMenu() {
    printf("\nStack Operations Menu:\n");
    printf("1. Calculate factorial\n");
    printf("2. Generate Fibonacci series\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, n;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to calculate factorial: ");
                scanf("%d", &n);
                if (n < 0) {
                    printf("Factorial is not defined for negative numbers\n");
                } else {
                    printf("Factorial of %d is: %d\n", n, factorial(n));
                }
                break;

            case 2:
                printf("Enter number of terms for Fibonacci series: ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("Please enter a positive number\n");
                } else {
                    fibonacci(n);
                }
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