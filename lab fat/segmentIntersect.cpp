#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool solution(vector<pair<int, int>>& p1, vector<pair<int, int>>& p2) {
        int d1 = direction(p2[0], p2[1], p1[0]);
        int d2 = direction(p2[0], p2[1], p1[1]);
        int d3 = direction(p1[0], p1[1], p2[0]);
        int d4 = direction(p1[0], p1[1], p2[1]);
        if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && 
        (d3 < 0 && d4 > 0 || d3 > 0 && d4 < 0)) {
            return true;
        }
        if (d1 == 0 && onSegment(p2[0], p2[1], p1[0])) 
            return true;
        if (d2 == 0 && onSegment(p2[0], p2[1], p1[1])) 
            return true;
        if (d3 == 0 && onSegment(p1[0], p1[1], p2[0]))
            return true;
        if (d4 == 0 && onSegment(p1[0], p1[1], p2[1])) 
            return true;
        return false;
            
    }
    
    int direction(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
        int x1 = p1.first;
        int x2 = p2.first;
        int x3 = p3.first;
        int y1 = p1.second;
        int y2 = p2.second;
        int y3 = p3.second;
        return (x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1);
    }
    
    bool onSegment(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
        int x1 = p1.first;
        int x2 = p2.first;
        int x3 = p3.first;
        int y1 = p1.second;
        int y2 = p2.second;
        int y3 = p3.second;
        
        return x3 <= max(x1, x2) && x3 >= min(x1, x2) && 
        y3 <= max(y1, y2) && y3 >= min(y1, y2);
    }
};


int main() {
    vector<pair<int, int>> points;
    for (int i = 0; i < 4; i++) {
        int x;
        int y;
        cin >> x >> y;
        points.push_back({x, y});
    }
    vector<pair<int, int>> s1;
    vector<pair<int, int>> s2;
    s1.push_back(points[0]);
    s1.push_back(points[1]);
    s2.push_back(points[2]);
    s2.push_back(points[3]);
    Solution solution;
    bool ans = solution.solution(s1, s2);
    if (ans)
        cout << "true";
    else
        cout << "false";
    return 0;
}