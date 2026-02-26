#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    void printSolution(string s, string p, int q) {
        int m = p.length();
        int n = s.length();

        if (m > n || m == 0)
            return;

        long long d = 256;
        long long h = 1;

        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }

        long long pHash = 0;
        long long sHash = 0;

        for (int i = 0; i < m; i++) {
            // calculate initial window
            pHash = (d * (pHash) + p[i])  % q;
            sHash = (d * (sHash) + s[i])  % q;
        }
        cout << "Pattern Hash: " << pHash << endl;

        for (int i = 0; i <= n - m; i++) {
            cout << "Index " << i << ": Hash=" << sHash << endl;
            if (sHash == pHash) {
                if (s.substr(i, m) == p.substr(0, m)) {
                    cout << "Pattern found at index " << i << endl;
                }
                else
                    cout << "Spurious Hit" << endl;
            }

            if (i < n - m) {
                long long removedTerm = (h * s[i]) % q;
                long long sub = sHash - removedTerm;
                if (sub < 0) {
                    sub = (sub + q) % q;
                }
                else
                    sub = sub % q;
                sHash = (d * sub + s[i + m]) % q;
            }
        }
    }
};

int main() {
    string s;
    string p;
    int q;
    cin >> s;
    cin >> p;
    cin >> q;
    Solution solution;
    solution.printSolution(s, p, q);
    return 0;
}