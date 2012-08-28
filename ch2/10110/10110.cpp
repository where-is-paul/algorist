#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long double ld;
typedef long long ll;

int main() {
	ld x;
	while (cin >> x) {
		if (x == 0) break;
		if (sqrt(x) - int(sqrt(x)) < 1e-8) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}