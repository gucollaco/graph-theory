// gustavo collaco - 111851 - graph theory
#include <iostream>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

// N_MAX is the number of children 
#define N_MAX 100

// keep the neighbours of each child (relation to toys)
vector<vector<int > >neighbours(N_MAX);

// variables to keep the number of toys, the number of children, and the qty of relationships
int N, M, L;

// DFS that returns true if it is possible to find a matching for u
bool findMatching(int u, bool visited[], int match[]) {
    // go to all neighbours of u
    for(vector<int >::iterator it = neighbours[u].begin(); it != neighbours[u].end(); ++it) {
        int v = (*it);
        // if child u is interested in toy v and the toy is not yet visited
        if (!visited[v]) {
            // Mark v as visited
            visited[v] = true;

            // if the toy is not assigned to a child or
            // if a child that already was assigned to this toy has another option of toy in interest
            if (match[v] < 0 || findMatching(match[v], visited, match)) { match[v] = u; return true; }
        }
    }

    return false;
}

// maximum number of matchings from children to toys 
// of matching from N to M
int maxBipartiteMatchingFlow() {
    // store children assigned to toys
    // arr[j] has the value of the children assigned to toy j
    int match[M];
  
    // all toys are avaialable (-1 initially)
    memset(match, -1, sizeof(match));
  
    // count toys already assigned
    int toys = 0;

    // for each child
    for (int u = 0; u < N; u++) {
        // mark all toys possible as not checked
        // for next child 
        bool visited[M];
        memset(visited, 0, sizeof(visited));
  
        // check if u can get a toy
        if (findMatching(u, visited, match)) toys++;
    }

    return toys;
}

// main function
int main() {
    // receiving N, M and L as inputs
    cin >> N >> M >> L;

    // receiving L pairs and creating edges on graph
    for (int i = 0; i < L; i++) {
        int u, v;
        cin >> u >> v;
        neighbours[u].push_back(v);
    }

    // print the maximum matching number
    cout << maxBipartiteMatchingFlow() << "\n";

    return 0;
}

