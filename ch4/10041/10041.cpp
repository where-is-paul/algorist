#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;
typedef long long ll;

int main() {
	int cases, n, num, med, ans;
	vector<int> nums;
	cin >> cases;
	while (cases --> 0) {
		nums.clear();
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> num;
			nums.push_back(num);
		}
		
		sort(nums.begin(), nums.end());
		med = nums[nums.size()/2];
		
		ans = 0;
		for (int i = 0; i < n; i++) {
			ans += abs(nums[i] - med);
		}
		
		cout << ans << endl;
	}
	
	return 0;
}