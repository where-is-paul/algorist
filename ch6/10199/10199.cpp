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

map<string, int> m;
map<int, string> m_inv;
set<int> ans;

typedef vector<vector<int> > graph;
graph g;

vector<int> dfsnum;
vector<int> low;
vector<int> parent;
vector<int> nchild;
int num = 0;

void reset(int n) {
	ans.clear();
	
	g.clear();
	g.resize(n);
}

void reset_dfs(int n) {
	dfsnum.clear();
	dfsnum.resize(n, -1);
	
	parent.clear();
	parent.resize(n, -1);
	
	nchild.clear();
	nchild.resize(n);
	
	low.clear();
	low.resize(n);
	
	num = 0;
}

void insert(int x, int y) {
	g[x].push_back(y);
	g[y].push_back(x);
}

void dfs(int u) {
	low[u] = dfsnum[u] = num++;
	
	//cout << "on street " << m_inv[u] << endl;
	int v;
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i];
		if (dfsnum[v] == -1) {
			//(u, v) is a tree edge
			parent[v] = u;
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else {
			//(u, v) is a back edge
			low[u] = min(low[u], dfsnum[v]);
		}
	}
}

void solve(int root) {
	for (int i = 0; i < g.size(); i++) {
		if (parent[i] < 0) continue;
		
		nchild[parent[i]]++;
	}
	
	for (int v = 0; v < g.size(); v++) {
		if (parent[v] < 0) continue;
		if (parent[v] == root) continue;
		
		if (low[v] >= dfsnum[parent[v]]) {
			// cout << "inserting.. " << m_inv[parent[v]] << endl;
			ans.insert(parent[v]);
		}
	}
	
	if (nchild[root] >= 2) ans.insert(root);
	else ans.erase(root);
	
	// cout << "the root is " << m_inv[root];
	// cout << " and it has " << nchild[root] << " children." << endl;
}



int main() {
	typeof(ans.begin()) it;
	int nodes, edges, count = 0;
	string name1, name2;
	vector<string> names;
	
	cin >> nodes;
	while (true) {
		if (nodes == 0) break;
		
		count++;
		reset(nodes);
		names.clear();
		for (int i = 0; i < nodes; i++) {
			cin >> name1;
			names.push_back(name1);
		}
		sort(names.begin(), names.end());
		
		for (int i = 0; i < nodes; i++) {
			m[names[i]] = i;
			m_inv[i] = names[i];
		}
		
		cin >> edges;
		for (int i = 0; i < edges; i++) {
			cin >> name1 >> name2;
			insert(m[name1], m[name2]);
		}
		
		reset_dfs(nodes);
		for (int i = 0; i < nodes; i++) {
			if (dfsnum[i] >= 0) continue;
			reset_dfs(nodes);
			dfs(i);
			solve(i);
		}
		printf("City map #%i: %i camera(s) found\n", count, ans.size());
		for (it = ans.begin(); it != ans.end(); it++) {
			cout << m_inv[*it] << endl;
		}
		
		cin >> nodes;
		if (nodes != 0)
		cout << endl;
	}
	
	return 0;
}