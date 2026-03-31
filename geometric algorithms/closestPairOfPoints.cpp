#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <cfloat>

using namespace std;

struct Point {
    double x, y;
};

// Helper function to calculate Euclidean distance
double getDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force for small base cases (3 or fewer points)
double bruteForce(const vector<Point>& points, int left, int right) {
    double min_dist = DBL_MAX;
    for (int i = left; i <= right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            double dist = getDistance(points[i], points[j]);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
    }
    return min_dist;
}

// Core Divide and Conquer recursive function
double closestUtil(const vector<Point>& pointsByX, const vector<Point>& pointsByY, int left, int right) {
    // Base case: 3 or fewer points
    if (right - left <= 2) {
        return bruteForce(pointsByX, left, right);
    }

    int mid = left + (right - left) / 2;
    Point midPoint = pointsByX[mid];

    // Divide points in Y-sorted array into left and right halves
    vector<Point> pyLeft;
    vector<Point> pyRight;
    
    // Reserve memory to avoid reallocations
    pyLeft.reserve(mid - left + 1);
    pyRight.reserve(right - mid);

    for (const auto& p : pointsByY) {
        // Keep points on the left of midPoint in pyLeft, others in pyRight
        // The size check ensures we handle duplicate x-coordinates properly
        if (p.x < midPoint.x || (p.x == midPoint.x && pyLeft.size() < (size_t)(mid - left + 1))) {
            pyLeft.push_back(p);
        } else {
            pyRight.push_back(p);
        }
    }

    // Conquer
    double dl = closestUtil(pointsByX, pyLeft, left, mid);
    double dr = closestUtil(pointsByX, pyRight, mid + 1, right);
    double d = min(dl, dr);

    // Combine: Build the strip array
    vector<Point> strip;
    for (const auto& p : pointsByY) {
        if (abs(p.x - midPoint.x) < d) {
            strip.push_back(p);
        }
    }

    // Find the closest points in the strip
    size_t stripSize = strip.size();
    for (size_t i = 0; i < stripSize; ++i) {
        // Geometrically, the inner loop runs at most 7 times
        for (size_t k = i + 1; k < stripSize && (strip[k].y - strip[i].y) < d; ++k) {
            double dist = getDistance(strip[i], strip[k]);
            if (dist < d) {
                d = dist;
            }
        }
    }

    return d;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // Check if input is empty
    if (!(cin >> n)) return 0;

    vector<Point> pointsByX(n);
    vector<Point> pointsByY(n);

    for (int i = 0; i < n; i++) {
        cin >> pointsByX[i].x >> pointsByX[i].y;
        pointsByY[i] = pointsByX[i];
    }

    // Pre-sort points by X and Y coordinates
    sort(pointsByX.begin(), pointsByX.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    
    sort(pointsByY.begin(), pointsByY.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    double minDistance = closestUtil(pointsByX, pointsByY, 0, n - 1);

    // Required VPL output format
    cout << fixed << setprecision(6) << minDistance << "\n";

    return 0;
}