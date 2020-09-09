// gustavo collaco - 111851 - graph theory
#include <stdio.h>
#include <stdlib.h>

// a struct Edge component represents an edge, with the two vertices connected and the weight of the connection
struct Edge {
    int point_one;
    int point_two;
    int weight;
};

// finds the parent of the vertex (which group the vertex belongs to)
int find(int sets[], int vertex) {
    if(sets[vertex] == vertex) return vertex;

    sets[vertex] = find(sets, sets[vertex]);
    return sets[vertex];
}

// group sets (union) and adjusts the ranks
void group(int sets[], int ranks[], int x_set, int y_set) {
    if(ranks[x_set] == ranks[y_set]) {
        sets[y_set] = x_set; // x_set turns to parent of y_set
        ranks[x_set]++; // update the rank
    } else if(ranks[x_set] > ranks[y_set]) {
        sets[y_set] = x_set; // x_set turns to parent of y_set
    } else {
        sets[x_set] = y_set;
    }
}

// swap function implementation
void swap(struct Edge *a, struct Edge *b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

// quicksort using middle value for pilot
void quickSort(struct Edge edges[], int low, int high) {
    int i = low;
    int j = high;
    int pivot = edges[(low + high) / 2].weight;
    while (i <= j) {
        while (edges[i].weight < pivot) i++;
        while (edges[j].weight > pivot) j--;
        if (i <= j) {
            swap(&edges[i], &edges[j]);
            i++;
            j--;
        }
    }
    if (low < j) quickSort(edges, low, j);
    if (i < high) quickSort(edges, i, high);
}

// minimum spanning tree using kruskal's
int MinimumSpanningTree(struct Edge edges[], int edges_qty, int vertices_qty) {
    // a set for each vertex
    int *sets;
    sets = (int*) malloc(vertices_qty * sizeof(int));
    
    int *ranks;
    ranks = (int*) malloc(vertices_qty * sizeof(int));

    // initially, all vertex are the parents of their own set
    int j;
    for (j = 0; j < vertices_qty; j++) {
        sets[j] = j;
        ranks[j] = 0;
    }
    
    // storing the total removed_weight
    int removed_weight = 0;

    // we try to add an edge, if adding it doesnt make a cycle, group the sets and make a new set (union)
    // if both are at the same sets, and a cycle is found, add the weight to the removed_weight variable
    // in case the qty of edges added equals the qty of vertices - 1, we break
    int i;
    int edges_included = 0;
    for (i = 0; i < edges_qty; i++) {
        if (edges_included >= vertices_qty) break;
        else {
            int x_set = find(sets, edges[i].point_one);
            int y_set = find(sets, edges[i].point_two);

            if(x_set == y_set) removed_weight += edges[i].weight;
            else {
                group(sets, ranks, x_set, y_set);
                edges_included++;
            }
        }
    }
    
    // now simply add the remaining weights
    for (j = i; j < edges_qty; j++) removed_weight += edges[j].weight;

    return removed_weight;
}

// main function
int main() {
    // receiving ints for the quantity of bus stops and the quantity of tracks covered
    int qty_bus_stops, qty_tracks;
    scanf("%d %d", &qty_bus_stops, &qty_tracks);

    // initializing the edges array
    struct Edge * edges;
    edges = (struct Edge*) malloc(qty_tracks * sizeof(struct Edge));

    // receiving inputs for each edge
    int j;
    for (j = 0; j < qty_tracks; j++) scanf("%d %d %d", &edges[j].point_one, &edges[j].point_two, &edges[j].weight);

    // order the edges ascending, using a quicksort with middle value for pivot
    quickSort(edges, 0, qty_tracks-1);

    // prints the result found
    int result = MinimumSpanningTree(edges, qty_tracks, qty_bus_stops);
    printf("%d\n", result);

    return 0;
}
