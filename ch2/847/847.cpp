#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long double ld;
typedef long long ll;

map<ll, bool> dp;
ll limit = 0;

bool winner(ll x) {
	if (dp.count(x)) return dp[x];
	if (x >= limit) return false;
	
	bool win = false;
	ll arg;
	for (int i = 2; i < 10; i++) {
		if ( !winner(x * i) ) {
			win = true;
			break;
		}
	}
	
	dp[x] = win;
	return win;
	
}

int main() {
	
	while (cin >> limit) {
		dp.clear();
		if (winner(1)) cout << "Stan wins." << endl;
		else cout << "Ollie wins." << endl;
	}
	
	return 0;
}