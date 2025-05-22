/*
Question 9: Generate Minimum spanning tree using Kruskal's algorithm when graph is represented using Adjacency matrix and list
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

// Structure for edge
struct Edge {
    int src;
    int dest;
    int weight;
};

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

// Structure for subset for union-find
struct Subset {
    int parent;
    int rank;
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

// Function to find set of an element i
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Function to do union of two sets
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare edges for qsort
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to implement Kruskal's algorithm using adjacency matrix
void KruskalMSTMatrix(struct GraphMatrix* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;
    
    // Create array of all edges
    struct Edge* edges = (struct Edge*)malloc(V * V * sizeof(struct Edge));
    int edgeCount = 0;
    
    for (int v = 0; v < V; v++) {
        for (int u = v + 1; u < V; u++) {
            if (graph->matrix[v][u] != 0) {
                edges[edgeCount].src = v;
                edges[edgeCount].dest = u;
                edges[edgeCount].weight = graph->matrix[v][u];
                edgeCount++;
            }
        }
    }
    
    // Sort edges by weight
    qsort(edges, edgeCount, sizeof(edges[0]), compareEdges);
    
    // Allocate memory for subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    
    // Create V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    // Process edges in sorted order
    while (e < V - 1 && i < edgeCount) {
        struct Edge next_edge = edges[i++];
        
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    
    // Print the MST
    printf("Edges in MST using Adjacency Matrix:\n");
    int minimumCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost: %d\n", minimumCost);
    
    free(edges);
    free(subsets);
}

// Function to implement Kruskal's algorithm using adjacency list
void KruskalMSTList(struct GraphList* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;
    
    // Create array of all edges
    struct Edge* edges = (struct Edge*)malloc(V * V * sizeof(struct Edge));
    int edgeCount = 0;
    
    // Collect all edges from adjacency list
    for (int v = 0; v < V; v++) {
        struct AdjListNode* current = graph->array[v].head;
        while (current != NULL) {
            if (v < current->dest) { // Avoid duplicate edges
                edges[edgeCount].src = v;
                edges[edgeCount].dest = current->dest;
                edges[edgeCount].weight = current->weight;
                edgeCount++;
            }
            current = current->next;
        }
    }
    
    // Sort edges by weight
    qsort(edges, edgeCount, sizeof(edges[0]), compareEdges);
    
    // Allocate memory for subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    
    // Create V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    // Process edges in sorted order
    while (e < V - 1 && i < edgeCount) {
        struct Edge next_edge = edges[i++];
        
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    
    // Print the MST
    printf("Edges in MST using Adjacency List:\n");
    int minimumCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost: %d\n", minimumCost);
    
    free(edges);
    free(subsets);
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
    printf("Kruskal's MST using Adjacency Matrix:\n");
    KruskalMSTMatrix(graphMatrix);
    
    printf("\nKruskal's MST using Adjacency List:\n");
    KruskalMSTList(graphList);
    
    // Free allocated memory
    freeGraphMatrix(graphMatrix);
    freeGraphList(graphList);
    
    return 0;
} 