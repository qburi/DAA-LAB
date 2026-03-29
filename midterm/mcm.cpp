#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void matrixChainMultiplication(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 1e7));
        vector<vector<int>> split(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
            dp[i][i] = 0;

        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j < n; j++) {
                for (int k = i; k < j; k++) {
                    int cost = arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j];

                    if (cost < dp[i][j]) {
                        split[i][j] = k;
                        dp[i][j] = cost;
                    }
                }
            }
        }

        cout << dp[1][n - 1] << endl;

        printAns(1, n - 1, split);
    }

    void printAns(int i, int j, vector<vector<int>>& split) {
        if (i == j) {
            cout << "A" << i;
            return;
        }

        cout << "(";
        printAns(i, split[i][j], split);
        printAns(split[i][j] + 1, j, split);
        cout << ")";
    }
};


int main() {
    int n;
    cin >> n;
    n++;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    Solution solution;
    solution.matrixChainMultiplication(arr);
    return 0;
}