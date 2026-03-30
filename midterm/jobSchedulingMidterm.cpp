#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void solution(vector<vector<int>>& jobs) {
        int n = jobs.size();
        sort(jobs.begin(), jobs.end(), [&](vector<int>& left, vector<int>& right) {
            return left[1] < right[1];
        });
        
        
        vector<int> suffix(n, 0);
        suffix[n - 1] = jobs[n - 1][0];
        int ug = jobs[n - 1][0];
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + jobs[i][0];
            ug += jobs[i][0];
        }
        
        queue<vector<int>> q;
        q.push({-1, 0, 0}); // prevIndex, incurredPenalty, executionTime
        
        while (! q.empty()) {
            int qSize = q.size();
            for (int ind = 0; ind < qSize; ind++) {
                vector<int> p = q.front(); q.pop();
                int prevIndex = p[0];
                int incurredPenalty = p[1];
                int et = p[2];
                
                
                for (int i = prevIndex + 1; i < n; i++) {
                    int newEt = et + jobs[i][2];
                    int newUpperBound = (i == n - 1) ? incurredPenalty : suffix[i + 1] + incurredPenalty;
                    
                    
                    if (newEt > jobs[i][1] || incurredPenalty > ug) {
                        incurredPenalty += jobs[i][0];
                        continue;
                    }            
                    
                    if (newUpperBound < ug) {
                        ug = newUpperBound;
                    }
                    q.push({i, incurredPenalty, newEt});
                    incurredPenalty += jobs[i][0];
                }
            }
        }
        
        cout << "Minimum Penalty: " << ug << endl;
        cout << "Maximum Profit: " << suffix[0] - ug << endl;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> jobs;
    for (int i = 0; i < n; i++) {
        int profit;
        int deadline;
        int et;
        cin >> profit >> deadline >> et;
        jobs.push_back({profit, deadline, et});
    }
    
    Solution solution;
    solution.solution(jobs);
    return 0;
}