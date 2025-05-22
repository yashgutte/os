/*
Question 5: Write a program to create a Binary search tree and perform following non recursive operations on it.
a. Pre-order       b. Post order       c. display total nodes    d. display leaf nodes.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

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
        } else if (data > current->data) {
            current = current->right;
        } else {
            return root; // Duplicate value
        }
    }

    if (data < parent->data) {
        parent->left = createNode(data);
    } else {
        parent->right = createNode(data);
    }

    return root;
}

// Non-recursive preorder traversal using stack
void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[MAX_SIZE];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* current = stack[top--];
        printf("%d ", current->data);

        if (current->right) {
            stack[++top] = current->right;
        }
        if (current->left) {
            stack[++top] = current->left;
        }
    }
    printf("\n");
}

// Non-recursive postorder traversal using two stacks
void postorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack1[MAX_SIZE];
    struct Node* stack2[MAX_SIZE];
    int top1 = -1;
    int top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        struct Node* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left) {
            stack1[++top1] = current->left;
        }
        if (current->right) {
            stack1[++top1] = current->right;
        }
    }

    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->data);
    }
    printf("\n");
}

// Count total nodes using level order traversal
int countTotalNodes(struct Node* root) {
    if (root == NULL) return 0;

    struct Node* queue[MAX_SIZE];
    int front = 0, rear = 0;
    int count = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];
        count++;

        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }

    return count;
}

// Display leaf nodes using level order traversal
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[MAX_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("Leaf nodes: ");
    while (front < rear) {
        struct Node* current = queue[front++];

        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }

        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }
    printf("\n");
}

void displayMenu() {
    printf("\nBST Non-recursive Operations Menu:\n");
    printf("1. Insert a number\n");
    printf("2. Pre-order traversal\n");
    printf("3. Post-order traversal\n");
    printf("4. Display total nodes\n");
    printf("5. Display leaf nodes\n");
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
                printf("Enter number to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Number inserted successfully\n");
                break;

            case 2:
                printf("Pre-order traversal: ");
                preorderTraversal(root);
                break;

            case 3:
                printf("Post-order traversal: ");
                postorderTraversal(root);
                break;

            case 4:
                printf("Total number of nodes: %d\n", countTotalNodes(root));
                break;

            case 5:
                displayLeafNodes(root);
                break;

            case 6:
                printf("Exiting program\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
} 