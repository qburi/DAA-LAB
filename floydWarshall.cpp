#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> dist;
    vector<vector<int>> pred;
    int n;

    void floydWarshall(vector<vector<int>>& graph) {
        this->n = graph.size();
        this->dist = graph;
        this->pred = vector<vector<int>>(n, vector<int>(n, -1));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] != INT_MAX && i != j)
                    pred[i][j] = i;
                // or else it rolls back to the default -1 which was already initialized
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                        continue;

                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pred[i][j] = pred[k][j];
                    }

                }
            }
        }

        // check for negative cycles
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0) {
                cout << "Negative cycles found." << endl;
                return;
            }
        }

        printDistanceMatrix();
        cout << endl;
        cout << endl;
        printPredecessorMatrix();
    }

    void printDistanceMatrix() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << "Shortest path from node " << i << " to node " << j << " is " << (dist[i][j] == INT_MAX ? "INFINITY" : to_string(dist[i][j])) << endl;
            }
        }
    }

    void printPredecessorMatrix() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && dist[i][j] != INT_MAX) {
                    cout << "Shortest path from " << i << " to " << j << ": ";
                    printPath(i, j);
                    cout << endl;
                }
            }
        }
    }

    void printPath(int u, int v) {
        if (u == v) {
            cout << u;
            return;
        }
        printPath(u, pred[u][v]);
        cout << " -> " << v;
    }
};

int main() {
    Solution solution;
    const int INF = INT_MAX;
    vector<vector<int>> graph = {
        {0,   4,   5,   INF, INF},
        {INF, 0,   INF, -2,  INF},
        {INF, INF, 0,   INF, 5},
        {INF, INF, -1,  0,   6},
        {8,   INF, INF, INF, 0}
    };
    solution.floydWarshall(graph);
    return 0;
}