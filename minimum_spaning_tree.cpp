// gustavo collaco - 111851 - graph theory
#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1

// defining bool type
typedef int bool;

// a struct Edge component represents an edge, with the two vertices connected and the weight of the connection
struct Edge {
    int point_one;
    int point_two;
    int weight;
};

// an adjacency list node struct
struct Node {
    int dest;
    struct Node* next;
};

// an adjacency list struct
struct AdjList {
    struct Node *head;
};

// a struct Graph component represents a graph, with vertices quantity and an adj list for each vertex
struct Graph {
    int vertices;
    struct AdjList* adj;
};

// creates a new adjacency list node
struct Node* newNode(int dest) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
};

// function to create the graph receiving the quantity of vertices as param
struct Graph* createGraph(int vertices_qty) { 
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));

    graph->vertices = vertices_qty;
    graph->adj = (struct AdjList*) malloc(vertices_qty * sizeof(struct AdjList));

    for (int i = 0; i < vertices_qty; ++i) {
        graph->adj[i].head = NULL;
    }

    return graph;
} 

// inserts an edge to the graph, setting the adjacency list of the linked vertices
void insertEdge(struct Graph* graph, int point_one, int point_two) {
    struct Node* node = newNode(point_two);
    node->next = graph->adj[point_one].head;
    graph->adj[point_one].head = node;

    node = newNode(point_one);
    node->next = graph->adj[point_two].head;
    graph->adj[point_two].head = node;
}

// inserts a node on the list
void insertNode(struct Graph* graph, int point_a, int point_b) {
    struct Node* node = newNode(point_b);
    node->next = graph->adj[point_a].head;
    graph->adj[point_a].head = node;
}

// DFS to visit all possible vertices
void DepthFirstSearch(bool visited[], struct Graph* graph, int vertex) {
    visited[vertex] = true;

    // iterate through all vertices adjacent to the vertex passed as parameter 
    struct Node* node = graph->adj[vertex].head;
	while(node != NULL) {
        if (!visited[node->dest]) DepthFirstSearch(visited, graph, node->dest);
        node = node->next;
    }
}

// function to check if the graph is still connected
bool connected(struct Graph* graph) {
    bool visited[graph->vertices];
    // initialize all vertices as non visited
    for (int i = 0; i < graph->vertices; i++) visited[i] = false;

    // run a DFS from the vertex 0, to update the visited array
    DepthFirstSearch(visited, graph, 0);

    // checks if there is an unvisited vertex on the graph. if yes, return false. if no, the graph is still connected
    for (int i = 0; i < graph->vertices; i++) {
        if(!visited[i]) return false;
    }
    return true;
}

// sorts the edges list based on the weight
void sort(struct Edge edges[], int edges_qty) {
	for (int i = 0; i < edges_qty; i++) {
		for (int j = 0; j < edges_qty; j++) {
			if (edges[j].weight < edges[i].weight) {
				struct Edge tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}
}

// function to delete a node of a list based on the value
void deleteNode(struct Node **head, int value) {
    // store head node
    struct Node* temp = *head, *prev;

    // if value to be deleted is at the head node
    if (temp != NULL && temp->dest == value) {
        *head = temp->next;
        free(temp);
        return;
    }

    // look for the value to be deleted, keeping the previous node
    while (temp != NULL && temp->dest != value) {
        prev = temp;
        temp = temp->next;
    }

    // if value not on the list
    if (temp == NULL) return;

    // unlink node
    prev->next = temp->next;
    free(temp);
}

// utility function for debugging
void printList(struct Node *node) { 
    while (node != NULL) {
        printf(" %d ", node->dest);
        node = node->next;
    }
}

// minimum spanning tree using reverse-delete, reverse of kruskal
int MinimumSpanningTree(struct Graph* graph, struct Edge edges[], int edges_qty) {
    int tree_weight = 0;

    // order the edges descending, considering the weight
    sort(edges, edges_qty);

    // we try to remove each edge, if removing it keeps the graph connected, keep it removed and add the weight to the tree_weight
    // else undo the removal
    for (int i = 0; i < edges_qty; i++) {
        int point_one = edges[i].point_one;
        int point_two = edges[i].point_two;

        // printf("weight:%d     point one: %d  point two: %d\n", edges[i].weight, point_one, point_two);

        // printf("\n\n");
        // printList(graph->adj[point_one].head);
        // printf("\n\n");
        // printList(graph->adj[point_two].head);
        // printf("\n\n");

        deleteNode(&graph->adj[point_one].head, point_two);
        deleteNode(&graph->adj[point_two].head, point_one);

        // printf("\n\n");
        // printList(graph->adj[point_one].head);
        // printf("\n\n");
        // printList(graph->adj[point_two].head);
        // printf("\n\n");

        // printf("removal number: %d     is graph connected? %d    \n", i, connected(graph));

        if (connected(graph)) tree_weight += edges[i].weight;
        else {
            insertNode(graph, point_one, point_two);
            insertNode(graph, point_two, point_one);

            // printf("\n\n");
            // printList(graph->adj[point_one].head);
            // printf("\n\n");
            // printList(graph->adj[point_two].head);
            // printf("\n\n");
        }
    }

    return tree_weight;
}

// main function
int main() {
    // receiving ints for the quantity of bus stops and the quantity of tracks covered
    int qty_bus_stops, qty_tracks;
    scanf("%d %d", &qty_bus_stops, &qty_tracks);

    struct Graph* graph = createGraph(qty_bus_stops);

    // initializing the edges array
    struct Edge edges[qty_tracks];
    for (int i = 0; i < qty_tracks; i++) {
        edges[i].point_one = -1;
        edges[i].point_two = -1;
        edges[i].weight = -1;
    }

    // receiving inputs for each edge of the graph
    for (int i = 0; i < qty_tracks; i++) {
        int point_one, point_two, weight;
        scanf("%d %d %d", &point_one, &point_two, &weight);
        edges[i].point_one = point_one;
        edges[i].point_two = point_two;
        edges[i].weight = weight;
        insertEdge(graph, point_one, point_two);
    }

    // prints the result found
    int result = MinimumSpanningTree(graph, edges, qty_tracks);
    printf("%d\n", result);

    return 0;
}
