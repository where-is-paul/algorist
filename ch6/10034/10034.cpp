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
typedef complex<double> pt;

typedef struct node {
	int v;
	double w;
} node;

typedef vector<vector<node> > graph;
vector<pt> g;
bool discovered[100];

void reset(int n) {
	g.clear();
	
	for (int i = 0; i < n; i++) 
	discovered[i] = false;
}

typedef pair<double, int> edge;

struct edge_comp {
	bool operator()(const edge& l, const edge& r) const {
		return l > r;
	}
};

double prims(int s, int n) {
	priority_queue<edge, vector<edge>, edge_comp> q;
	edge elem;
	double res = 0;
	
	q.push(make_pair(0,s));
	while (!q.empty()) {
		elem = q.top();
		q.pop();

		if (discovered[elem.second]) continue;

		res += elem.first;
		s = elem.second;
		discovered[s] = true;
		for (int i = 0; i < n; i++) {
			if (!discovered[i]) {
				q.push(make_pair(abs(g[s]-g[i]), i));
			}
		}
	}
	
	return res;
}

int main() {
	int cases, n;
	double x, y;
	cin >> cases;
	while (cases --> 0) {
		cin >> n;
		reset(n);
		
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			g.push_back(pt(x, y));
		}
		
		printf("%.2f\n", prims(0, n));
		
		if (cases != 0)
		cout << endl;
	}
	
	return 0;
}