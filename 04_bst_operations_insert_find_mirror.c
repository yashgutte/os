/*
Question 4: Write a program to illustrate operations on BST holding numeric keys.
The menu must include insert, find, mirror image.
*/

#include <stdio.h>
#include <stdlib.h>

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

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

struct Node* find(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return find(root->left, data);
    }

    return find(root->right, data);
}

void mirror(struct Node* root) {
    if (root == NULL) {
        return;
    }

    // Swap left and right subtrees
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively mirror left and right subtrees
    mirror(root->left);
    mirror(root->right);
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void displayMenu() {
    printf("\nBST Operations Menu:\n");
    printf("1. Insert a number\n");
    printf("2. Find a number\n");
    printf("3. Create mirror image\n");
    printf("4. Display tree (inorder)\n");
    printf("5. Exit\n");
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
                printf("Enter number to find: ");
                scanf("%d", &data);
                struct Node* found = find(root, data);
                if (found) {
                    printf("Number %d found in the tree\n", data);
                } else {
                    printf("Number %d not found in the tree\n", data);
                }
                break;

            case 3:
                mirror(root);
                printf("Mirror image created successfully\n");
                printf("Tree after mirroring (inorder): ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 4:
                printf("Tree contents (inorder): ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 5:
                printf("Exiting program\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
} 