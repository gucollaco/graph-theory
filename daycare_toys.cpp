// gustavo collaco - 111851 - graph theory
#include <iostream>
#include <string.h>

using namespace std;

// M_MAX is the number of toys  
// and N_MAX is the number of children 
#define M_MAX 100
#define N_MAX 100

// variables to keep the number of toys, the number of children, and the qty of relationships
int N, M, L;

// function to add an edge to the graph
void addEdge(bool graph[N_MAX][M_MAX], int u, int v) { graph[u][v] = 1; }

// DFS that returns true if it is possible to find a matching for u
bool findMatching(bool graph[N_MAX][M_MAX], int u, bool visited[], int match[]) {
    // iterate for each toy
    for (int v = 0; v < M; v++) {
        // if child u is interested in toy v and the toy is not yet visited
        if (graph[u][v] && !visited[v]) {
            // Mark v as visited
            visited[v] = true;

            // if the toy is not assigned to a child
            if (match[v] < 0) { match[v] = u; return true; }

            // if a child that already was assigned to this toy has another option of toy in interest
            if(findMatching(graph, match[v], visited, match)) { match[v] = u; return true; }
        }
    }

    return false;
}

// maximum number of matchings from children to toys 
// of matching from N to M
int maxBipartiteMatchingFlow(bool graph[N_MAX][M_MAX]) {
    // store children assigned to toys
    // arr[j] has the value of the children assigned to toy j
    int match[M];
  
    // all toys are avaialable (-1 initially)
    memset(match, -1, sizeof(match));
  
    // count toys already assigned
    int toys = 0;

    // for each child
    for (int u = 0; u < N; u++) {
        // Mark all jobs as not visited  
        // for next applicant. 
        bool visited[N];
        memset(visited, 0, sizeof(visited));
  
        // Find if the applicant 'u' can get a job 
        if (findMatching(graph, u, visited, match))
            toys++;
    }

    return toys;
}

// main function
int main() {
    // graph declaration
    bool graph[N_MAX][M_MAX];

    // receiving N, M and L as inputs
    cin >> N >> M >> L;

    // receiving L pairs and creating edges on graph
    for (int i = 0; i < L; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(graph, u, v);
    }

    // print the maximum matching number
    cout << maxBipartiteMatchingFlow(graph) << "\n";

    return 0;
}
