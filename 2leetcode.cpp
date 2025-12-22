#include <vector>
#include <iostream>

using namespace std;

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int unique_index = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[i - 1]) {
            nums[unique_index] = nums[i];
            unique_index++;
        }
    }
    return unique_index;
}

int main() {
    vector<int> nums = {1, 1, 2, 3,3,3,3,3,3,3,5};
    int k = removeDuplicates(nums);
    cout << k << endl;
    for (int i = 0; i < k; i++) {
        cout << nums[i] << " ";
    }

    return 0;
}