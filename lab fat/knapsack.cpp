#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void solution(vector<pair<int, int>>& items, int cap) {
        int n = items.size();
        vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= cap; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                int wt = items[i - 1].first;
                int value = items[i - 1].second;

                if (j - wt >= 0 && dp[i - 1][j - wt] + value > dp[i][j])
                    dp[i][j] = dp[i - 1][j - wt] + value;
            }
        }

        cout << dp[n][cap];

    }
};

int main() {
    int n;
    int cap;
    cin >> n >> cap;
    vector<pair<int, int>> items(n);
    for (int i = 0; i < n; i++) {
        int wt;
        cin >> wt;
        items[i].first = wt;
    }
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        items[i].second = value;
    }
    Solution solution;
    solution.solution(items, cap);
    return 0;
}