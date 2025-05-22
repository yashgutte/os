/*
Question 13: Implement single source shortest path using Dijkstra's algorithm
with both adjacency matrix and adjacency list representations
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

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
    
    // Allocate memory for adjacency matrix
    graph->matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->matrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
    
    return graph;
}

// Function to add an edge to the adjacency list graph
void addEdgeList(struct GraphList* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Function to add an edge to the adjacency matrix graph
void addEdgeMatrix(struct GraphMatrix* graph, int src, int dest, int weight) {
    graph->matrix[src][dest] = weight;
}

// Function to find minimum distance vertex
int minDistance(int dist[], int visited[], int V) {
    int min = INF, min_index = -1;
    
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

// Function to print the shortest path
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to print the solution
void printSolution(int dist[], int parent[], int V, int src) {
    printf("\nVertex\tDistance\tPath\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            printf("%d\tINF\t\tNo path\n", i);
        } else {
            printf("%d\t%d\t\t", i, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
}

// Function to implement Dijkstra's algorithm using adjacency matrix
void dijkstraMatrix(struct GraphMatrix* graph, int src) {
    int V = graph->V;
    int dist[V];
    int visited[V];
    int parent[V];
    
    // Initialize distances and visited array
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    // Distance of source vertex from itself is 0
    dist[src] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph->matrix[u][v] != INF &&
                dist[u] != INF && dist[u] + graph->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->matrix[u][v];
                parent[v] = u;
            }
        }
    }
    
    printSolution(dist, parent, V, src);
}

// Function to implement Dijkstra's algorithm using adjacency list
void dijkstraList(struct GraphList* graph, int src) {
    int V = graph->V;
    int dist[V];
    int visited[V];
    int parent[V];
    
    // Initialize distances and visited array
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    // Distance of source vertex from itself is 0
    dist[src] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;
        
        // Update distances of adjacent vertices
        struct AdjListNode* current = graph->array[u].head;
        while (current != NULL) {
            int v = current->dest;
            if (!visited[v] && dist[u] != INF &&
                dist[u] + current->weight < dist[v]) {
                dist[v] = dist[u] + current->weight;
                parent[v] = u;
            }
            current = current->next;
        }
    }
    
    printSolution(dist, parent, V, src);
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
    printf("\nDijkstra's Algorithm Operations:\n");
    printf("1. Create Graph (Adjacency Matrix)\n");
    printf("2. Create Graph (Adjacency List)\n");
    printf("3. Find Shortest Path (Adjacency Matrix)\n");
    printf("4. Find Shortest Path (Adjacency List)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct GraphMatrix* graphMatrix = NULL;
    struct GraphList* graphList = NULL;
    int choice, V, src, dest, weight;
    
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
                printf("Enter source vertex: ");
                scanf("%d", &src);
                if (src >= 0 && src < graphMatrix->V) {
                    dijkstraMatrix(graphMatrix, src);
                } else {
                    printf("Invalid source vertex!\n");
                }
                break;
                
            case 4:
                if (graphList == NULL) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printf("Enter source vertex: ");
                scanf("%d", &src);
                if (src >= 0 && src < graphList->V) {
                    dijkstraList(graphList, src);
                } else {
                    printf("Invalid source vertex!\n");
                }
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
            
            printf("Enter edges (source destination weight):\n");
            for (int i = 0; i < E; i++) {
                scanf("%d %d %d", &src, &dest, &weight);
                if (src >= 0 && src < V && dest >= 0 && dest < V) {
                    if (choice == 1) {
                        addEdgeMatrix(graphMatrix, src, dest, weight);
                    } else {
                        addEdgeList(graphList, src, dest, weight);
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