#include <bits/stdc++.h>


using namespace std;


class Solution {
public:

    int solve(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
        if (i == j)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int minSum = INT_MAX;
        for (int k = i; k < j; k++) {
            minSum = min(minSum, arr[i - 1] * arr[k] * arr[j] + solve(i, k, arr, dp) + solve(k + 1, j, arr, dp));
        }

        dp[i][j] = minSum;
        return minSum;
    }

    int mcm(vector<int> arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        return solve(1, n - 1, arr, dp);
    }
};


int main() {
    int n;
    cin >> n;
    n++;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    Solution solution;
    int output = solution.mcm(arr);
    cout << output << endl;

    return 0;
}