#include <bits/stdc++.h>


using namespace std;


class Solution {
public:
    void als(vector<int>& a1, vector<int>& a2, vector<int>& t1, vector<int>& t2, int e1, int e2, int x1, int x2) {
        int n = a2.size();
        vector<int> f1(n, 0);
        vector<int> f2(n, 0);

        f1[0] = e1 + a1[0];
        f2[0] = e2 + a2[0];

        for (int i = 1; i < n; i++) {
            f1[i] = min(f1[i - 1] + a1[i], f2[i - 1] + t2[i - 1] + a1[i]);
            f2[i] = min(f2[i - 1] + a2[i], f1[i - 1] + t1[i - 1] + a2[i]);
        }


        cout << min(f1[n - 1] + x1, f2[n - 1] + x2) << endl;
    }
};


int main() {
    Solution solution;
    int n;
    cin >> n;
    int e1, e2;
    cin >> e1 >> e2;
    int x1, x2;
    cin >> x1 >> x2;
    vector<int> a1(n, 0);
    vector<int> a2(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a2[i];
    }

    vector<int> t1(n - 1, 0);
    vector<int> t2(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        cin >> t1[i];
    }

    for (int i = 0; i < n - 1; i++) {
        cin >> t2[i];
    }
    solution.als(a1, a2, t1, t2, e1, e2, x1, x2);
    return 0;
}