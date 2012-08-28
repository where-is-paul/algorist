#include <cstdio>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>

using namespace std;

typedef long double ld;
typedef long long ll;

typedef struct edge {
	edge(int v, int w) : v(v), w(w) {
	};
	int v;
	int w;
} edge;

typedef vector<vector<edge> > graph;
graph g;
vector<int> dist;
vector<bool> discovered;

void insert(int x, int y, int w) {
	g[x].push_back(edge(y, w));
	g[y].push_back(edge(x, w));
}

int bfs(int s, int e) {
	discovered[s] = true;
	dist[s] = 10000;
	
	queue<int> q;
	q.push(s);
	
	edge E(0,0);
	while (!q.empty()) {
		s = q.front(); q.pop();
		for (int i = 0; i < g[s].size(); i++) {
			E = g[s][i];
			if (!discovered[E.v] || min(dist[s], E.w) > dist[E.v]) {
				discovered[E.v] = true;
				dist[E.v] = min(dist[s], E.w);
				q.push(E.v);
			}
		}
	}
	
	return dist[e];
}

void reset(int nodes) {
	g.clear();
	dist.clear();
	discovered.clear();
	
	g.resize(nodes);
	dist.resize(nodes, 0);
	discovered.resize(nodes, false);
}

//distance is maximizing the minimum edge weight path now.
//so distance is min(w1, w2, ... wi) instead of sum wi.
int main() {
	int nodes, edges, x, y, w, counter = 0;
	int s, e, path_cap, ans;
	double cap;
	while (cin >> nodes >> edges) {
		counter++;
		if (nodes == 0 && edges == 0) break;
		
		reset(nodes);
		while (edges --> 0) {
			cin >> x >> y >> w;
			x--; y--;
			insert(x, y, w);
		}
		cin >> s >> e >> cap;
		s--; e--;
		
		path_cap = bfs(s, e);
		path_cap--;
		ans = ceil(cap/path_cap);
		printf("Scenario #%i\n", counter);
		printf("Minimum Number of Trips = %i\n", ans); 
		cout << endl;
	}
	
	return 0;
}