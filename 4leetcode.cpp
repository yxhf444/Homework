#include <vector>
#include <iostream>

using namespace std;

void moveZeroes(vector<int>& nums) {
    int last_non_zero = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            int temp = nums[last_non_zero];
            nums[last_non_zero] = nums[i];
            nums[i] = temp;

            last_non_zero++;
        }
    }
}

int main() {
    vector<int> nums = {0, 1, 0, 3, 12};
    moveZeroes(nums);

    for (int num : nums) {
        cout << num << " ";
    }

    return 0;
}