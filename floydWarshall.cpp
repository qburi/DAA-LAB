#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Using a safe INF to avoid overflow during addition
const int INF = 1e7;
const int V = 5;

void printPath(int i, int j, const vector<vector<int>>& pred) {
    if (i == j) {
        cout << i;
        return;
    }
    if (pred[i][j] == -1) {
        cout << "No path";
        return;
    }
    printPath(i, pred[i][j], pred);
    cout << " -> " << j;
}

void floydWarshall(vector<vector<int>>& graph) {
    vector<vector<int>> dist = graph;
    vector<vector<int>> pred(V, vector<int>(V, -1));

    // --- Step 1: Initialization ---
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != INF && i != j) {
                pred[i][j] = i;
            }
        }
    }

    // --- Step 2: The Three Loops ---
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pred[i][j] = pred[k][j]; // Update predecessor
                    }
                }
            }
        }
    }

    // --- Step 3: Output and Path Reconstruction ---
    cout << "Pairwise Shortest Paths and Routes:\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                cout << i << " to " << j << " | Cost: ";
                if (dist[i][j] == INF) {
                    cout << "INF | Path: None" << endl;
                } else {
                    cout << setw(2) << dist[i][j] << " | Path: [";
                    printPath(i, j, pred);
                    cout << "]" << endl;
                }
            }
        }
    }

    // Negative Cycle Check
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            cout << "\nWARNING: GRAPH CONTAINS A NEGATIVE WEIGHT CYCLE!" << endl;
            return;
        }
    }
}

int main() {
    // Example Graph (A=0, B=1, C=2, D=3, E=4)
    vector<vector<int>> graph = {
        {0,   4,   5,   INF, INF},
        {INF, 0,   INF, -2,  INF},
        {INF, INF, 0,   INF, 5},
        {INF, INF, -1,  0,   6},
        {8,   INF, INF, INF, 0}
    };

    floydWarshall(graph);

    return 0;
}