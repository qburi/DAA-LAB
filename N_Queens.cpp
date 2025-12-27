#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    int n;

    void solve(int i, int j, int placed, vector<vector<bool>> blacklisted, vector<string> candidate) {
        if (placed == n) {
            ans.push_back(candidate);
           return;
        }
        if (i < 0 || i == n || j < 0 || j == n || blacklisted[i][j]) return;

        blacklisted[i][j] = true;
        candidate[i][j] = 'Q';
        listTheMatrix(blacklisted, true, i, j);
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (! blacklisted[row][col])
                    solve(row, col, placed + 1, blacklisted, candidate);
            }
        }

        blacklisted[i][j] = false;
        listTheMatrix(blacklisted, false, i, j);
        candidate[i][j] = '.';
    }

    void listTheMatrix(vector<vector<bool>>& blacklisted, bool value, int i, int j) {
        // blacklist all reachable rows, columns and diagonals

        // 1. Blacklist all rows
        for (int row = 0; row < n; row++)
            blacklisted[row][j] = value;

        // 2. Blacklist all columns
        for (int col = 0; col < n; col++)
            blacklisted[i][col] = value;

        // 3. blacklist left diagonal -> sum is constant
        int sum = i + j;
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++)
                if (row + col == sum)
                    blacklisted[row][col] = value;

        // 4. blacklist the right diagonal
        int row = i;
        int col = j;
        while (true) {
            blacklisted[row][col] = value;
            row--;
            col--;
            if (row == 0 || col == 0) {
                blacklisted[row][col] = value;
                break;
            }
        }

        row = i;
        col = j;
        while (true) {
            blacklisted[row][col] = value;
            row++;
            col++;

            if (row == n - 1 || col == n - 1) {
                blacklisted[row][col] = value;
                break;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        this->ans = vector<vector<string>>(n, vector<string>(n, ""));
        this->n = n;
        vector<string> candidate(n, string(n, '.'));
        vector<vector<bool>> blacklisted(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                solve(i, j, 0, blacklisted, candidate);
            }
        }

        return ans;
    }
};



int main() {
    Solution* solution = new Solution();
    vector<vector<string>> sol = solution->solveNQueens(4);
    for (auto& list: sol ) {
        for (auto& s: list) {
            cout << s << endl;
        }
        cout << endl;
        cout << endl;
    }
    delete solution;
    return 0;
}