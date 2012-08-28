#include <iostream>
#include <iomanip>
#include <exception>
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

typedef struct edge {
	int v;
	int t1;
	int t2;
	edge (int v, int t1, int t2) : v(v), t1(t1), t2(t2) {};
	edge () : v(-1), t1(0), t2(0) {};
	
	bool operator<(const edge &e) const {  
        if (t1 == e.t1) return t2 < e.t2;
		return t1 < e.t1;  
    }
} edge;

typedef vector<vector<edge> > graph;
graph g;

typedef pair<int, int> pii;

vector<int> prev;
vector<int> dist;
map<string, int> m;
map<int, string> m_inv;

bool operator<(const pii& l, const pii& r) {
	return l > r;
}

int time(int i) {
	return (i%100) + 60*(i/100);
}

int inv_time(int t) {
	return 100*(t/60) + (t%60);
}

void djikstra(int s, int t) {
	edge e;
	pii key = make_pair(t, s);
	priority_queue<pii> q;
	
	q.push(key);
	prev[s] = -1;
	dist[s] = -1;
	
	while (!q.empty()) {
		key = q.top();
		q.pop();
		
		t = key.first;
		s = key.second;
		
		//if (s == end) cout << inv_time(dist[key]) << endl;
		
		for (int i = 0; i < g[s].size(); i++) {
			e = g[s][i];
			// cout << inv_time(t) << " at station " << m_inv[e.v] << " at time " << inv_time(e.t2);
			// cout << " from station " << m_inv[s] << endl;
			if (t > e.t1) continue;
			
			key = make_pair(e.t2, e.v);
			if (dist[e.v] >= e.t2) {
				prev[e.v] = s;
				dist[e.v] = e.t2;
				q.push(key);
				
				// cout << "the previous station to " << m_inv[e.v];
				// cout << " is " << m_inv[s] << endl;
				// cout << "the current distance is now " << inv_time(e.t2) << endl;
			}
		}
	}
}

void reset(int n) {
	g.clear();
	g.resize(n);
	
	m.clear();
	m_inv.clear();
	
	prev.clear();
	prev.resize(n, -1);

	dist.clear();
	dist.resize(n, 100000);
}

void insert(int i, int j, int t1, int t2) {
	g[i].push_back(edge(j, t1, t2));
}

void print_res(int s, int e) {
	if (prev[e] == -1) {
		cout << "No connection" << endl;
		return;
	}
	
	int i = e, j = i, t1 = dist[e], t2 = dist[e], t = dist[e];
	while (i >= 0) {
		j = i;
		i = prev[i];
		//cout << i << " " << j << " " << t << " " << inv_time(t) <<  endl;
		if (i < 0) break;
		for (int v = 0; v < g[i].size(); v++) {
			if (g[i][v].v == j && g[i][v].t2 <= t) {
				t1 = g[i][v].t1;
				//cout << "now setting t1 to " << inv_time(t1) << endl;
			}
		}
		t = t1;
	}
	
	cout << "Departure " << setfill('0') << setw(4) << inv_time(t1) << " " << m_inv[s] << endl;
	cout << "Arrival   " << setfill('0') << setw(4) << inv_time(t2) << " " << m_inv[e] << endl;
}

int main() {
	int cases, n, k, trains, t1, t2;
	string name1, name2;
	
	
	cin >> cases;
	for (int c = 0; c < cases; c++) {
		cin >> n;
		reset(n);
		
		for (int i = 0; i < n; i++) {
			cin >> name1;
			m[name1] = i;
			m_inv[i] = name1;
		}
		
		cin >> k;
		for (int i = 0; i < k; i++) {
			cin >> trains;
			
			cin >> t1;
			cin >> name1;
			trains--;
			while (trains --> 0) {
				cin >> t2;
				cin >> name2;
				//cout << name1 << " " << t1 << endl;
				//cout << name2 << " " << t2 << endl;
				
				insert(m[name1], m[name2], time(t1), time(t2));
				name1 = name2;
				t1 = t2;
			}
		}
		
		for (int i = 0; i < n; i++) {
			sort(g[i].begin(), g[i].end());
		}
		
		
		cin >> t1;
		cin >> name1;
		cin >> name2;
		
		
		djikstra(m[name1], time(t1));
		
		cout << "Scenario " << c+1 << endl;
		print_res(m[name1], m[name2]);
		
		//answer here
		cout << endl;
	}

	return 0;
}