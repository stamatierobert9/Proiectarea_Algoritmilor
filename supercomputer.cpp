// Copyright 2023 <Stamatie Mihai-Robert>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

// Function to perform BFS and calculate the maximum number of switches
int bfs(const std::vector<int>& dataset, const std::vector<std::vector<int>>& graph,
        std::vector<int>& inDegreeCount, std::vector<int>& switchCount) {
    int maxSwitches = 0;
    std::queue<int> q;

    // Enqueue nodes with zero in-degree
    for (int i = 0; i < inDegreeCount.size(); ++i) {
        if (inDegreeCount[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Traverse the neighbors of the current node
        for (int v : graph[u]) {
            --inDegreeCount[v];
            switchCount[v] = std::max(switchCount[v], switchCount[u] + (dataset[u] != dataset[v]));

            if (inDegreeCount[v] == 0) {
                q.push(v);
            }

            maxSwitches = std::max(maxSwitches, switchCount[v]);
        }
    }

    return maxSwitches;
}

int main() {
    std::ifstream input("supercomputer.in");
    std::ofstream output("supercomputer.out");

    int N, M;
    input >> N >> M;

    std::vector<int> dataset(N);
    std::vector<std::vector<int>> graph(N);
    std::vector<int> inDegreeCount(N, 0);
    std::vector<int> switchCount(N, 0);

    // Read the dataset values
    for (int i = 0; i < N; ++i) {
        input >> dataset[i];
    }

    // Build the graph and calculate in-degree counts
    for (int i = 0; i < M; ++i) {
        int u, v;
        input >> u >> v;
        --u;
        --v;
        graph[u].emplace_back(v);
        ++inDegreeCount[v];
    }

    // Perform BFS to calculate the maximum number of switches
    int maxSwitches = bfs(dataset, graph, inDegreeCount, switchCount);

    // Write the result to the output file
    output << maxSwitches << std:: endl;

    return 0;
}
