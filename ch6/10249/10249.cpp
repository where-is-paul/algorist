#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <complex>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;

bool comp(const pii& l, const pii& r) {
	if (l.first == r.first) return l.second < r.second;
	return l > r;
}

int main() {
	int m, n, i;
	bool valid;
	vector<vector<int> > ans;
	vector<pii> table;
	vector<pii> team;
	
	while (cin >> m >> n) {
		if (m == 0 && n == 0) break;
		
		ans.clear();
		table.clear();
		team.clear();
		
		ans.resize(m);
		valid = true;
		
		for (int j = 0; j < m; j++) {
			cin >> i;
			team.push_back(make_pair(i, j));
		}
		
		for (int j = 0; j < n; j++) {
			cin >> i;
			table.push_back(make_pair(i, j));
		}
		
		i = 0;
		sort(team.begin(), team.end(), comp);
		while (i < m) {
			sort(table.begin(), table.end(), comp);
			for (int j = 0; j < team[i].first; j++) {
				table[j].first--;
				if (table[j].first < 0) {
					valid = false;
					goto end;
				}
				ans[team[i].second].push_back(table[j].second);
			}
			i++;
		}
			
end:
		if (valid) {
			cout << 1 << endl;
			for (int i = 0; i < m; i++) {
				sort(ans[i].begin(), ans[i].end());
				for (int j = 0; j < int(ans[i].size())-1; j++) {
					cout << ans[i][j]+1 << " ";
				}
				cout << ans[i][ans[i].size()-1]+1 << endl;
			}
		} else {
			cout << 0 << endl;
		}
	}
	return 0;
}