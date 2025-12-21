#include <bits/stdc++.h>

using namespace std;


/**
 * Calculates the minimum time to pass through the assembly lines.
 *
 * @param a 2D array where a[0] is Line 1 processing times, a[1] is Line 2.
 * @param t 2D array where t[0] is transfer FROM Line 1, t[1] is transfer FROM Line 2.
 * @param e Entry times for Line 1 and Line 2.
 * @param x Exit times for Line 1 and Line 2.
 * @return The minimum total time.
 */
int assemblyLineScheduling(vector<vector<int>>& a, vector<vector<int>>& t, int entry1, int entry2, int exit1, int exit2) {
    const int n = a[0].size(); // the number of stations
    vector<int> f1(n, 0);
    vector<int> f2(n, 0);

    f1[0] = a[0][0] + entry1;
    f2[0] = a[1][0] + entry2;

    // already processed station 1
    for (int j = 1; j < n; j++) {
        f1[j] = min(f1[j - 1] + a[0][j], f2[j - 1] + t[1][j - 1] + a[0][j]);
        f2[j] = min(f2[j - 1] + a[1][j], f1[j - 1] + t[0][j - 1] + a[1][j]);
    }

    return min(f1[n - 1] + exit1, f2[n - 1] + exit2);
}


int main() {
    vector<vector<int>> a = {
        {2, 8, 9, 3, 6, 1},
        {4, 3, 2, 1, 7, 3}
    };

    // FIX: Updated Row 0 to match Slide Page 18 (2, 3, 1, 3, 4)
    vector<vector<int>> t = {
        {2, 3, 1, 3, 4}, // Transfer FROM Line 1 TO Line 2
        {2, 1, 2, 2, 1}  // Transfer FROM Line 2 TO Line 1
    };

    vector<int> e = {4, 2};
    vector<int> x = {3, 7};

    // FIX: Corrected indices for exit array (x[0], x[1])
    cout << "Minimum time: "
            << assemblyLineScheduling(a, t, e[0], e[1], x[0], x[1]) << endl;

    return 0;
}