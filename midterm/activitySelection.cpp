#include <bits/stdc++.h>


using namespace std;

class Solution {
public:
    void mergeSort(vector<pair<int, int>>& intervals) {
        if (intervals.size() <= 1)
            return;

        int mid = intervals.size() / 2;
        vector<pair<int, int>> leftArray(intervals.begin(), intervals.begin() + mid);
        vector<pair<int, int>> rightArray(intervals.begin() + mid, intervals.end());
        mergeSort(leftArray);
        mergeSort(rightArray);
        merge(leftArray, rightArray, intervals);
    }

    void merge(vector<pair<int, int>>& leftArray, vector<pair<int, int>>& rightArray, vector<pair<int, int>>& arr) {
        int r = 0;
        int l = 0;
        int i = 0;

        while (l < leftArray.size() && r < rightArray.size()) {
            arr[i++] = leftArray[l].second <= rightArray[r].second ? leftArray[l++] : rightArray[r++];
        }

        while (l < leftArray.size()) {
            arr[i++] = leftArray[l++];
        }

        while (r < rightArray.size()) {
            arr[i++] = rightArray[r++];
        }

    }

    vector<pair<int, int>> getMaximumNonOverlappingIntervals(vector<pair<int, int>>& intervals) {
        if (intervals.empty())
            return {};

        // approach will be to sort them based on end times
        mergeSort(intervals);

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

// int main() {
//     vector<pair<int, int>> intervals; // { {start, end}, {start, end} }
//     int n;
//     cout << "Enter the number of intervals: ";
//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         int start;
//         int end;
//         cout << "Enter details of interval " << i + 1 << ": " << endl;
//         cout << "Enter start time: ";
//         cin >> start;
//         cout << "Enter end time: ";
//         cin >> end;
//         intervals.emplace_back(start, end);
//     }
//
//     Solution* solution = new Solution();
//     vector<pair<int, int>> ans = solution->getMaximumNonOverlappingIntervals(intervals);
//     cout << "Non-overlapping intervals" << endl;
//     for (auto& [start, end]: ans) {
//         cout << start << ", " << end << endl;
//     }
//     delete solution;
//     return 0;
// }


// some test cases
// Helper function to run and format test cases cleanly
void runTestCase(int testNum, const string &description, vector<pair<int, int> > intervals, Solution &sol) {
    cout << "Test Case " << testNum << ": " << description << "\n";
    cout << "Input:    ";
    for (const auto &p: intervals) {
        cout << "{" << p.first << ", " << p.second << "} ";
    }
    cout << "\n";

    vector<pair<int, int> > result = sol.getMaximumNonOverlappingIntervals(intervals);

    cout << "Selected: ";
    for (const auto &p: result) {
        cout << "{" << p.first << ", " << p.second << "} ";
    }
    cout << "\n-------------------------------------------------\n";
}

int main() {
    Solution sol;

    // Test Case 1: Classic mix of overlapping and non-overlapping activities
    runTestCase(1, "Standard Mix",
                {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}}, sol);

    // Test Case 2: Sorted by start time, but end times are nested
    // (A naive sort-by-start-time would fail here by picking {1, 10})
    runTestCase(2, "Nested Intervals",
                {{1, 10}, {2, 9}, {3, 8}, {4, 7}, {5, 6}}, sol);

    // Test Case 3: All activities are mutually disjoint
    runTestCase(3, "Completely Disjoint",
                {{1, 2}, {3, 4}, {5, 6}, {7, 8}}, sol);

    // Test Case 4: All activities overlap, sharing the same start time
    runTestCase(4, "Completely Overlapping",
                {{1, 5}, {1, 2}, {1, 3}, {1, 4}}, sol);

    return 0;
}

