#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef long double ld;
typedef long long ll;

//idea:
//look at increasing subsequences starting with 1
int get_starting_point(vector<int>& inp) {
	int res = 0;
	for (int i = 0; i < inp.size(); i++) {
		if (inp[i] == res) res++;
	}
	
	return res;
}

int main() {
	map<string, int> trans;
	map<int, string> inv_trans;
	string line;
	vector<string> input;
	vector<int> inp;
	int cases, n, i;
	
	cin >> cases;
	while (cases --> 0) {
		cin >> n;
		getline(cin, line);
		
		inp.clear();
		input.clear();
		trans.clear();
		inv_trans.clear();
		
		for (i = 0; i < n; i++) {
			getline(cin, line);
			input.push_back(line);
		}
		reverse(input.begin(), input.end());
		
		for (i = 0; i < n; i++) {
			getline(cin, line);
			trans[line] = n-i-1;
			inv_trans[n-i-1] = line;
		}
		
		for (i = 0; i < n; i++) {
			inp.push_back(trans[input[i]]);
		}
		
		for (i = get_starting_point(inp); i < n; i++) {
			cout << inv_trans[i] << endl;
		}
		
		cout << endl;
	}
	return 0;
}