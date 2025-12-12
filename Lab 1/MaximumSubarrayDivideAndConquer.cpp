#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return maxSubArraySum(nums, 0, nums.size() - 1);
    }

    int maxSubArraySum(vector<int>& arr, int low, int high) {
        if (low == high) return arr[low];

        int middle = low + (high - low) / 2;

        int leftMax = maxSubArraySum(arr, low, middle);
        int rightMax = maxSubArraySum(arr, middle + 1, high);
        int crossMax = maxCrossingSum(arr, low, middle, high);

        return max({leftMax, rightMax, crossMax});
    }

    int maxCrossingSum(vector<int>& arr, int low, int middle, int high) {
        int sum = 0;
        int leftSum = INT_MIN;
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
    return 0;
}