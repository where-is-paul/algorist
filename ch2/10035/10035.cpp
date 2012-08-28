#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

typedef long double ld;
typedef long long ll;

const int size = 10;

int carries(int a[], int b[]) {
	int res = 0, digit = 0, carry = 0;
	for (int i = 0; i < size; i++) {
		//cout << a[i] << " " << b[i] << " " << carry << endl;
		if (a[i] + b[i] + carry >= 10) {
			digit = (a[i]+b[i]) % 10;
			carry = 1;
			res++;
		} else {
			digit = a[i] + b[i] + carry;
			carry = 0;
		}
		
		b[i] = digit;
	}
	
	return res;
}

void load(ll num, int a[]) {
	int digit = 0;
	while (num > 0) {
		a[digit] = num % 10;
		num /= 10;
		digit++;
	}

} 

int a[size+1], b[size+1];

int main() {
	ll x, y;
	int ans;
	
	while (cin >> x >> y) {
		//cout << x << " " << y << endl;
		if (x == 0 && y == 0) break;
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
		
		load(x, a);
		load(y, b);
		
		ans = carries(a, b);
		if (ans == 0) cout << "No carry operation." << endl;
		else if (ans == 1) cout << "1 carry operation." << endl;
		else cout << ans << " " << "carry operations." << endl;
	}
	return 0;
}