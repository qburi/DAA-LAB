#include <bits/stdc++.h>


using namespace std;

#define INF 99999

struct Edge {
  int u;
  int v;
  int wt;
  Edge(int u, int v, int wt) : u(u), v(v), wt(wt) {}
};

class Solution {
public:
    void sssp(int n, int src, vector<vector<pair<int, int>>>& adj) {
        vector<int> dist(n, INF);
        dist[src] = 0;
        
        auto cmp = [&](pair<int, int>& left, pair<int, int>& right) {
            return left.second > right.second;
        };
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp); // { node, distance }
        
        pq.push({src, 0});
        
        while (! pq.empty()) {
            auto p = pq.top(); pq.pop();
            int node = p.first;
            int currentDistance = p.second;
            if (dist[node] < currentDistance)
                continue;
            
            
            for (auto& neighbor: adj[node]) {
                int newNode = neighbor.first;
                int newDistance = neighbor.second + currentDistance;
                if (newDistance < dist[newNode]) {
                    pq.push({newNode, newDistance});
                    dist[newNode] = newDistance;
                }
            }
        }
        
        // dijkstra end
        
        // belmman ford
        vector<Edge> edges;
        for (int i = 0; i < n; i++) {
            for (auto& p: adj[i]) {
                int v = p.first;
                int wt = p.second;
                edges.push_back(Edge(i, v, wt));
            }
        }
        
        vector<int> distances(n, INF);
        distances[src] = 0;
        
        for (int k = 1; k < n; k++) {
            bool changed = false;
            for (Edge edge: edges) {
                int u = edge.u;
                int v = edge.v;
                int wt = edge.wt;
                
                if (distances[u] != INF && distances[u] + wt < distances[v]) {
                    distances[v] = distances[u] + wt;
                    changed = true;
                }
            }
            
            if (! changed) 
                break;
        }
        
        bool negativeCycles = false;
        for (Edge edge: edges) {
            int u = edge.u;
            int v = edge.v;
            int wt = edge.wt;
                
            if (distances[u] != INF && distances[u] + wt < distances[v]) {
                negativeCycles = true;
                break;
            }
        }
        
        cout << "Dijkstra: ";
        for (int u = 0; u < n; u++) {
                cout << (dist[u] == INF ? "INF" : to_string(dist[u])) << " ";
                
        }
        cout << endl;
        cout << "Bellman-Ford: ";
        if (negativeCycles) {
            cout << "Negative Cycle Detected" << endl;
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << (distances[i] == INF ? "INF" : to_string(distances[i])) << " ";
            }
            cout << endl;
            
        }
        
    }
};

int main() {
    int v;
    int e;
    int src;
    cin >> v >> e;
    cin >> src;
    vector<vector<pair<int, int>>> adj(v, vector<pair<int, int>>());
    for (int i = 0; i < e; i++) {
        int u;
        int v;
        int wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
    }
    Solution solution;
    solution.sssp(v, src, adj);
    return 0;
}


/*
    this code gives infinite loops bug for the negative cycle test case (3)
3 3
0
0 1 1
1 2 -5
2 0 2
*/