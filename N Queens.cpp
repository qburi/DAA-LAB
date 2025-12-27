#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    int n;


    vector<vector<string>> solveNQueens(int n) {
        this->ans = vector<vector<string>>(n, vector<string>(n, ""));
        this->n = n;
    }
};

int main() {
    return 0;
}