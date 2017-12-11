#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
void sortIndexes(const std::vector<T> &v, std::vector<int> &idxs) {

	// initialize original index locations
	idxs.resize(v.size());
	std::iota(idxs.begin(), idxs.end(), 0);

	// sort indexes based on comparing values in v
	std::sort(idxs.begin(), idxs.end(), [&v](int i1, int i2) { return v[i1] < v[i2]; } );
}

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		std::vector<int> idxs(nums.size()); // store sorted indices
		sortIndexes(nums, idxs);

		std::vector<int> result;

		// locate indices for sum
		int i = 0, j = nums.size() - 1;
		while (i < j) {
			int s = nums[idxs[i]] + nums[idxs[j]];
			if (s < target) {
				++i;
			} else if (s > target) {
				--j;
			} else {
				result.push_back(idxs[i]);
				result.push_back(idxs[j]);
				break;
			}
		}

		return result;
	}
};

int main(int argc, char** argv)
{
	auto sol = Solution();
	std::vector<int> nums;
	nums.push_back(1);
	nums.push_back(3);
	nums.push_back(5);
	nums.push_back(7);
	nums.push_back(9);
	auto res = sol.twoSum(nums, 14);
	std::cout << res[0] << ", " << res[1] << std::endl;

	return 0;
}