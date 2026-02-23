#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to;
    int capacity;
    int flow;
    Edge* residual; // Pointer to the residual edge

    Edge(int to, int capacity) {
        this->to = to;
        this->capacity = capacity;
        this->flow = 0;
        this->residual = nullptr;
    }

    int remainingCapacity() {
        return capacity - flow;
    }

    void augment(int bottleneck) {
        flow += bottleneck;
        residual->flow -= bottleneck;
    }
};

void addEdge(vector<vector<Edge*>>& adj, int from, int to, int capacity) {
    Edge* e1 = new Edge(to, capacity);
    Edge* e2 = new Edge(from, 0); // Residual edge starts with 0 capacity

    // Cross-link the pointers
    e1->residual = e2;
    e2->residual = e1;

    adj[from].push_back(e1);
    adj[to].push_back(e2);
}

// DFS to find augmenting paths
int dfs(int u, int t, int current_flow, vector<vector<Edge*>>& adj, vector<bool>& visited) {
    if (u == t)
        // we have reached the sink
        return current_flow;

    visited[u] = true;

    // Notice the pointer syntax (*) and (->)
    for (Edge* edge : adj[u]) {
        if (!visited[edge->to] && edge->remainingCapacity() > 0) {

            int bottleneck = dfs(edge->to, t, min(current_flow, edge->remainingCapacity()), adj, visited);

            if (bottleneck > 0) {
                edge->augment(bottleneck); // Automatically handles the residual!
                return bottleneck;
            }
        }
    }
    return 0;
}

int fordFulkerson(int V, int source, int sink, vector<vector<Edge*>>& adj) {
    int max_flow = 0;

    while (true) {
        vector<bool> visited(V, false);
        int flow = dfs(source, sink, INT_MAX, adj, visited);

        if (flow == 0)
            // no more augmenting paths
            break;

        max_flow += flow;
    }

    return max_flow;
}

int main() {
    int V = 6;
    vector<vector<Edge*>> adj(V);

    addEdge(adj, 0, 1, 16);
    addEdge(adj, 0, 2, 13);
    addEdge(adj, 1, 2, 10);
    addEdge(adj, 1, 3, 12);
    addEdge(adj, 2, 1, 4);
    addEdge(adj, 2, 4, 14);
    addEdge(adj, 3, 2, 9);
    addEdge(adj, 3, 5, 20);
    addEdge(adj, 4, 3, 7);
    addEdge(adj, 4, 5, 4);

    cout << "Maximum Flow: " << fordFulkerson(V, 0, 5, adj) << endl;

    // Note: In a production C++ app, we would write a loop here to 'delete'
    // all the 'new Edge' pointers to prevent memory leaks. For a timed lab exam,
    // the OS cleans it up when the program exits, so we skip it to save time.

    return 0;
}