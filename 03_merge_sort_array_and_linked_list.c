/*
Question 3: Implement merge sort using array/linked list
*/

#include <stdio.h>
#include <stdlib.h>

// Array implementation
void mergeArrays(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
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

void mergeSortArray(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortArray(arr, left, mid);
        mergeSortArray(arr, mid + 1, right);
        mergeArrays(arr, left, mid, right);
    }
}

// Linked List implementation
struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

struct Node* mergeLists(struct Node* first, struct Node* second) {
    if (!first) return second;
    if (!second) return first;

    struct Node* result = NULL;

    if (first->data <= second->data) {
        result = first;
        result->next = mergeLists(first->next, second);
    } else {
        result = second;
        result->next = mergeLists(first, second->next);
    }
    return result;
}

void splitList(struct Node* source, struct Node** front, struct Node** back) {
    struct Node* fast;
    struct Node* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSortList(struct Node** headRef) {
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    splitList(head, &a, &b);
    mergeSortList(&a);
    mergeSortList(&b);
    *headRef = mergeLists(a, b);
}

void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int choice;
    printf("Choose implementation:\n");
    printf("1. Array\n");
    printf("2. Linked List\n");
    scanf("%d", &choice);

    if (choice == 1) {
        // Array implementation
        int n;
        printf("Enter number of elements: ");
        scanf("%d", &n);
        int* arr = (int*)malloc(n * sizeof(int));
        
        printf("Enter elements:\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        printf("Original array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        mergeSortArray(arr, 0, n - 1);

        printf("Sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        free(arr);
    } else {
        // Linked List implementation
        struct Node* head = NULL;
        int n, data;
        
        printf("Enter number of elements: ");
        scanf("%d", &n);
        
        printf("Enter elements:\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &data);
            insertAtEnd(&head, data);
        }

        printf("Original list: ");
        displayList(head);

        mergeSortList(&head);

        printf("Sorted list: ");
        displayList(head);
    }

    return 0;
} 