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

typedef vector<vector<int> > graph;
vector<bool> colour, discovered;

void insert(graph& g, int x, int y) {
	g[x].push_back(y);
	g[y].push_back(x);
}

bool dfs(graph& g, int s) {
	int j;
	for (int i = 0; i < g[s].size(); i++) {
		j = g[s][i];
		if (!discovered[j]) {
			discovered[j] = true;
			colour[j] = !colour[s];
			dfs(g, j);
		} else {
			if (colour[j] == colour[s]) return false;
		}
	}
	
	return true;
}

template <class Container>
void reset(Container& c, int nodes) {
	c.clear();
	c.resize(nodes);
}

int main() {
	graph g;
	int nodes, edges, x, y;
	while (true) {
		cin >> nodes;
		if (nodes == 0) break;
		cin >> edges;

		reset(g, nodes);
		reset(colour, nodes);
		reset(discovered, nodes);
		
		while (edges --> 0) {
			cin >> x >> y;
			insert(g, x, y);
		}
		
		discovered[0] = true;
		colour[0] = true;
		if (dfs(g, 0)) cout << "BICOLORABLE." << endl;
		else cout << "NOT BICOLORABLE." << endl;
	}
	
	return 0;
}