#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to;
    int capacity;
    int flow;
    Edge* residualEdge;

    Edge(int to, int capacity) {
        flow = 0;
        this->capacity = capacity;
        this->to = to;
        residualEdge = nullptr;
    }

    int cf() {
        // residual capacity
        return capacity - flow;
    }

    void augment(int bottleneck) {
        residualEdge->flow -= bottleneck;
        flow += bottleneck;
    }

};

class Solution {
public:
    void edmondsKarp(int v, int src, int sink, vector<vector<Edge*>>& adj)  {
        for (int i = 0; i < v; i++) {
            sort(adj[i].begin(), adj[i].end(), [](Edge* a, Edge* b) {
                return a->to < b->to;
            });
        }


        int maxFlow = 0;
        vector<Edge*> edgeTo(v, nullptr);

        while (true) {
            int flow = bfs(v, src, sink, adj, edgeTo);

            if (flow == 0) {
                break;
            }

            maxFlow += flow;

            vector<int> path;
            int currentNode = sink;

            while (currentNode != src) {
                path.push_back(currentNode);
                Edge* edge = edgeTo[currentNode];
                currentNode = edge->residualEdge->to; // we use residual edge because we want to backtrack
            }
            path.push_back(src);
            reverse(path.begin(), path.end());

            cout << "Path: " << path[0];
            for (int i = 1; i < path.size(); i++) {
                cout << " -> " << path[i];
            }
            cout << ", Flow: " << flow << "\n\n";


            // augmentation
            currentNode = sink;
            while (currentNode != src) {
                Edge* edge = edgeTo[currentNode];
                edge->augment(flow);
                currentNode = edge->residualEdge->to;
            }
        }

        cout << "Total Maximum Flow: " << maxFlow << endl;
    }

    int bfs(int v, int src, int sink, vector<vector<Edge*>>& adj, vector<Edge*>& edgeTo) {
        // returns bottleneck value
        fill(edgeTo.begin(), edgeTo.end(), nullptr);

        queue<pair<int, int>> q; // { currentNode, currentBOttleneck }
        q.push({src, INT_MAX});

        while (! q.empty()) {
            int qSize = q.size();
            for (int i = 0; i < qSize; i++) {
                auto [currentNode, currentBottleneck] = q.front(); q.pop();

                if (currentNode == sink) {
                    return currentBottleneck;
                }

                for (Edge* edge: adj[currentNode]) {
                    int to = edge->to;

                    if (edge->cf() > 0 && edgeTo[to] == nullptr && to != src) {
                        edgeTo[to] = edge;
                        q.push({to, min(currentBottleneck, edge->cf())});
                    }
                }
            }
        }

        return 0; // no augmenting paths could be found
    }
};


int main() {
    int v, m;
    cin >> v >> m;
    int src = 0;
    int sink = v - 1;
    vector<vector<Edge*>> adj(v, vector<Edge*>(0, nullptr));
    for (int i = 0; i < m; i++) {
        int u;
        int v;
        int c;
        cin >> u >> v >> c;
        Edge* edge = new Edge(v, c);
        edge->residualEdge = new Edge(u, 0);
        adj[u].push_back(edge);
    }
    Solution solution;
    solution.edmondsKarp(v, src, sink, adj);
    return 0;
}