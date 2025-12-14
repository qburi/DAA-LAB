#include <bits/stdc++.H>

using namespace std;

class Solution {
public:
    int solve(int i, int j, vector<int> &arr, vector<vector<int>>& dp) {
        if (i == j) return 0; // 0 operations to multiply a matrix with nothing
        if (dp[i][j] != -1) return dp[i][j];
        int minimumSteps = INT_MAX;
        for (int k = i; k < j; k++) {
            int steps = arr[i - 1] * arr[k] * arr[j] + solve(i, k, arr, dp) + solve(k + 1, j, arr, dp);
            minimumSteps = min(minimumSteps, steps);
        }
        dp[i][j] = minimumSteps;
        return minimumSteps;
    }

    int matrixChainMultiplication(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(1, n - 1, arr, dp);
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
