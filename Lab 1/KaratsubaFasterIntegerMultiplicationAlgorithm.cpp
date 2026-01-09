#include <bits/stdc++.h>


using namespace std;


class Solution {
public:
    long long powerOfTen(long long n) {
        long long res = 1;
        for (int i = 0; i < n; i++) {
            res *= 10;
        }
        return res;
    }

    long long multiply(long long x, long long y) {
        if (x < 10 || y < 10)
            return x * y;

        long long n = max(to_string(abs(x)).length(), to_string(abs(y)).length());
        long long half = n / 2;
        long long multiplier = powerOfTen(half);
        long long a = x / multiplier;
        long long b = x % multiplier;
        long long c = y / multiplier;
        long long d = y % multiplier;

        long long ac = multiply(a, c);
        long long bd = multiply(b, d);
        long long ad_plus_bc = multiply(a + b, c + d) - ac - bd;
        return ac * powerOfTen(2 * half) + (ad_plus_bc * multiplier) + bd;
    }
};

int main() {
    Solution solution = Solution();
    long long x;
    long long y;
    cout << "Enter two numbers: " << endl;
    cin >> x >> y;
    cout << solution.multiply(x, y) << endl;
    return 0;
}
