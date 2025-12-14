#include <bits/stdc++.H>

using namespace std;

class Solution {
public:
    int solve(int i, int j, vector<int> &arr) {
        if (i == j) return 0; // 0 operations to multiply a matrix with nothing
        int minimumSteps = INT_MAX;
        for (int k = i; k < j; k++) {
            int steps = arr[i - 1] * arr[k] * arr[j] + solve(i, k, arr) + solve(k + 1, j, arr);
            minimumSteps = min(minimumSteps, steps);
        }

        return minimumSteps;
    }

    int matrixChainMultiplication(vector<int> &arr, int N) {
        return solve(1, N - 1, arr);
    }
};

int main() {
    vector<int> arr{10, 30, 5, 10};
    Solution* solution = new Solution();
    int N = arr.size();
    cout << "Minimum number of multiplications: ";
    cout << solution->matrixChainMultiplication(arr, N) << endl;

    delete solution;
    return 0;
}
