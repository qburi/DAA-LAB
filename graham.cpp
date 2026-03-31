#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int getDeterminant(pair<int, int>& p1, pair<int, int>& p2, pair<int, int>& p3) {
        int x1 = p1.first;
        int y1 = p1.second;
        int x2 = p2.first;
        int y2 = p2.second;
        int x3 = p3.first;
        int y3 = p3.second;

        return (x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1);
    }

    int distSq(pair<int, int>& p1, pair<int, int>& p2) {
        int x1 = p1.first;
        int x2 = p2.first;
        int y1 = p1.second;
        int y2 = p2.second;
        int d1 = x1 - x2;
        int d2 = y1 - y2;
        return d1 * d1 + d2 * d2;
    }

    void solution(vector<pair<int, int>>& points) {
        int n = points.size();

        if (n <= 1) {
            if (n == 1)
                cout << "(" << points[0].first << ", " << points[0].second << ")";
            return;
        }

        int minIndex = 0;
        for (int i = 1; i < n; i++) {
            if (points[i].second < points[minIndex].second ||
                (points[i].second == points[minIndex].second &&
                points[i].first < points[minIndex].first)) {
                    minIndex = i;
                }
        }

        swap(points[minIndex], points[0]);
        pair<int, int> p0 = points[0]; // lowest point
        sort(points.begin() + 1, points.end(), [&](pair<int, int>& left, pair<int, int>& right) {
            int det = getDeterminant(p0, left, right);

            if (det == 0) {
                return distSq(p0, left) < distSq(p0, right);
            }

            return det < 0;
        });

        vector<pair<int, int>> hull;
        hull.push_back(points[0]);
        hull.push_back(points[1]);

        for (int i = 2; i < n; i++) {

            while (hull.size() > 1) {
                if (getDeterminant(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) >= 0) {
                    hull.pop_back();
                }
                else break;
            }
            hull.push_back(points[i]);
        }

        for (int i = 0; i < hull.size() - 1; i++) {
            cout << "(" << hull[i].first << ", " << hull[i].second << ") ";
        }
        cout << "(" << hull[hull.size() - 1].first << ", " << hull[hull.size() - 1].second << ")";

    }
};

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> points;
    for (int i = 0; i < n; i++) {
        int x;
        int y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    Solution solution;
    solution.solution(points);
    return 0;
}