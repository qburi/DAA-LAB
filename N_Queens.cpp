#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    int n;

    // We change 'blacklisted' from bool to int
    // 0 = Safe
    // 1+ = Attacked (Higher number = attacked by multiple queens)
    void solve(int row, vector<vector<int>>& attackCounts, vector<string>& candidate) {
        // Base Case: If we have moved past the last row, we found a solution
        if (row == n) {
            ans.push_back(candidate);
            return;
        }

        // Try every column in the current row
        for (int col = 0; col < n; col++) {
            // Check if the spot is safe (0 means no queen is attacking this spot)
            if (attackCounts[row][col] == 0) {

                // 1. PLACE QUEEN
                candidate[row][col] = 'Q';
                // Mark the board with +1 (add danger)
                markBoard(attackCounts, row, col, +1);

                // 2. RECURSE to the next row
                solve(row + 1, attackCounts, candidate);

                // 3. BACKTRACK
                // Unmark the board with -1 (remove danger)
                markBoard(attackCounts, row, col, -1);
                candidate[row][col] = '.';
            }
        }
    }

    // This is your 'listTheMatrix' function, but now it accepts a 'delta' (+1 or -1)
    void markBoard(vector<vector<int>>& attackCounts, int r, int c, int delta) {
        // 1. Mark the Row and Column
        for (int i = 0; i < n; i++) {
            attackCounts[r][i] += delta; // Mark row
            attackCounts[i][c] += delta; // Mark col
        }

        // 2. Mark Diagonals
        // We use simple directions: Top-Left, Top-Right, Bottom-Left, Bottom-Right

        // Directions array: {row_change, col_change}
        int dr[] = {-1, -1, 1, 1};
        int dc[] = {-1, 1, -1, 1};

        for(int k=0; k<4; k++) {
            int newR = r + dr[k];
            int newC = c + dc[k];

            // Move in that direction until we hit the wall
            while(newR >= 0 && newR < n && newC >= 0 && newC < n) {
                attackCounts[newR][newC] += delta;
                newR += dr[k];
                newC += dc[k];
            }
        }

        // Note: The loop above marks the Queen's own spot multiple times.
        // This is fine because we never check the spot the queen is currently sitting on,
        // we only check the next empty rows.
    }

    vector<vector<string>> solveNQueens(int n) {
        this->ans.clear();
        this->n = n;
        vector<string> candidate(n, string(n, '.'));

        // Use Integers instead of Booleans!
        vector<vector<int>> attackCounts(n, vector<int>(n, 0));

        // Start from Row 0
        solve(0, attackCounts, candidate);

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