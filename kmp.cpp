#include <bits/stdc++.h>

using namespace std;


class Solution {
public:

    void printSolution(string s, string p) {
        int n = s.length();
        int m = p.length();
        int i = 1;
        vector<int> lps(m, 0);
        int len = 0;

        while (i < m) {
            if (p[i] == p[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if (len > 0) {
                    len = lps[len - 1];
                }
                else {
                    i++;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            cout << lps[i] << " ";
        }
        cout << endl;

        i = 0;
        int j = 0;
        while (i < n) {
            if (s[i] == p[j]) {
                i++;
                j++;
            }
            if (j == m) {
                cout << "Pattern found at index " << i - m << endl;
                j = lps[j - 1];
            }
            else if (i < n && s[i] != p[j]) {
                if (j != 0) {
                    cout << "Shift: j=" << j << " -> " << lps[j - 1] << endl;
                    j = lps[j - 1];
                }
                else {
                    i++;
                }
            }
        }
    }
};

int main() {
    string s;
    string p;
    cin >> s;
    cin >> p;
    Solution solution;
    solution.printSolution(s, p);
    return 0;
}