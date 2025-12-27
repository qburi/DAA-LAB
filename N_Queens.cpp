#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    vector<vector<string>> ans;
    int n;

    // track blacklisted locations
    vector<bool> d1; // Main Diagonal -> row - col = constant
    vector<bool> d2; // Anti diagonal -> row + col = constant
    vector<bool> cols;

    void solve(int row, vector<string>& candidate) {
        if (row == n) {
            // we have filled rows from 0 to n - 1
            ans.push_back(candidate);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (! cols[col] && ! d1[row + col] && ! d2[row - col + n]) {
                d1[row + col] = true;
                d2[row - col + n] = true;
                cols[col] = true;
                candidate[row][col] = 'Q';

                solve(row + 1, candidate);
                d1[row + col] = false;
                d2[row - col + n] = false;
                cols[col] = false;
                candidate[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        d1.assign(2 * n, false);
        d2.assign(2* n, false);
        cols.assign(n, false);
        this->n = n;

        vector<string> candidate(n, string(n, '.'));
        solve(0, candidate);
        return ans;
    }
};


int main() {
    Solution* solution = new Solution();
    int N = 4;
    vector<vector<string>> sol = solution->solveNQueens(N);

    cout << "Found " << sol.size() << " solutions for N=" << N << ":\n\n";

    for (auto& list: sol ) {
        for (auto& s: list) {
            cout << s << endl;
        }
        cout << endl;
    }
    delete solution;
    return 0;
}