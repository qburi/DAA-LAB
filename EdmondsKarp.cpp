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
    int bfs(int V, int source, int sink, vector<vector<Edge*>>& adj) {
        vector<bool> visited(V, false);
        // We need this to trace the path backwards from sink to source
        vector<Edge*> parentEdge(V, nullptr);
        queue<int> q;

        q.push(source);
        visited[source] = true;

        // Standard BFS loop
        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            if (curr == sink) break; // Reached the sink, stop searching

            for (Edge* edge : adj[curr]) {
                if (!visited[edge->to] && edge->remainingCapacity() > 0) {
                    visited[edge->to] = true;
                    parentEdge[edge->to] = edge; // Leave a breadcrumb
                    q.push(edge->to);
                }
            }
        }

        // If we never reached the sink, no augmenting path exists
        if (parentEdge[sink] == nullptr)
            return 0;

        // Step 1: Trace back to find the bottleneck capacity
        int bottleNeck = INT_MAX;
        int curr = sink;
        while (curr != source) {
            Edge* edge = parentEdge[curr];
            bottleNeck = min(bottleNeck, edge->remainingCapacity());
            // Move backward: the 'from' node of this edge is the 'to' node of its residual
            curr = edge->residualEdge->to;
        }

        // Step 2: Trace back again to actually augment the flow
        curr = sink;
        while (curr != source) {
            Edge* edge = parentEdge[curr];
            edge->augment(bottleNeck); // This updates forward AND residual!
            curr = edge->residualEdge->to;
        }

        return bottleNeck;
    }

    int edmondsKarp(int V, int source, int sink, vector<vector<Edge*>>& adj) {
        int maxFlow = 0;

        while (true) {
            // BFS handles visited internally now, so just call it
            int flow = bfs(V, source, sink, adj);

            if (flow == 0)
                break; // no more augmenting paths

            maxFlow += flow;
        }

        return maxFlow;
    }
};

int main() {
    // Time complexity: O(V * E^2)
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

    cout << "Maximum Flow (Edmonds-Karp): " << solution.edmondsKarp(V, 0, 5, adj) << endl;

    return 0;
}