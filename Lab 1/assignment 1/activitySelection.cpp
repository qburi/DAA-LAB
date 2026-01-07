#include <bits/stdc++.h>


using namespace std;

class Solution {
public:

    vector<pair<int, int>> getMaximumNonOverlappingIntervals(vector<pair<int, int>>& intervals) {
        if (intervals.empty())
            return {};

        // approach will be to sort them based on end times
        sort(intervals.begin(), intervals.end(), [&](pair<int, int>& left, pair<int, int>& right) {
           return left.second < right.second;
        });

        vector<pair<int, int>> ans;
        int prevEnd = intervals[0].second;
        ans.emplace_back(intervals[0].first, intervals[0].second);
        for (int i = 1; i < intervals.size(); i++) {
            auto [nextStart, nextEnd] = intervals[i];
            if (prevEnd > nextStart)
                continue;
            prevEnd = nextEnd;
            ans.emplace_back(nextStart, nextEnd);
        }

        return ans;

        // time complexity: O(nlogn)
        // space complexity: O(n) to store the ans array
    }
};

int main() {
    vector<pair<int, int>> intervals; // { {start, end}, {start, end} }
    int n;
    cout << "Enter the number of intervals: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int start;
        int end;
        cout << "Enter details of interval " << i + 1 << ": " << endl;
        cout << "Enter start time: ";
        cin >> start;
        cout << "Enter end time: ";
        cin >> end;
        intervals.emplace_back(start, end);
    }

    Solution* solution = new Solution();
    vector<pair<int, int>> ans = solution->getMaximumNonOverlappingIntervals(intervals);
    cout << "Non-overlapping intervals" << endl;
    for (auto& [start, end]: ans) {
        cout << start << ", " << end << endl;
    }
    delete solution;
    return 0;
}