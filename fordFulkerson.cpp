#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to;
    int capacity;
    int flow;
    Edge* residualEdge;

    Edge(int to, int capacity) {
        flow = 0;
        this->to = to;
        this->capacity = capacity;
        residualEdge = nullptr;
    }

    int remainingCapacity() {
        return capacity - flow;
    }

    void augment(int bottleNeck) {
        flow += bottleNeck;
        residualEdge->flow -= bottleNeck;
    }

    static void addEdge(vector<vector<Edge*>>& adj, int from, int to, int capacity) {
        // from -> to : forward edge
        // to -> from : backward edge
        Edge* forward = new Edge(to, capacity);
        Edge* backward = new Edge(from, 0);

        forward->residualEdge = backward;
        backward->residualEdge = forward;

        adj[from].push_back(forward);
        adj[to].push_back(backward);
    }
};

class Solution {
public:
    int dfs(int from, int sink, int currentFlow, vector<bool>& visited, vector<vector<Edge*>>& adj) {
        if (from == sink)
            return currentFlow;

        visited[from] = true;

        for (Edge* edge: adj[from]) {

            if (! visited[edge->to] && edge->remainingCapacity() > 0) {
                int bottleNeck = dfs(edge->to, sink, min(currentFlow, edge->remainingCapacity()), visited, adj);

                if (bottleNeck > 0) {
                    edge->augment(bottleNeck);
                    return bottleNeck;
                }
            }

        }

        // no path
        return 0;
    }
    int fordFulkerson(int V, int source, int sink, vector<vector<Edge*>>& adj) {
        int maxFlow = 0;

        while (true) {
            vector<bool> visited(V, false); // needed for augmenting new paths

            // we pass int INT_MAX for currentFlow because source has infinite flow and will not act as a bottleneck.
            int flow = dfs(source, sink, INT_MAX, visited, adj);

            if (flow == 0)
                // no more augmenting paths
                break;

            maxFlow += flow;
        }

        return maxFlow;
    }
};


int main() {
    // time complexity: O(fE)
    // Space complexity: O(V + E)
    int V = 6;
    vector<vector<Edge*>> adj(V);

    Edge::addEdge(adj, 0, 1, 16);
    Edge::addEdge(adj, 0, 2, 13);
    Edge::addEdge(adj, 1, 2, 10);
    Edge::addEdge(adj, 1, 3, 12);
    Edge::addEdge(adj, 2, 1, 4);
    Edge::addEdge(adj, 2, 4, 14);
    Edge::addEdge(adj, 3, 2, 9);
    Edge::addEdge(adj, 3, 5, 20);
    Edge::addEdge(adj, 4, 3, 7);
    Edge::addEdge(adj, 4, 5, 4);

    Solution solution;

    cout << "Maximum Flow: " << solution.fordFulkerson(V, 0, 5, adj) << endl;
    return 0;
}