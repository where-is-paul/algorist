#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long double ld;
typedef long long ll;

int main() {
	double n, x, avg, ans, ans1, ans2;
	vector<double> v;
	while (cin >> n) {
		if (n == 0) break;
		
		v.clear();
		avg = 0;
		ans1 = 0;
		ans2 = 0;
		
		for (int i = 0; i < n; i++) {
			cin >> x;
			v.push_back(x);
			avg += x;
		}
		avg /= n;
		
		sort(v.begin(), v.end());
		
		avg = int(100*avg+0.5);
		avg /= 100;
		for (int i = 0; i < n; i++) {
			if (v[i] < avg) {
				ans1 += avg - v[i];
			} else {
				ans2 -= avg - v[i];
			}
		}

		ans = min(ans1, ans2);
		ans = int(100*ans+0.5);
		ans /= 100;
		
		printf("$%.2f\n", ans);
		
	}
	
	return 0;
}