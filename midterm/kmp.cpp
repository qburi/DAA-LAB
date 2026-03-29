#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void solution(string& text, string& pattern) {
        int m = pattern.length();
        int n = text.length();
        int i = 1;
        int len = 0;
        vector<int> lps(m, 0);

        while (i < m) {
            if (pattern[i] == pattern[len]) {
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

        for (int i = 0; i < m - 1; i++)
            cout << lps[i] << " ";
        cout << lps[m - 1] << endl;

        int j = 0;
        i = 0;

        while (i < n) {
            if (text[i] == pattern[j]) {
                i++;
                j++;
            }

            if (j == m) {
                cout << "Pattern found at index " << (i - m) << endl;
                cout << "Shift: j=" << j << " -> " << lps[j - 1] << endl;
                j = lps[j - 1];
            }
            else if (i < n && text[i] != pattern[j]) {
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
    string text;
    string pattern;
    cin >> text >> pattern;
    Solution solution;
    solution.solution(text, pattern);
    return 0;
}