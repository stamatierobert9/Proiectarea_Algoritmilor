// Copyright 2023 <Stamatie Mihai-Robert>

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int n, m, s;
int id = 1;
int sccCount = 0;
int rez = 0;
int x = 0;

vector<int> adj[100005];
stack<int> nodes_stack;
vector<int> ids;
vector<int> low;
vector<int> parent;
vector<bool> in_stack;

bool isRoot;

void dfs(int node) {
    nodes_stack.push(node);
    in_stack[node] = true;
    ids[node] = low[node] = id++;

    for (int neigh : adj[node]) {
        if (ids[neigh] == -1) {
            dfs(neigh);
        }
        if (in_stack[neigh]) {
            low[node] = min(low[node], low[neigh]);
        }
        if (low[neigh] != low[node]) {
            parent[low[neigh]]++;
        }
    }

    if (ids[node] == low[node]) {
        x = nodes_stack.top();
        nodes_stack.pop();
        in_stack[x] = false;
        while (x != node) {
            parent[ids[x]] = -1;
            low[x] = ids[node];
            if (x == node) {
                break;
            }
            x = nodes_stack.top();
            nodes_stack.pop();
            in_stack[x] = false;
        }
        sccCount++;
    }
}

int main() {
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    fin >> n >> m >> s;
    ids.resize(n + 1, -1);
    low.resize(n + 1, -1);
    parent.resize(n + 1, 0);
    in_stack.resize(n + 1, false);

    for (int node = 1; node <= n; node++) {
        adj[node].clear();
    }

    for (int i = 1, x, y; i <= m; i++) {
        fin >> x >> y;
        adj[x].push_back(y);
    }

    for (int i = 1; i <= n; i++) {
        if (ids[i] == -1) {
            dfs(i);
        }
    }

    parent[low[s]] = -2;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == 0) {
            rez++;
        }
    }

    fout << rez << endl;

    fin.close();
    fout.close();

    return 0;
}
