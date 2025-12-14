#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int matrixChainMultiplication(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
        for (int i = 1; i < n; i++)
            dp[i][i] = 0; // base case
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j < n; j++) {
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j]);
                }
            }
        }

        return dp[1][n - 1];
    }
};

int main() {
    vector<int> arr{10, 30, 5, 60};
    Solution* solution = new Solution();
    cout << "Minimum number of multiplications: ";
    cout << solution->matrixChainMultiplication(arr) << endl;

    delete solution;
    return 0;
}
