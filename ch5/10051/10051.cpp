#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef long double ld;
typedef long long ll;

string to_side(int i) {
	switch (i) {
	case 0:
		return "front";
	case 1:
		return "back";
	case 2:
		return "left";
	case 3:
		return "right";
	case 4:
		return "top";
	case 5:
		return "bottom";
	}
}

typedef struct node {
	int val;
	int side;
	int prev_c;
	int prev_i;
	node() : val(1), side(-1), prev_c(-1), prev_i(-1) {};
	node(int v, int s, int p_c, int p_i) {
		val = v;
		side = s;
		prev_c = p_c;
		prev_i = p_i;
	};
	
	void update(int v, int s, int p_c, int p_i) {
		val = v;
		side = s;
		prev_c = p_c;
		prev_i = p_i;
	};
} node;

map<pair<int, int>, node> dp[500];
bool colours[100];

void reset(int n) {
	for (int i = 0; i < n; i++) {
		dp[i].clear();
	}
	for (int i = 0; i < 100; i++)
	colours[i] = false;
}

void print_res_recurse(int i, pair<int, int> c) {
	node curr = dp[i][c];
	if (curr.prev_i < 0) {
		cout << i+1 << " " << to_side(curr.side) << endl;
		return;
	}
	print_res_recurse(curr.prev_i, make_pair(curr.prev_c, c.first));
	cout << i+1 << " " << to_side(curr.side) << endl;
}

void print_res(int i) {
	int res = 0, best_i = 0;
	pair<int, int> best_c;
	for (typeof(dp[i].begin()) it = dp[i].begin(); it != dp[i].end(); it++) {
		if (res < (it->second).val) {
			res = (it->second).val;
			best_i = i;
			best_c = (it->first);
		}
	}
	
	cout << res << endl;
	print_res_recurse(best_i, best_c);
}

int main() {
	int n, c, c1, c2, max_val = 0, max_i = 0;
	int counter = 0;
	pair<int, int> c_for, c_rev, t;
	while (cin >> n) {
		if (n == 0) break;
		reset(n);
		max_val = max_i = 0;
		
		for (int i = 0; i < n; i++)
		for (int side = 0; side < 6; side+=2) {
			cin >> c1 >> c2;
			c_for = make_pair(c1, c2);
			c_rev = make_pair(c2, c1);
			
			dp[i][c_for] = node(1, side, -1, -1);
			dp[i][c_rev] = node(1, side+1, -1, -1);
			
			for (int j = 0; j < i; j++) {
			for (int c = 0; c < 100; c++) {
				if (!colours[c]) continue;
				t = make_pair(c, c1);
				if (dp[j].count(t))
				if (1+dp[j][t].val > dp[i][c_for].val) {
					dp[i][c_for].update(1+dp[j][t].val, side, c, j);
				}
				
				t = make_pair(c, c2);
				if (dp[j].count(t))
				if (1+dp[j][t].val > dp[i][c_rev].val) {		
					dp[i][c_rev].update(1+dp[j][t].val, side+1, c, j);
				}
			}
			}
			
			if (dp[i][c_for].val > max_val) {
				max_val = dp[i][c_for].val;
				max_i = i;
			}
			
			if (dp[i][c_rev].val > max_val) {
				max_val = dp[i][c_rev].val;
				max_i = i;
			}
			
			colours[c1] = true;
			colours[c2] = true;
		}
		
		counter++;
		cout << "Case #" << counter << endl;
		print_res(max_i);
		cout << endl;
	}
	return 0;
}