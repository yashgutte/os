/*
Question 16: Create a Binary search tree and perform following non recursive operations:
a. In order       b. Post order       c. display total nodes    d. display leaf nodes
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure for tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure for stack node
struct StackNode {
    struct Node* node;
    struct StackNode* next;
};

// Structure for stack
struct Stack {
    struct StackNode* top;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new stack node
struct StackNode* createStackNode(struct Node* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to push a node onto stack
void push(struct Stack* stack, struct Node* node) {
    struct StackNode* newNode = createStackNode(node);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a node from stack
struct Node* pop(struct Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    
    struct StackNode* temp = stack->top;
    struct Node* node = temp->node;
    
    stack->top = stack->top->next;
    free(temp);
    
    return node;
}

// Function to check if stack is empty
int isStackEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to insert a node into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    struct Node* current = root;
    struct Node* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (data < parent->data) {
        parent->left = createNode(data);
    } else {
        parent->right = createNode(data);
    }
    
    return root;
}

// Function to perform non-recursive inorder traversal
void inorderTraversal(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    struct Stack* stack = createStack();
    struct Node* current = root;
    
    printf("Inorder Traversal: ");
    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
    
    free(stack);
}

// Function to perform non-recursive postorder traversal
void postorderTraversal(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    struct Stack* stack1 = createStack();
    struct Stack* stack2 = createStack();
    
    push(stack1, root);
    
    while (!isStackEmpty(stack1)) {
        struct Node* current = pop(stack1);
        push(stack2, current);
        
        if (current->left) {
            push(stack1, current->left);
        }
        if (current->right) {
            push(stack1, current->right);
        }
    }
    
    printf("Postorder Traversal: ");
    while (!isStackEmpty(stack2)) {
        struct Node* current = pop(stack2);
        printf("%d ", current->data);
    }
    printf("\n");
    
    free(stack1);
    free(stack2);
}

// Function to count total nodes non-recursively
int countTotalNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    struct Stack* stack = createStack();
    push(stack, root);
    int count = 0;
    
    while (!isStackEmpty(stack)) {
        struct Node* current = pop(stack);
        count++;
        
        if (current->right) {
            push(stack, current->right);
        }
        if (current->left) {
            push(stack, current->left);
        }
    }
    
    free(stack);
    return count;
}

// Function to display leaf nodes non-recursively
void displayLeafNodes(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    struct Stack* stack = createStack();
    push(stack, root);
    
    printf("Leaf Nodes: ");
    while (!isStackEmpty(stack)) {
        struct Node* current = pop(stack);
        
        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }
        
        if (current->right) {
            push(stack, current->right);
        }
        if (current->left) {
            push(stack, current->left);
        }
    }
    printf("\n");
    
    free(stack);
}

// Function to free memory allocated for tree
void freeTree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    
    struct Stack* stack = createStack();
    push(stack, root);
    
    while (!isStackEmpty(stack)) {
        struct Node* current = pop(stack);
        
        if (current->right) {
            push(stack, current->right);
        }
        if (current->left) {
            push(stack, current->left);
        }
        
        free(current);
    }
    
    free(stack);
}

void displayMenu() {
    printf("\nBST Operations:\n");
    printf("1. Insert a node\n");
    printf("2. Inorder Traversal\n");
    printf("3. Postorder Traversal\n");
    printf("4. Display Total Nodes\n");
    printf("5. Display Leaf Nodes\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, data;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Node inserted successfully\n");
                break;
                
            case 2:
                inorderTraversal(root);
                break;
                
            case 3:
                postorderTraversal(root);
                break;
                
            case 4:
                printf("Total number of nodes: %d\n", countTotalNodes(root));
                break;
                
            case 5:
                displayLeafNodes(root);
                break;
                
            case 6:
                freeTree(root);
                printf("Exiting program\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
} 