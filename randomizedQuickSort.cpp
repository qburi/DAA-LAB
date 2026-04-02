#include <bits/stdc++.h>

using namespace std;

// Standard partition logic
int partition(vector<int>& arr, int start, int end) {
    int i = start - 1;
    int pivot = arr[end];

    for (int j = start; j <= end - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    i++;
    swap(arr[i], arr[end]);
    return i;
}

int randomizedPartition(vector<int>& arr, int start, int end) {
    // Generate a random index between start and end inclusive
    int randomIndex = start + rand() % (end - start + 1);

    // Swap the randomly chosen element with the last element
    swap(arr[randomIndex], arr[end]);

    // Proceed with the standard partition
    return partition(arr, start, end);
}

void quickSort(vector<int>& arr, int start, int end) {
    if (start >= end) return;

    // Call the randomized partition instead of the standard one
    int pivot = randomizedPartition(arr, start, end);

    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    vector<int> arr{1, 2, 5, 10, 2, 3, 8, -1, -4};
    quickSort(arr, 0, arr.size() - 1);

    for (int num: arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}