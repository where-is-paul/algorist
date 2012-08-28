#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>

using namespace std;

typedef long double ld;
typedef long long ll;

int main() {
	vector<int> v;
	vector<int> diffs;
	int x;
	string line;
	bool ans;
	
	while (getline(cin, line)) {
		diffs.clear();
		v.clear();
		
		stringstream ss(line);
		ss >> x;
		while (ss >> x) v.push_back(x);

		for (int i = 0; i < v.size()-1; i++) {
			diffs.push_back(abs(v[i] - v[i+1]));
		}
		
		sort(diffs.begin(), diffs.end());
		
		ans = true;
		for (int i = 0; i < diffs.size(); i++) {
			if (diffs[i] != i+1) ans = false;
		}
		
		cout << (ans ? "Jolly" : "Not jolly" ) << endl;
	}
	
	return 0;
}