#include <bits/stdc++.h>


using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    int n;
    
    void backtrack(
        vector<string> candidate, vector<bool>& cols, vector<bool>& md, vector<bool>& ad,
        int row
        ) {
            if (row == n) {
                ans.push_back(candidate);
                return;
            }
            
            for (int i = 0; i < n; i++) {
                if (! md[i - row] && ! ad[i + row] && ! cols[i]) {
                    cols[i] = true;
                    md[i - row] = true;
                    ad[i + row] = true;
                    candidate[row][i] = 'Q';
                    backtrack(candidate, cols, md, ad, row + 1);
                    
                    cols[i] = false;
                    md[i - row] = false;
                    ad[i + row] = false;
                    candidate[row][i] = '.';
                }
            }
        }
        
    void solution(int n) {
        this->n = n;
        vector<string> candidate(n, string(n, '.'));
        vector<bool> cols(n, false);
        vector<bool> ad(2 * n + 1, false);
        vector<bool> md(2 * n + 1, false);
        backtrack(candidate, cols, md, ad, 0);
        
        bool found = false;
        vector<int> finalAns;
        for (vector<string>& q: ans) {
            for (string& s: q) {
                for (int i = 0; i < s.length(); i++) {
                    if (s[i] == 'Q') {
                        found = true;
                        finalAns.push_back(i);
                    }
                }
            }
            
            if (found)
                break;
        }
        
        for (int i = 0; i < (int)finalAns.size(); i++) {
            if (i != (int)finalAns.size() - 1) {
                cout << finalAns[i] << " ";
            }
            else cout << finalAns[i];
        }
        if (! found) {
            cout << "No Solution" << endl;
        }
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    solution.solution(n);
    return 0;
}