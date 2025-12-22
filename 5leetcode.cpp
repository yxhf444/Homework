#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

vector<int> findMissed(vector<int>& nums) {
    int i = 0;
    while (i < nums.size()) {
        int index = nums[i] - 1;
        if (nums[i] != nums[index]) {
            int temp = nums[i];
            nums[i] = nums[index];
            nums[index] = temp;
        } else {
            i++;
        }
    }

    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != i + 1) {
            res.push_back(i + 1);
        }
    }

    return res;
}

int main() {
    vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> res = findMissed(nums);

    for (int num : res) {
        cout << num << " ";
    }

    return 0;
}