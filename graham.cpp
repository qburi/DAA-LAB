#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // Using your exact determinant formula:
    // | x3 - x1    x2 - x1 |
    // | y3 - y1    y2 - y1 |
    // Returns: < 0 (Left/CCW), > 0 (Right/CW), 0 (Collinear)
    long long getDeterminant(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
        long long x1 = p1.first, y1 = p1.second;
        long long x2 = p2.first, y2 = p2.second;
        long long x3 = p3.first, y3 = p3.second;

        // Casts to long long prevent integer overflow during multiplication
        return (x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1);
    }

    // Helper to calculate squared distance
    long long distSq(pair<int, int> p1, pair<int, int> p2) {
        long long dx = p1.first - p2.first;
        long long dy = p1.second - p2.second;
        return dx * dx + dy * dy;
    }

    void solution(vector<pair<int, int>>& points) {
        int n = points.size();

        // Handle degenerate cases
        if (n <= 1) {
            if (n == 1) cout << "(" << points[0].first << ", " << points[0].second << ")" << endl;
            return;
        }

        // 1. Find the starting vertex (bottom-most, tie-break with left-most)
        int minIdx = 0;
        for (int i = 1; i < n; i++) {
            if (points[i].second < points[minIdx].second ||
               (points[i].second == points[minIdx].second && points[i].first < points[minIdx].first)) {
                minIdx = i;
            }
        }

        // Swap starting point to index 0
        swap(points[0], points[minIdx]);
        pair<int, int> p0 = points[0];

        // 2. Sort the remaining points by polar angle using the determinant
        sort(points.begin() + 1, points.end(), [&](pair<int, int>& a, pair<int, int>& b) {
            long long det = getDeterminant(p0, a, b);

            if (det == 0) {
                // If collinear, keep the closer one first so the furthest gets pushed last
                return distSq(p0, a) < distSq(p0, b);
            }
            // det < 0 means 'b' is a Left turn from 'a' (CCW), so 'a' comes first
            return det < 0;
        });

        // Ensure we don't process duplicate identical points to p0
        vector<pair<int, int>> validPoints;
        validPoints.push_back(points[0]);
        for (int i = 1; i < n; i++) {
            if (points[i] != p0) {
                validPoints.push_back(points[i]);
            }
        }

        if (validPoints.size() == 1) {
            cout << "(" << p0.first << ", " << p0.second << ")" << endl;
            return;
        }

        // 3. Process the stack (using a vector as a stack for easier iteration later)
        vector<pair<int, int>> hull;
        hull.push_back(validPoints[0]);
        hull.push_back(validPoints[1]);

        for (size_t i = 2; i < validPoints.size(); i++) {
            // Pop if right turn (> 0) OR perfectly flat/collinear (== 0) -> det >= 0
            while (hull.size() > 1) {
                pair<int, int> top = hull.back();
                pair<int, int> nextToTop = hull[hull.size() - 2];

                if (getDeterminant(nextToTop, top, validPoints[i]) >= 0) {
                    hull.pop_back();
                } else {
                    break;
                }
            }
            hull.push_back(validPoints[i]);
        }

        // 4. Format Output strictly as requested
        for (size_t i = 0; i < hull.size(); i++) {
            cout << "(" << hull[i].first << ", " << hull[i].second << ")";
            if (i != hull.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<pair<int, int>> points;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    Solution solution;
    solution.solution(points);
    return 0;
}

