// gustavo collaco - 111851 - graph theory
#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

#define maximum 10000
#define inf numeric_limits<int>::max()

// graph - adjacency list
vector<vector<pair<int, int>>>graph(maximum * 2 + 1);

// distance to every node
vector<int> dist(maximum * 2, inf);

// odd x representation
int odd(int x) { return x + maximum; }

// pushing the edges
void addEdge(int a, int b, int w) {
    graph[a].push_back({ odd(b), w });
    graph[odd(a)].push_back({ b, w });
    graph[odd(b)].push_back({ a, w });
    graph[b].push_back({ odd(a), w });
}

// dijkstra from src do dest points
int dijkstra(int src, int dest) {
    // priority queue - distance nodes
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;

    // push first node to queue and set dist to 0
    queue.push({ 0, src });
    dist[src] = 0;

    // while can loop
    while (!queue.empty()) {
        // get node from top of queue
        int u = queue.top().second;
        queue.pop();

        // go to all neighbours of u
        for (pair<int, int> pair : graph[u]) {
            // v is the node and w the weight
            int v = pair.first;
            int w = pair.second;

            // check if there is a shorter path to v through u
            if (dist[u] + w < dist[v]) {
                // updating distance of v
                dist[v] = dist[u] + w;
                queue.push({ dist[v], v });
            }
        }
    }

    // returning shorter dist to dest
    return dist[dest];
}

// main
int main() {
    // N -> islands, M -> pairs of islands
    int N, M;
    cin >> N >> M;
        // Receiving inputs for each edge of the graph
    for (int i = 0; i < M; i++) {
        int point_one, point_two, weight;
        cin >> point_one >> point_two >> weight;
        addEdge(point_one, point_two, weight);
    }

    int src = 1;
    int dest = N;
    int res = dijkstra(src, dest);

    // if answer not found, show -1 else show result
    if (res == inf) cout << "-1" << "\n";
    else cout << res << "\n";

    return 0;
}