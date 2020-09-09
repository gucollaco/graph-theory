// gustavo collaco - 111851 - graph theory
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

// a struct Edge component represents an edge, with the two vertices connected and the weight of the connection
struct Edge {
    int point_one;
    int point_two;
    int weight;
};

// a struct Graph component represents a graph, with vertices quantity, an adj list for each vertex and a list of edges with weights
struct Graph {
    int vertices;
    list<int> *adj;
    vector<Edge> edges; 
};

// inserts an edge to the graph, setting the adjacency list of the linked vertices, as well as the edges vector
void insertEdge(Graph *graph, int point_one, int point_two, int weight) {
    graph->adj[point_one].push_back(point_two);
    graph->adj[point_two].push_back(point_one);
    Edge edge = { point_one, point_two, weight };
    graph->edges.push_back(edge);
}

// function to be used on the list sort, ordering the list in a descending way, considering the weight of the edges
bool compareWeights(Edge edge_one, Edge edge_two) {
    return (edge_one.weight > edge_two.weight);
}

// DFS to visit all possible vertices
void DepthFirstSearch(bool visited[], Graph *graph, int vertex = 0) {
    visited[vertex] = true;

    // iterate through all vertices adjacent to the vertex passed as parameter 
    list<int>::iterator it; 
    for (it = graph->adj[vertex].begin(); it != graph->adj[vertex].end(); ++it) {
        // if not visited, visit
        if (!visited[*it]) DepthFirstSearch(visited, graph, *it); 
    }
}

// function to check if the graph is still connected
bool connected(Graph *graph) {
    bool visited[graph->vertices];

    // run a DFS from the vertex 0, to update the visited array
    DepthFirstSearch(visited, graph);

    // checks if there is an unvisited vertex on the graph. if yes, return false. if no, the graph is still connected
    for (int i = 1; i < graph->vertices; i++) {
        if(!visited[i]) return false;
    }
    return true;
}

// minimum spanning tree using reverse-delete, reverse of kruskal
int MinimumSpanningTree(Graph *graph) {
    int tree_weight = 0;

    // order the edges descending, considering the weight
    sort(graph->edges.begin(), graph->edges.end(), compareWeights);

    // we try to remove each edge, if removing it keeps the graph connected, keep it removed and add the weight to the tree_weight
    // else undo the removal
    for (int i = 0; i < graph->edges.size(); i++) {
        int point_one = graph->edges[i].point_one;
        int point_two = graph->edges[i].point_two;

        graph->adj[point_one].remove(point_two);
        graph->adj[point_two].remove(point_one);

        if (connected(graph)) tree_weight += graph->edges[i].weight;
        else {
            graph->adj[point_one].push_back(point_two);
            graph->adj[point_two].push_back(point_one);
        }
    }

    return tree_weight;
}

// main function
int main() {
    // receiving ints for the quantity of bus stops and the quantity of tracks covered
    int qty_bus_stops, qty_tracks;
    cin >> qty_bus_stops >> qty_tracks;

    Graph graph = { qty_bus_stops, new list<int>[qty_bus_stops] };

    // Receiving inputs for each edge of the graph
    for (int i = 0; i < qty_tracks; i++) {
        int point_one, point_two, weight;
        cin >> point_one >> point_two >> weight;
        insertEdge(&graph, point_one, point_two, weight);
    }

    // prints the result found
    cout << MinimumSpanningTree(&graph) << endl;
    return 0;
}
