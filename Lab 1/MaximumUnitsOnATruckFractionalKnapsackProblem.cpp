#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(boxTypes.begin(), boxTypes.end(), [](vector<int>& left, vector<int>& right) {
            return left[1] > right[1];
        });

        int items = 0;

        for (auto& item: boxTypes) {
            int numberOfItems = item[0];
            int numberOfUnits = item[1];

            items += numberOfUnits * (truckSize - numberOfItems >= 0 ? numberOfItems : truckSize);
            truckSize -= numberOfItems;
            if (truckSize <= 0) return items;
        }

        return items;
    }
};

int main() {
    return 0;
}