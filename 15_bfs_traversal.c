/*
Question 15: Implement BFS traversal on graph using Adjacency Matrix and adjacency lists
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure for queue node
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Structure for queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Structure for adjacency list node
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure for adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure for graph using adjacency list
struct GraphList {
    int V;
    struct AdjList* array;
};

// Structure for graph using adjacency matrix
struct GraphMatrix {
    int V;
    int** matrix;
};

// Function to create a new queue node
struct QueueNode* newQueueNode(int data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a node
void enqueue(struct Queue* queue, int data) {
    struct QueueNode* newNode = newQueueNode(data);
    
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a node
int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return -1;
    }
    
    struct QueueNode* temp = queue->front;
    int data = temp->data;
    
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    return data;
}

// Function to check if queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph using adjacency list
struct GraphList* createGraphList(int V) {
    struct GraphList* graph = (struct GraphList*)malloc(sizeof(struct GraphList));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// Function to create a graph using adjacency matrix
struct GraphMatrix* createGraphMatrix(int V) {
    struct GraphMatrix* graph = (struct GraphMatrix*)malloc(sizeof(struct GraphMatrix));
    graph->V = V;
    
    // Allocate memory for adjacency matrix
    graph->matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->matrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = 0;
        }
    }
    
    return graph;
}

// Function to add an edge to the adjacency list graph
void addEdgeList(struct GraphList* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // For undirected graph, add edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to add an edge to the adjacency matrix graph
void addEdgeMatrix(struct GraphMatrix* graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1; // For undirected graph
}

// Function to perform BFS traversal using adjacency matrix
void BFSMatrix(struct GraphMatrix* graph, int start, int* visited) {
    struct Queue* queue = createQueue();
    
    visited[start] = 1;
    printf("%d ", start);
    enqueue(queue, start);
    
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        
        for (int i = 0; i < graph->V; i++) {
            if (graph->matrix[current][i] && !visited[i]) {
                visited[i] = 1;
                printf("%d ", i);
                enqueue(queue, i);
            }
        }
    }
    
    free(queue);
}

// Function to perform BFS traversal using adjacency list
void BFSList(struct GraphList* graph, int start, int* visited) {
    struct Queue* queue = createQueue();
    
    visited[start] = 1;
    printf("%d ", start);
    enqueue(queue, start);
    
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        
        struct AdjListNode* temp = graph->array[current].head;
        while (temp != NULL) {
            if (!visited[temp->dest]) {
                visited[temp->dest] = 1;
                printf("%d ", temp->dest);
                enqueue(queue, temp->dest);
            }
            temp = temp->next;
        }
    }
    
    free(queue);
}

// Function to perform BFS traversal starting from all vertices
void BFSTraversalMatrix(struct GraphMatrix* graph) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    
    printf("BFS Traversal (Adjacency Matrix):\n");
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            printf("Component starting from vertex %d: ", i);
            BFSMatrix(graph, i, visited);
            printf("\n");
        }
    }
    
    free(visited);
}

// Function to perform BFS traversal starting from all vertices
void BFSTraversalList(struct GraphList* graph) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    
    printf("BFS Traversal (Adjacency List):\n");
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            printf("Component starting from vertex %d: ", i);
            BFSList(graph, i, visited);
            printf("\n");
        }
    }
    
    free(visited);
}

// Function to free memory allocated for adjacency list graph
void freeGraphList(struct GraphList* graph) {
    for (int i = 0; i < graph->V; i++) {
        struct AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            struct AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

// Function to free memory allocated for adjacency matrix graph
void freeGraphMatrix(struct GraphMatrix* graph) {
    for (int i = 0; i < graph->V; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

void displayMenu() {
    printf("\nBFS Traversal Operations:\n");
    printf("1. Create Graph (Adjacency Matrix)\n");
    printf("2. Create Graph (Adjacency List)\n");
    printf("3. Perform BFS (Adjacency Matrix)\n");
    printf("4. Perform BFS (Adjacency List)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct GraphMatrix* graphMatrix = NULL;
    struct GraphList* graphList = NULL;
    int choice, V, src, dest;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter number of vertices: ");
                scanf("%d", &V);
                if (graphMatrix != NULL) {
                    freeGraphMatrix(graphMatrix);
                }
                graphMatrix = createGraphMatrix(V);
                printf("Graph created with %d vertices\n", V);
                break;
                
            case 2:
                printf("Enter number of vertices: ");
                scanf("%d", &V);
                if (graphList != NULL) {
                    freeGraphList(graphList);
                }
                graphList = createGraphList(V);
                printf("Graph created with %d vertices\n", V);
                break;
                
            case 3:
                if (graphMatrix == NULL) {
                    printf("Please create a graph first!\n");
                    break;
                }
                BFSTraversalMatrix(graphMatrix);
                break;
                
            case 4:
                if (graphList == NULL) {
                    printf("Please create a graph first!\n");
                    break;
                }
                BFSTraversalList(graphList);
                break;
                
            case 5:
                if (graphMatrix != NULL) {
                    freeGraphMatrix(graphMatrix);
                }
                if (graphList != NULL) {
                    freeGraphList(graphList);
                }
                printf("Exiting program\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        // Add edges to the graph
        if (choice == 1 || choice == 2) {
            printf("Enter number of edges: ");
            int E;
            scanf("%d", &E);
            
            printf("Enter edges (source destination):\n");
            for (int i = 0; i < E; i++) {
                scanf("%d %d", &src, &dest);
                if (src >= 0 && src < V && dest >= 0 && dest < V) {
                    if (choice == 1) {
                        addEdgeMatrix(graphMatrix, src, dest);
                    } else {
                        addEdgeList(graphList, src, dest);
                    }
                } else {
                    printf("Invalid edge! Vertices must be between 0 and %d\n", V - 1);
                    i--;
                }
            }
        }
    }
    
    return 0;
} 