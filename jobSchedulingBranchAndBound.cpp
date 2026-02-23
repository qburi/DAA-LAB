#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void jobScheduling(vector<vector<int>>& jobs) {
        // { Profit, Deadline, Execution TIme }
        int n = jobs.size();
        sort(jobs.begin(), jobs.end(), [&](const vector<int>& a, const vector<int>& b) 
        {
            return a[1] < b[1];
        });

        vector<int> suffix(n, 0);
        suffix[n - 1] = jobs[n - 1][0];
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = jobs[i][0] + suffix[i + 1];
        }
        int upperBoundPenalty = 0;
        // miss all the jobs
        for (int i = 0; i < jobs.size(); i++) 
            upperBoundPenalty += jobs[i][0];
        
        
        // FIFO
        queue<vector<int>> q; // { prevIndex, execution time, incurred penalty, upper bound }
        q.push(vector<int>{-1, 0, 0, upperBoundPenalty});
        int minPenalty = upperBoundPenalty;
        
        while (! q.empty()) {
            int qSize = q.size();
            
            for (int ind = 0; ind < qSize; ind++) {
                vector<int> node = q.front(); q.pop();
                int prevIndex = node[0];
                int executionTime = node[1];
                int incurredPenalty = node[2];
                int currentUpperBound = node[3];
                
                for (int j = prevIndex + 1; j < n; j++) {
                    int newUpperBound = j == (n - 1) ? 
                    incurredPenalty : incurredPenalty + suffix[j + 1];

                    
                    if (executionTime > jobs[j][1] 
                    || incurredPenalty > upperBoundPenalty
                    || executionTime + jobs[j][2] > jobs[j][1]
                    ) {
                        incurredPenalty += jobs[j][0]; // for next node
                        continue;
                    }
                    
                    
                    if (newUpperBound < upperBoundPenalty) {
                        // update
                        upperBoundPenalty = newUpperBound;
                        minPenalty = newUpperBound;
                    }
                    int newExecutionTime = executionTime + jobs[j][2];
                    q.push(vector<int>{j, newExecutionTime, incurredPenalty, newUpperBound});
                    incurredPenalty += jobs[j][0]; // for next node
                    
                    
                }
            }
        }
        
        cout << "Minimum Penalty: " << minPenalty << endl;
        cout << "Maximum Profit: " << suffix[0] - minPenalty;
    }
    
    void printJobs(vector<vector<int>>& jobs) {
        int n = jobs.size();
        for (int i = 0; i < n; i++) {
            cout << "Job: " << i << ", Profit: " << jobs[i][0]
            << ", Deadline: " << jobs[i][1] << ", Execution Time: " << jobs[i][2] << endl;
        }
    }
    
    void printSuffix(vector<int>& suffix) {
        for (int i = 0; i < suffix.size(); i++)
            cout << suffix[i] << " ";
        cout << endl;
    }
    
    void printQueueElement(vector<int>& element) {
        // { node index, execution time, incurred penalty, current upper bound }
        cout << "Node Index: " << element[0] << endl;
        cout << "Current Execution time: " << element[1] << endl;
        cout << "current Incurred penalty: " << element[2] << endl;
        cout << "current upper bound: " << element[3] << endl;
        cout << endl;
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> jobs(n, vector<int>(3, 0));
    for (int i = 0; i < n; i++) {
        cin >> jobs[i][0];
        cin >> jobs[i][1];
        cin >> jobs[i][2];
    }
    
    Solution solution;
    solution.jobScheduling(jobs);
    
    return 0;
}