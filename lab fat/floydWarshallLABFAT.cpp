#include <bits/stdc++.h>

using namespace std;

#define INF 99999

class Solution {
public:
    void solution(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == INF) {
                    cout << "INF ";
                }
                else cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n, INF));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string ip;
            cin >> ip;
            if (ip != "INF") {
                matrix[i][j] = stoi(ip);
            }
        }
    }
    
    Solution solution;
    solution.solution(matrix);
    return 0;
}