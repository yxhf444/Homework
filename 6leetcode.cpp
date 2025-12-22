#include <vector>
#include <iostream>

using namespace std;

vector<int> smartUmn(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);

    int left_product = 1;
    for (int i = 0; i < n; i++) {
        res[i] = left_product;
        left_product *= nums[i];
    }

    int right_product = 1;
    for (int i = n - 1; i >= 0; i--) {
        res[i] *= right_product;
        right_product *= nums[i];
    }
    
    return res;
}

int main() {
    vector<int> nums = {1, 2, 3, 4};
    vector<int> res = smartUmn(nums);

    for (int num : res) {
        cout << num << " ";
    }

    return 0;
}