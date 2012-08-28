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

vector<bool> discovered(10000, false);
vector<int> dist(10000, -1);
vector<int> forbidden(10000, false);

int change_nth(int s, int d_num, bool up) {
	int p = pow(10, d_num);
	int res = s;
	
	s = (s/p)%10;
	
	if (up) {
		if (s == 9) res -= 9*p;
		else res += p;
	} else {
		if (s == 0) res += 9 * p;
		else res -= p;
	}
	
	return res;
}

vector<int> neighbours(int s) {
	vector<int> res;
	int l, r;
	for (int d_num = 0; d_num < 4; d_num++) {
		l = change_nth(s, d_num, true);
		r = change_nth(s, d_num, false);
		
		if (!forbidden[l])
		res.push_back(l);
		
		if (!forbidden[r])
		res.push_back(r);
	}
	
	return res;
}

int bfs(int s, int e) {
	discovered[s] = true;
	dist[s] = 0;
	
	queue<int> q;
	q.push(s);
	
	vector<int> v;
	while (!q.empty()) {
		s = q.front(); q.pop();
		v = neighbours(s);
		for (int i = 0; i < v.size(); i++) {
			if (!discovered[v[i]]) {
				q.push(v[i]);
				dist[v[i]] = dist[s]+1; 
				discovered[v[i]] = true;
			}
		}
	}
	
	return dist[e];
}

int input_to_num() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	return 1000*a + 100*b + 10*c + d;
}

int main() {
	int cases, n;
	int start, end, v;
	
	cin >> cases;
	while (cases --> 0) {
		fill(dist.begin(), dist.end(), -1);
		fill(discovered.begin(), discovered.end(), false);
		fill(forbidden.begin(), forbidden.end(), false);
		
		
		start = input_to_num();
		end = input_to_num();
		
		cin >> n;
		while (n --> 0) {
			v = input_to_num();
			forbidden[v] = true;
		}
		
		cout << bfs(start, end) << endl;
	}
	
	return 0;
}