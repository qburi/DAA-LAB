#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Structure to represent an edge connecting u and v
struct Edge {
    int u, v;
};

// Disjoint Set (Union-Find) data structure with path compression and union by rank
struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initialize each vertex to be its own parent
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        // Path compression
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            // Union by rank
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

// Function to run a single iteration of Karger's algorithm
int kargerSingleIteration(int V, int E, const vector<Edge>& edges) {
    DisjointSet dsu(V);
    int vertices_left = V;

    // Keep contracting edges until only 2 vertices remain
    while (vertices_left > 2) {
        // Pick a random edge
        int random_edge_idx = rand() % E;
        int u = edges[random_edge_idx].u;
        int v = edges[random_edge_idx].v;

        int set1 = dsu.find(u);
        int set2 = dsu.find(v);

        // If the edge connects two different sets, contract it
        if (set1 != set2) {
            vertices_left--;
            dsu.unite(set1, set2);
        }
    }

    // Count the number of crossing edges between the 2 remaining super-vertices
    int cut_edges = 0;
    for (int i = 0; i < E; ++i) {
        int set1 = dsu.find(edges[i].u);
        int set2 = dsu.find(edges[i].v);
        // If the endpoints belong to different sets, it's a cut edge
        if (set1 != set2) {
            cut_edges++;
        }
    }

    return cut_edges;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E;
    if (!(cin >> V >> E)) return 0;

    vector<Edge> edges(E);
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].u >> edges[i].v;
    }

    // Seed the random number generator
    srand(time(NULL));

    int min_cut = E + 1; // Initialize with a value larger than any possible cut
    int iterations = 500; // Mandatory number of iterations as per assignment

    for (int i = 0; i < iterations; ++i) {
        min_cut = min(min_cut, kargerSingleIteration(V, E, edges));
    }

    // Print ONLY the final integer
    cout << min_cut << "\n";

    return 0;
}