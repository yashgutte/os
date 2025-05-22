/*
Question 7: WAP to implement insertion sort, merge sort, bubble sort on 1 D array of student structure 
(contains student_name, roll_no, total marks) with keys as students_roll_no and count the number of swap performed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

struct Student {
    char name[MAX_NAME_LENGTH];
    int roll_no;
    float total_marks;
};

// Global variable to count swaps
int swap_count = 0;

// Function to swap two student records
void swap(struct Student* a, struct Student* b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

// Insertion Sort
void insertionSort(struct Student arr[], int n) {
    swap_count = 0;
    for (int i = 1; i < n; i++) {
        struct Student key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].roll_no > key.roll_no) {
            arr[j + 1] = arr[j];
            j--;
            swap_count++;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
void merge(struct Student arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Student* L = (struct Student*)malloc(n1 * sizeof(struct Student));
    struct Student* R = (struct Student*)malloc(n2 * sizeof(struct Student));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].roll_no <= R[j].roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            swap_count++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(struct Student arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Bubble Sort
void bubbleSort(struct Student arr[], int n) {
    swap_count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].roll_no > arr[j + 1].roll_no) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Function to display student records
void displayStudents(struct Student arr[], int n) {
    printf("\nStudent Records:\n");
    printf("Roll No\tName\t\tTotal Marks\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-20s%.2f\n", arr[i].roll_no, arr[i].name, arr[i].total_marks);
    }
}

// Function to input student records
void inputStudents(struct Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]s", arr[i].name);
        printf("Roll No: ");
        scanf("%d", &arr[i].roll_no);
        printf("Total Marks: ");
        scanf("%f", &arr[i].total_marks);
    }
}

void displayMenu() {
    printf("\nSorting Menu:\n");
    printf("1. Insertion Sort\n");
    printf("2. Merge Sort\n");
    printf("3. Bubble Sort\n");
    printf("4. Display Records\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int n, choice;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("Invalid number of students\n");
        return 1;
    }

    inputStudents(students, n);

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertionSort(students, n);
                printf("Records sorted using Insertion Sort\n");
                printf("Number of swaps: %d\n", swap_count);
                break;

            case 2:
                swap_count = 0;
                mergeSort(students, 0, n - 1);
                printf("Records sorted using Merge Sort\n");
                printf("Number of swaps: %d\n", swap_count);
                break;

            case 3:
                bubbleSort(students, n);
                printf("Records sorted using Bubble Sort\n");
                printf("Number of swaps: %d\n", swap_count);
                break;

            case 4:
                displayStudents(students, n);
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