#include <bits/stdc++.h>


using namespace std;


class Solution {
public:
    long long multiply(long long x, long long y) {
        if (x < 10 || y < 10)
            return x * y;

        long long n = max(to_string(x).length(), to_string(y).length());
        long long half = n / 2;
        long long a = x / pow(10, half);
        long long b = x % (long long) pow(10, half);
        long long c = y / pow(10, half);
        long long d = y % (long long) pow(10, half);

        long long ac = multiply(a, c);
        long long bd = multiply(b, d);
        long long ad_plus_bc = multiply(a + b, c + d) - ac - bd;
        return ac * pow(10, 2 * half) + (ad_plus_bc * pow(10, half)) + bd;
    }
};

int main() {
    Solution solution = Solution();
    cout << solution.multiply(200, 8) << endl;
    return 0;
}
