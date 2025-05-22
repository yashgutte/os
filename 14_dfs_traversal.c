/*
Question 14: Implement DFS traversal on graph using Adjacency Matrix and adjacency lists
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

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

// Function to perform DFS traversal using adjacency matrix
void DFSUtilMatrix(struct GraphMatrix* graph, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);
    
    for (int i = 0; i < graph->V; i++) {
        if (graph->matrix[v][i] && !visited[i]) {
            DFSUtilMatrix(graph, i, visited);
        }
    }
}

// Function to perform DFS traversal using adjacency list
void DFSUtilList(struct GraphList* graph, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);
    
    struct AdjListNode* current = graph->array[v].head;
    while (current != NULL) {
        if (!visited[current->dest]) {
            DFSUtilList(graph, current->dest, visited);
        }
        current = current->next;
    }
}

// Function to perform DFS traversal starting from all vertices
void DFSMatrix(struct GraphMatrix* graph) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    
    printf("DFS Traversal (Adjacency Matrix):\n");
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            printf("Component starting from vertex %d: ", i);
            DFSUtilMatrix(graph, i, visited);
            printf("\n");
        }
    }
    
    free(visited);
}

// Function to perform DFS traversal starting from all vertices
void DFSList(struct GraphList* graph) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    
    printf("DFS Traversal (Adjacency List):\n");
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            printf("Component starting from vertex %d: ", i);
            DFSUtilList(graph, i, visited);
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
    printf("\nDFS Traversal Operations:\n");
    printf("1. Create Graph (Adjacency Matrix)\n");
    printf("2. Create Graph (Adjacency List)\n");
    printf("3. Perform DFS (Adjacency Matrix)\n");
    printf("4. Perform DFS (Adjacency List)\n");
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
                DFSMatrix(graphMatrix);
                break;
                
            case 4:
                if (graphList == NULL) {
                    printf("Please create a graph first!\n");
                    break;
                }
                DFSList(graphList);
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