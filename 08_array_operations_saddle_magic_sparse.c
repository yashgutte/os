/*
Question 8: Implement following problems based on arrays
a) i/p  {2,2,3,4} o/p 1
b) find the address of the array
c) Find saddle point in matrix     
d) Magic Square(check)
e) Represent given matrix in its sparse form
*/

#include <stdio.h>
#include <stdlib.h>

// Function to find missing number in array
int findMissingNumber(int arr[], int n) {
    int total = (n + 1) * (n + 2) / 2;
    for (int i = 0; i < n; i++) {
        total -= arr[i];
    }
    return total;
}

// Function to find saddle point in matrix
void findSaddlePoint(int matrix[][100], int rows, int cols) {
    int found = 0;
    
    for (int i = 0; i < rows; i++) {
        int min_row = matrix[i][0];
        int col_ind = 0;
        
        // Find minimum element in row
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] < min_row) {
                min_row = matrix[i][j];
                col_ind = j;
            }
        }
        
        // Check if this minimum is maximum in its column
        int is_saddle = 1;
        for (int k = 0; k < rows; k++) {
            if (matrix[k][col_ind] > min_row) {
                is_saddle = 0;
                break;
            }
        }
        
        if (is_saddle) {
            printf("Saddle point found at position [%d][%d] with value %d\n", 
                   i, col_ind, min_row);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No saddle point found\n");
    }
}

// Function to check if matrix is magic square
int isMagicSquare(int matrix[][100], int n) {
    int sum = 0;
    int diag1 = 0, diag2 = 0;
    
    // Calculate sum of first row
    for (int j = 0; j < n; j++) {
        sum += matrix[0][j];
    }
    
    // Check rows
    for (int i = 1; i < n; i++) {
        int row_sum = 0;
        for (int j = 0; j < n; j++) {
            row_sum += matrix[i][j];
        }
        if (row_sum != sum) return 0;
    }
    
    // Check columns
    for (int j = 0; j < n; j++) {
        int col_sum = 0;
        for (int i = 0; i < n; i++) {
            col_sum += matrix[i][j];
        }
        if (col_sum != sum) return 0;
    }
    
    // Check diagonals
    for (int i = 0; i < n; i++) {
        diag1 += matrix[i][i];
        diag2 += matrix[i][n-1-i];
    }
    
    return (diag1 == sum && diag2 == sum);
}

// Structure for sparse matrix element
struct SparseElement {
    int row;
    int col;
    int value;
};

// Function to convert matrix to sparse form
void convertToSparse(int matrix[][100], int rows, int cols, 
                    struct SparseElement sparse[], int* sparse_size) {
    *sparse_size = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse[*sparse_size].row = i;
                sparse[*sparse_size].col = j;
                sparse[*sparse_size].value = matrix[i][j];
                (*sparse_size)++;
            }
        }
    }
}

void displayMenu() {
    printf("\nArray Operations Menu:\n");
    printf("1. Find missing number\n");
    printf("2. Find array address\n");
    printf("3. Find saddle point\n");
    printf("4. Check magic square\n");
    printf("5. Convert to sparse matrix\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    int matrix[100][100];
    int rows, cols;
    struct SparseElement sparse[1000];
    int sparse_size;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int arr[] = {2, 2, 3, 4};
                int n = sizeof(arr) / sizeof(arr[0]);
                printf("Missing number is: %d\n", findMissingNumber(arr, n));
                break;
            }

            case 2: {
                int arr[] = {1, 2, 3, 4, 5};
                printf("Array address: %p\n", (void*)arr);
                printf("First element address: %p\n", (void*)&arr[0]);
                break;
            }

            case 3:
                printf("Enter number of rows and columns: ");
                scanf("%d %d", &rows, &cols);
                printf("Enter matrix elements:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        scanf("%d", &matrix[i][j]);
                    }
                }
                findSaddlePoint(matrix, rows, cols);
                break;

            case 4:
                printf("Enter size of square matrix: ");
                scanf("%d", &rows);
                printf("Enter matrix elements:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < rows; j++) {
                        scanf("%d", &matrix[i][j]);
                    }
                }
                if (isMagicSquare(matrix, rows)) {
                    printf("The matrix is a magic square\n");
                } else {
                    printf("The matrix is not a magic square\n");
                }
                break;

            case 5:
                printf("Enter number of rows and columns: ");
                scanf("%d %d", &rows, &cols);
                printf("Enter matrix elements:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        scanf("%d", &matrix[i][j]);
                    }
                }
                convertToSparse(matrix, rows, cols, sparse, &sparse_size);
                printf("\nSparse Matrix Representation:\n");
                printf("Row\tColumn\tValue\n");
                for (int i = 0; i < sparse_size; i++) {
                    printf("%d\t%d\t%d\n", sparse[i].row, sparse[i].col, sparse[i].value);
                }
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