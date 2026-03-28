#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSubarraySum(vector<int>& arr, int low, int high) {
        if (low == high)
            return arr[low];

        int middle = (low + high) / 2;
        int leftSum = maxSubarraySum(arr, low, middle);
        int rightSum = maxSubarraySum(arr, middle + 1, high);
        int crossSum = maxCrossSum(arr, low, high, middle);

        if (low == 0 && high == arr.size() - 1) {
            cout << max({leftSum, rightSum, crossSum}) << endl;
            cout << crossSum;
        }

        return max({leftSum, rightSum, crossSum});
    }

    int maxCrossSum(vector<int>& arr, int low, int high, int middle) {
        int leftSum = INT_MIN;
        int sum = 0;

        for (int i = middle; i >= low; i--) {
            sum += arr[i];
            if (sum > leftSum)
                leftSum = sum;
        }

        sum = 0;
        int rightSum = INT_MIN;
        for (int i = middle + 1; i <= high; i++) {
            sum += arr[i];
            if (sum > rightSum)
                rightSum = sum;

        }

        return leftSum + rightSum;
    }

};


int main() {
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Solution solution;
    solution.maxSubarraySum(arr, 0, arr.size() - 1);
    return 0;
}