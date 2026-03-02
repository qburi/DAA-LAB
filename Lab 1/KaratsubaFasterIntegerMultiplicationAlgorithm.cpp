#include <bits/stdc++.h>


using namespace std;

#define ll long long

class Solution {
public:
    ll powerOfTen(ll n) {
        ll res = 1;
        for (int i = 0; i < n; i++) {
            res *= 10;
        }
        return res;
    }

    ll multiply(ll x, ll y) {
        if (x < 10 || y < 10)
            return x * y;

        ll n = max(to_string(abs(x)).length(), to_string(abs(y)).length());
        ll half = n / 2;
        ll multiplier = powerOfTen(half);
        ll a = x / multiplier;
        ll b = x % multiplier;
        ll c = y / multiplier;
        ll d = y % multiplier;

        ll ac = multiply(a, c);
        ll bd = multiply(b, d);
        ll ad_plus_bc = multiply(a + b, c + d) - ac - bd;
        return ac * powerOfTen(2 * half) + (ad_plus_bc * multiplier) + bd;
    }
};


int main() {
    Solution sol;

    vector<pair<ll, ll>> testCases = {
        {1234, 5678},       // Standard even digits
        {123, 45},          // Mismatched and odd digits
        {12345, 67890},     // Larger numbers
        {9999, 9999},       // Max digits for 4-length
        {9, 9}              // Base case trigger
    };

    for (auto& [x, y] : testCases) {
        ll expected = x * y;
        ll result = sol.multiply(x, y);

        cout << "Input:   " << x << " * " << y << "\n";
        cout << "Result:  " << result << "\n";
        cout << (result == expected ? "✅ PASS" : "❌ FAIL") << "\n\n";
    }

    return 0;
}


//
// int main() {
//     Solution solution = Solution();
//     ll x;
//     ll y;
//     cout << "Enter two numbers: " << endl;
//     cin >> x >> y;
//     cout << solution.multiply(x, y) << endl;
//     return 0;
// }
