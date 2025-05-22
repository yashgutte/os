/*
Question 10: Generate Minimum spanning tree using Prim's algorithm when graph is represented using adjacency list and matrix
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Structure for adjacency list node
struct AdjListNode {
    int dest;
    int weight;
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

// Structure for min heap node
struct MinHeapNode {
    int v;
    int key;
};

// Structure for min heap
struct MinHeap {
    int size;
    int capacity;
    int* pos;
    struct MinHeapNode** array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
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
    
    graph->matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->matrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = 0;
        }
    }
    
    return graph;
}

// Function to add an edge to adjacency list graph
void addEdgeList(struct GraphList* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // Since graph is undirected, add edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to add an edge to adjacency matrix graph
void addEdgeMatrix(struct GraphMatrix* graph, int src, int dest, int weight) {
    graph->matrix[src][dest] = weight;
    graph->matrix[dest][src] = weight; // Since graph is undirected
}

// Function to create a new min heap node
struct MinHeapNode* newMinHeapNode(int v, int key) {
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}

// Function to create a min heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Function to swap two min heap nodes
void swapMinHeapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify at given index
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        struct MinHeapNode* smallestNode = minHeap->array[smallest];
        struct MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if min heap is empty
bool isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease key value of a given vertex
void decreaseKey(struct MinHeap* minHeap, int v, int key) {
    int i = minHeap->pos[v];
    minHeap->array[i]->key = key;

    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to check if a vertex is in min heap
bool isInMinHeap(struct MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

// Function to implement Prim's algorithm using adjacency matrix
void PrimMSTMatrix(struct GraphMatrix* graph) {
    int V = graph->V;
    int parent[V];
    int key[V];
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all vertices
    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }

    // Make key value of 0th vertex as 0
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        for (int v = 0; v < V; v++) {
            if (graph->matrix[u][v] && isInMinHeap(minHeap, v) && 
                graph->matrix[u][v] < key[v]) {
                key[v] = graph->matrix[u][v];
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
        }
    }

    // Print MST
    printf("Edges in MST using Adjacency Matrix:\n");
    int minimumCost = 0;
    for (int i = 1; i < V; i++) {
        printf("%d -- %d == %d\n", parent[i], i, graph->matrix[i][parent[i]]);
        minimumCost += graph->matrix[i][parent[i]];
    }
    printf("Minimum Cost: %d\n", minimumCost);

    // Free memory
    for (int i = 0; i < V; i++) {
        free(minHeap->array[i]);
    }
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

// Function to implement Prim's algorithm using adjacency list
void PrimMSTList(struct GraphList* graph) {
    int V = graph->V;
    int parent[V];
    int key[V];
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all vertices
    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }

    // Make key value of 0th vertex as 0
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        struct AdjListNode* current = graph->array[u].head;
        while (current != NULL) {
            int v = current->dest;
            if (isInMinHeap(minHeap, v) && current->weight < key[v]) {
                key[v] = current->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            current = current->next;
        }
    }

    // Print MST
    printf("Edges in MST using Adjacency List:\n");
    int minimumCost = 0;
    for (int i = 1; i < V; i++) {
        printf("%d -- %d == %d\n", parent[i], i, key[i]);
        minimumCost += key[i];
    }
    printf("Minimum Cost: %d\n", minimumCost);

    // Free memory
    for (int i = 0; i < V; i++) {
        free(minHeap->array[i]);
    }
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
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

int main() {
    int V = 4; // Number of vertices
    
    // Create graph using adjacency matrix
    struct GraphMatrix* graphMatrix = createGraphMatrix(V);
    
    // Add edges to matrix graph
    addEdgeMatrix(graphMatrix, 0, 1, 10);
    addEdgeMatrix(graphMatrix, 0, 2, 6);
    addEdgeMatrix(graphMatrix, 0, 3, 5);
    addEdgeMatrix(graphMatrix, 1, 3, 15);
    addEdgeMatrix(graphMatrix, 2, 3, 4);
    
    // Create graph using adjacency list
    struct GraphList* graphList = createGraphList(V);
    
    // Add edges to list graph
    addEdgeList(graphList, 0, 1, 10);
    addEdgeList(graphList, 0, 2, 6);
    addEdgeList(graphList, 0, 3, 5);
    addEdgeList(graphList, 1, 3, 15);
    addEdgeList(graphList, 2, 3, 4);
    
    // Find MST using both representations
    printf("Prim's MST using Adjacency Matrix:\n");
    PrimMSTMatrix(graphMatrix);
    
    printf("\nPrim's MST using Adjacency List:\n");
    PrimMSTList(graphList);
    
    // Free allocated memory
    freeGraphMatrix(graphMatrix);
    freeGraphList(graphList);
    
    return 0;
} 