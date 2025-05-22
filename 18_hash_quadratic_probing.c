/*
Question 18: Implement quadratic probing collision handling technique for hash table
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define EMPTY -1
#define DELETED -2

// Structure for hash table entry
struct HashEntry {
    int key;
    int value;
};

// Structure for hash table
struct HashTable {
    struct HashEntry* table;
    int size;
    int count;
};

// Function to create a new hash table
struct HashTable* createHashTable(int size) {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->size = size;
    ht->count = 0;
    ht->table = (struct HashEntry*)malloc(size * sizeof(struct HashEntry));
    
    // Initialize all entries as empty
    for (int i = 0; i < size; i++) {
        ht->table[i].key = EMPTY;
        ht->table[i].value = 0;
    }
    
    return ht;
}

// Hash function using modulo
int hashFunction(int key, int size) {
    return key % size;
}

// Function to insert a key-value pair using quadratic probing
int insert(struct HashTable* ht, int key, int value) {
    if (ht->count == ht->size) {
        printf("Hash table is full!\n");
        return 0;
    }
    
    int index = hashFunction(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    // Quadratic probing
    while (ht->table[index].key != EMPTY && ht->table[index].key != DELETED) {
        if (ht->table[index].key == key) {
            printf("Key already exists!\n");
            return 0;
        }
        
        i++;
        index = (originalIndex + i * i) % ht->size;
        
        // If we've gone through the entire table
        if (i >= ht->size) {
            printf("Hash table is full!\n");
            return 0;
        }
    }
    
    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->count++;
    return 1;
}

// Function to search for a key using quadratic probing
int search(struct HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index].key != EMPTY) {
        if (ht->table[index].key == key) {
            return ht->table[index].value;
        }
        
        i++;
        index = (originalIndex + i * i) % ht->size;
        
        // If we've gone through the entire table
        if (i >= ht->size) {
            break;
        }
    }
    
    return -1; // Key not found
}

// Function to delete a key using quadratic probing
int delete(struct HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index].key != EMPTY) {
        if (ht->table[index].key == key) {
            ht->table[index].key = DELETED;
            ht->count--;
            return 1;
        }
        
        i++;
        index = (originalIndex + i * i) % ht->size;
        
        // If we've gone through the entire table
        if (i >= ht->size) {
            break;
        }
    }
    
    return 0; // Key not found
}

// Function to display the hash table
void display(struct HashTable* ht) {
    printf("\nHash Table:\n");
    printf("Index\tKey\tValue\n");
    for (int i = 0; i < ht->size; i++) {
        printf("%d\t", i);
        if (ht->table[i].key == EMPTY) {
            printf("EMPTY\tEMPTY\n");
        } else if (ht->table[i].key == DELETED) {
            printf("DELETED\tDELETED\n");
        } else {
            printf("%d\t%d\n", ht->table[i].key, ht->table[i].value);
        }
    }
    printf("\n");
}

// Function to free memory allocated for hash table
void freeHashTable(struct HashTable* ht) {
    free(ht->table);
    free(ht);
}

void displayMenu() {
    printf("\nHash Table Operations (Quadratic Probing):\n");
    printf("1. Insert\n");
    printf("2. Search\n");
    printf("3. Delete\n");
    printf("4. Display\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct HashTable* ht = createHashTable(TABLE_SIZE);
    int choice, key, value, result;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key and value to insert: ");
                scanf("%d %d", &key, &value);
                if (insert(ht, key, value)) {
                    printf("Inserted successfully\n");
                }
                break;
                
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                result = search(ht, key);
                if (result != -1) {
                    printf("Value found: %d\n", result);
                } else {
                    printf("Key not found\n");
                }
                break;
                
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                if (delete(ht, key)) {
                    printf("Deleted successfully\n");
                } else {
                    printf("Key not found\n");
                }
                break;
                
            case 4:
                display(ht);
                break;
                
            case 5:
                freeHashTable(ht);
                printf("Exiting program\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
} 