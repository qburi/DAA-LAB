#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    void backtrack(vector<vector<int>>& result, vector<int>& candidates, vector<int>& plausibleCandidate,
             int target, int start) {
        if (target == 0) {
            result.push_back(plausibleCandidate);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            if (candidates[i] > target) break;

            plausibleCandidate.push_back(candidates[i]);
            backtrack(result, candidates, plausibleCandidate, target - candidates[i], i + 1);

            plausibleCandidate.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> result;
        vector<int> plausibleCandidate;
        backtrack(result, candidates, plausibleCandidate, target, 0);
        return result;
    }
};