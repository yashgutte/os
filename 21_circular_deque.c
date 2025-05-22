/*
Question 21: Implement circular double ended queue where user can add and remove elements from both front and rear
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Structure for circular double-ended queue
struct Deque {
    int* arr;
    int front;
    int rear;
    int size;
    int capacity;
};

// Function to create a new deque
struct Deque* createDeque(int capacity) {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    deque->arr = (int*)malloc(capacity * sizeof(int));
    deque->front = -1;
    deque->rear = -1;
    deque->size = 0;
    deque->capacity = capacity;
    return deque;
}

// Function to check if deque is empty
int isEmpty(struct Deque* deque) {
    return deque->size == 0;
}

// Function to check if deque is full
int isFull(struct Deque* deque) {
    return deque->size == deque->capacity;
}

// Function to insert element at front
void insertFront(struct Deque* deque, int data) {
    if (isFull(deque)) {
        printf("Deque is full!\n");
        return;
    }
    
    if (isEmpty(deque)) {
        deque->front = deque->rear = 0;
    } else {
        deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    }
    
    deque->arr[deque->front] = data;
    deque->size++;
    printf("Inserted %d at front\n", data);
}

// Function to insert element at rear
void insertRear(struct Deque* deque, int data) {
    if (isFull(deque)) {
        printf("Deque is full!\n");
        return;
    }
    
    if (isEmpty(deque)) {
        deque->front = deque->rear = 0;
    } else {
        deque->rear = (deque->rear + 1) % deque->capacity;
    }
    
    deque->arr[deque->rear] = data;
    deque->size++;
    printf("Inserted %d at rear\n", data);
}

// Function to delete element from front
int deleteFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return -1;
    }
    
    int data = deque->arr[deque->front];
    
    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else {
        deque->front = (deque->front + 1) % deque->capacity;
    }
    
    deque->size--;
    printf("Deleted %d from front\n", data);
    return data;
}

// Function to delete element from rear
int deleteRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return -1;
    }
    
    int data = deque->arr[deque->rear];
    
    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else {
        deque->rear = (deque->rear - 1 + deque->capacity) % deque->capacity;
    }
    
    deque->size--;
    printf("Deleted %d from rear\n", data);
    return data;
}

// Function to get front element
int getFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return deque->arr[deque->front];
}

// Function to get rear element
int getRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return deque->arr[deque->rear];
}

// Function to display the deque
void display(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return;
    }
    
    printf("Deque contents: ");
    int i = deque->front;
    int count = 0;
    
    while (count < deque->size) {
        printf("%d ", deque->arr[i]);
        i = (i + 1) % deque->capacity;
        count++;
    }
    printf("\n");
}

// Function to free memory allocated for deque
void freeDeque(struct Deque* deque) {
    free(deque->arr);
    free(deque);
}

void displayMenu() {
    printf("\nCircular Double-Ended Queue Operations:\n");
    printf("1. Insert at Front\n");
    printf("2. Insert at Rear\n");
    printf("3. Delete from Front\n");
    printf("4. Delete from Rear\n");
    printf("5. Get Front Element\n");
    printf("6. Get Rear Element\n");
    printf("7. Display\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Deque* deque = createDeque(MAX_SIZE);
    int choice, data, result;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to insert at front: ");
                scanf("%d", &data);
                insertFront(deque, data);
                break;
                
            case 2:
                printf("Enter data to insert at rear: ");
                scanf("%d", &data);
                insertRear(deque, data);
                break;
                
            case 3:
                result = deleteFront(deque);
                break;
                
            case 4:
                result = deleteRear(deque);
                break;
                
            case 5:
                result = getFront(deque);
                if (result != -1) {
                    printf("Front element: %d\n", result);
                }
                break;
                
            case 6:
                result = getRear(deque);
                if (result != -1) {
                    printf("Rear element: %d\n", result);
                }
                break;
                
            case 7:
                display(deque);
                break;
                
            case 8:
                freeDeque(deque);
                printf("Exiting program\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
} 