#include <bits/stdc++.h>

using namespace std;

// Translated from your custom Union-Find logic
int findSet(int p, vector<int>& id) {
    int root = p;
    // Find the root
    while (root != id[root]) {
        root = id[root];
    }

    // Path compression (Two-pass approach just like your Java code)
    while (p != root) {
        int next = id[p];
        id[p] = root;
        p = next;
    }

    return root;
}

bool unionSets(int p, int q, vector<int>& id, int& numberOfConnectedComponents) {
    int root1 = findSet(p, id);
    int root2 = findSet(q, id);

    if (root1 == root2) return false;

    // Union by setting root1's parent to root2
    id[root1] = root2;
    numberOfConnectedComponents--;
    return true;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    if (!(cin >> V >> E)) return 0;

    vector<pair<int, int>> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    // Seed the random number generator as per assignment instructions
    srand(time(NULL));

    int globalMinCut = E; // The max possible cut is all edges
    int iterations = 500; // Requirement: at least 500 times

    // Array to hold indices of edges for efficient random selection
    vector<int> edgeIndices(E);
    iota(edgeIndices.begin(), edgeIndices.end(), 0);

    for (int i = 0; i < iterations; i++) {
        vector<int> id(V);
        for (int v = 0; v < V; v++) {
            id[v] = v;
        }

        int numberOfConnectedComponents = V;

        // Shuffle edge indices to simulate picking a random edge
        // without getting stuck picking already contracted edges.
        random_shuffle(edgeIndices.begin(), edgeIndices.end());

        // Contract edges until only 2 vertices (components) remain
        for (int idx : edgeIndices) {
            if (numberOfConnectedComponents <= 2) break;

            int u = edges[idx].first;
            int v = edges[idx].second;

            // Your union logic
            unionSets(u, v, id, numberOfConnectedComponents);
        }

        // Count the crossing edges between the 2 remaining super-vertices
        int currentCut = 0;
        for (int j = 0; j < E; j++) {
            int root1 = findSet(edges[j].first, id);
            int root2 = findSet(edges[j].second, id);
            if (root1 != root2) {
                currentCut++;
            }
        }

        if (currentCut < globalMinCut) {
            globalMinCut = currentCut;
        }
    }

    // Output format strictly requires ONLY the integer
    cout << globalMinCut << "\n";

    return 0;
}