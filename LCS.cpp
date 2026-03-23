#include <bits/stdc++.h>


using namespace std;


class Solution {
public:

    void lcs(string& s, string& t) {
        int m = s.length();
        int n = t.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

                if (s[i - 1] == t[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
            }
        }

        string ans = "";
        int i = m;
        int j = n;

        while (i >= 1 && j >= 1) {
            if (s[i - 1] == t[j - 1]) {
                ans.push_back(s[i - 1]);
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            }
            else j--;
        }
        reverse(ans.begin(), ans.end());

        cout << "LCS: " << ans << endl;
        cout << "Length: " << dp[m][n] << endl;
    }
};


int main() {
    string s;
    string t;
    cin >> s >> t;

    Solution solution;
    solution.lcs(s, t);
}