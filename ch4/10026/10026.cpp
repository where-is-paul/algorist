#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;
typedef long long ll;

vector<int> T, S, v;

ll cost(int t, int s, int k) {
	ll res = 0;
	for (int i = 0; i < k; i++) {
		res += s*T[i];
	}
	
	for (int i = k; i < S.size(); i++) {
		res += t*S[i];
	}
	
	return res;
}

//this essentially reduces to an insertion sort with a special comparator.
//we can also use the STL sort. job (t1, s1) is less than job (t2, s2) if 
//t1*s2 < t2*s1. this reflects the fact that ordering
// t1 s1
// t2 s2
//has a cost of t1*s2 where as ordering the other way around has a cost of
//t2*s1. thus we order job 1 first if t1*s2 < t2*s1
int main() {
	ll cases, n, s, t, min_cost, min;
	cin >> cases;
	while (cases --> 0) {
		T.clear();
		S.clear();
		v.clear();
		
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> t >> s;
			
			min_cost = 1e10;
			min = 0;
			for (int k = 0; k < T.size()+1; k++) {
				if (cost(t,s,k) <= min_cost) {
					//cout << "new mincost is " << cost(t,s,k) << endl;
					min = k;
					min_cost = cost(t,s,k);
				}
			}
			//cout << "best additional cost is: " << min_cost << endl << endl;
			T.insert(T.begin()+min, t);
			S.insert(S.begin()+min, s);
			v.insert(v.begin()+min, i+1);
		}
		
		for (int i = 0; i < n-1; i++) {
			cout << v[i] << " ";
		}
		cout << v[n-1] << endl;
		
		if (cases != 0) cout << endl;
	}
	
	return 0;
}