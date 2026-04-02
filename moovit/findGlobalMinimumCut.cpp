#include <bits/stdc++.h>


using namespace std;

int find(int p, vector<int>& id) {
    int root = p;
    while (root != id[root]) {
        root = id[root];
    }

    while (p != root) {
        int next = id[p];
        id[p] = root;
        p = next;
    }

    return root;
}

bool unify(int p, int q, vector<int>& id, int& numberOfConnectedComponents) {
    int rootP = find(p, id);
    int rootQ = find(q, id);

    if (rootP == rootQ)
        return false; // already part of the same component

    id[rootQ] = rootP;
    numberOfConnectedComponents--;
    return true;
}

int main() {
    int v, e;

    cin >> v >> e;
    vector<pair<int, int>> edges(e);
    for (int i = 0; i < e; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    srand(time(NULL));

    int globalMinCut = e;
    int iterations = 500;
    vector<int> edgeIndices(e);
    iota(edgeIndices.begin(), edgeIndices.end(), 0);

    for (int i = 0; i < iterations; i++) {
        vector<int> id(v);
        for (int i = 0; i < v; i++)
            id[i] = i;

        int numberOfConnectedComponents = v;
        random_shuffle(edgeIndices.begin(), edgeIndices.end());

        for (int idx: edgeIndices) {
            if (numberOfConnectedComponents <= 2) break;

            int u = edges[idx].first;
            int v = edges[idx].second;

            unify(u, v, id, numberOfConnectedComponents);
        }

        int currentCut = 0;
        for (int j = 0; j < e; j++) {
            int rootP = find(edges[j].first, id);
            int rootQ = find(edges[j].second, id);
            if (rootP != rootQ) {
                currentCut++;
            }
        }

        if (currentCut < globalMinCut) {
            globalMinCut = currentCut;
        }
    }

    cout << globalMinCut << "\n";
    return 0;
}
