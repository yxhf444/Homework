#include <vector>
#include <iostream>

using namespace std;

vector<int> sortedSquares(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    int left = 0, right = n - 1;
    int pos = n - 1;

    while (left <= right) {
        int left_square = nums[left] * nums[left];
        int right_square = nums[right] * nums[right];

        if (left_square > right_square) {
            result[pos] = left_square;
            left++;
        } else {
            result[pos] = right_square;
            right--;
        }
        pos--;
    }

    return result;
}

int main() {
    vector<int> nums = {-4, -1, 0, 3, 10};
    vector<int> result = sortedSquares(nums);
    for (int num : result) {
        cout << num << " ";
    }

    return 0;
}