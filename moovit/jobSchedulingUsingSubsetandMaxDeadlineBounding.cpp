#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void solution(vector<vector<int>>& jobs) {
        // { profit, deadline, execution time}
        
        int n = jobs.size();
        
        vector<int> suffix(n, 0);
        suffix[n - 1] = jobs[n - 1][0];
        for (int i = n - 2; i >= 0; i--) 
            suffix[i] = suffix[i + 1] + jobs[i][0];
        
        int ug = suffix[0];
        
        queue<vector<int>> q; // { prevIndex, execution time, incurred penalty, upper bound penalty, max deadline } 
        q.push({-1, 0, 0, ug, -1});         
        while (! q.empty()) {
            int qSize = q.size();
            
            for (int i = 0; i < qSize; i++) {
                vector<int> node = q.front(); q.pop();
                int prevIndex = node[0];
                int et = node[1];
                int im = node[2];
                int ub = node[3];
                int maxDeadline = node[4];
                
                for (int j = prevIndex + 1; j < n; j++) {
                    // we will include this index
                    int newUb = (j == n - 1) ? im : im + suffix[j + 1];
                    int deadline = maxDeadline == -1 ? jobs[j][1] : max(maxDeadline, jobs[j][1]);
                    
                    if (et + jobs[j][2] > deadline || im > ug) {
                        im += jobs[j][0];
                        continue;
                    }
                    
                    if (newUb < ug) {
                        ug = newUb;
                    }
                    q.push({j, et + jobs[j][2], im, newUb, deadline});
                    
                    // we skip this index
                    im += jobs[j][0];
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
        int executionTime;
        cin >> profit >> deadline >> executionTime;
        jobs.push_back({profit, deadline, executionTime});
    }
    Solution solution;
    solution.solution(jobs);
    return 0;
}