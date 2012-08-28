#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <list>

using namespace std;

typedef long double ld;
typedef long long ll;

const int size = 55;

typedef vector<vector<int> > graph;
graph g;

void insert(int x, int y) {
	g[x].push_back(y);
	g[y].push_back(x);
}

void reset() {
	g.clear();
	g.resize(size);
}

bool check_degree() {
	for (int i = 0; i < size; i++) {
		if (g[i].size() % 2) return false;
	}
	
	return true;
}

void solve(int u) {
	if (g[u].empty()) return;
	
	typeof(g[u].begin()) it;
	int i, v;
	while (!g[u].empty()) {
		it = g[u].end()-1;
		v = *it;
		g[u].erase(it);
		for (it = g[v].begin(); it != g[v].end(); it++) {
			if (*it == u) {
				g[v].erase(it);
				break;
			}
		}
		
		solve(v);
		cout << v << " " << u << endl;
	}
}

int main() {
	int x, y, n, cases;
	
	cin >> cases;
	for (int c = 0; c < cases; c++) {
		cin >> n;
		reset();
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			insert(x, y);
		}
		
		printf("Case #%i\n", c+1);
		if (!check_degree()) {
			cout << "some beads may be lost" << endl;
		} else {
			solve(y);
		}
		cout << endl;
		
		//find euler cycle
	}
	
	return 0;
}