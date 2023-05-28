// Copyright 2023 <Stamatie Mihai-Robert>

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::make_pair;
using std::ifstream;
using std::ofstream;
using std::priority_queue;
using std::ios_base;

const int INF = 2e9;  // Increased INF value

struct Edge {
    int to;
    int weight;
    bool isTeleported;
    int period;

    Edge(int to, int weight, bool isTeleported, int period)
        : to(to), weight(weight), isTeleported(isTeleported), period(period) {}
};

typedef vector<vector<Edge>> Graph;

vector<int> dijkstra(const Graph& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, 
    std::greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (edge.isTeleported) {
                int period = edge.period;
                int waitTime = (dist[u] % period == 0) ? 0 : (period - (dist[u] % period));
                w = waitTime + 1;
            }

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

int main() {

    ifstream inputFile("teleportare.in");
    ofstream outputFile("teleportare.out");

    int N, M, K;
    inputFile >> N >> M >> K;

    Graph graph(N + 1);

    for (int i = 0; i < M; i++) {
        int x, y, t;
        inputFile >> x >> y >> t;
        graph[x].emplace_back(y, t, false, 0);
        graph[y].emplace_back(x, t, false, 0);
    }

    for (int i = 0; i < K; i++) {
        int x, y, p;
        inputFile >> x >> y >> p;
        // Add a teleport edge between vertices x and y with a wait period of p
        graph[x].emplace_back(y, 1, true, p);
        // Add a teleport edge between vertices y and x with a wait period of p
        graph[y].emplace_back(x, 1, true, p);
    }

    // Perform Dijkstra's algorithm to find the shortest distances from vertex 1
    vector<int> dist = dijkstra(graph, 1);

    // Write the shortest distance to vertex N in the output file
    outputFile << dist[N] << '\n';

    inputFile.close();
    outputFile.close();

    return 0;
}
