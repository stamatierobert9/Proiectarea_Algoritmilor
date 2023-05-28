// Copyright 2023 <Stamatie Mihai-Robert>

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Graph {
public :

    vector<vector<int>> adj;
    vector<int> start;
    vector<int> finish;

    void addEdge(int v, int w);
    void DFS(int v, vector<int>& order);
    int road = 0;
};

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::DFS(int v, vector<int>& order) {
    road++;
    start[v] = road;
    order.push_back(v);

    for (int i : adj[v]) {
        if (start[i] == 0) {
            DFS(i, order);
        }
    }

    finish[v] = road;
}

int main() {
    Graph g;

    ifstream inputFile("magazin.in");
    ofstream outputFile("magazin.out");

    int N, Q, k, D, E;

    inputFile >> N >> Q;

    vector<int> order;

    g.adj.resize(N + 1);
    g.start.resize(N + 1);
    g.finish.resize(N + 1);

    for (int i = 2; i <= N; i++) {
        inputFile >> k;
        g.addEdge(k, i);
    }

    g.DFS(1, order);

    for (int i = 0; i < Q; i++) {
        inputFile >> D >> E;
        int result = -1;
        int diff = g.finish[D] - g.start[D];
        if (diff >= E && order.size() > g.start[D] + E - 1) {
            result = order[g.start[D] + E - 1];
        }
        outputFile << result << '\n';
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
