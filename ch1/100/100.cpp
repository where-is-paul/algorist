#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

typedef long double ld;
typedef long long ll;

ll collatz[1000005];

ll get_collatz(ll j) {
	
	ll res = 0;
	while (true) {
		if ((j < 1000000) && (collatz[j] > 0)) 
			return res+collatz[j];
		
		if (j % 2) {
			j = 3*j + 1;
		} else {
			j = j/2;
		}
		
		res++;
	}
	
}

int main() {
	memset(collatz, -1, sizeof(collatz));
	
	ll i, j;
	collatz[1] = 1;
	for (i = 1; i < 1000000; i++) {
		//cout << i;
		collatz[i] = get_collatz(i);
		//cout << " " << get_collatz(i) << endl;
	}
	
	ll w, r; 
	while (cin >> i >> j) {
		w = i, r = j;
		if (j < i) {
			w = j;
			r = i;
		}
		cout << i << " " << j << " " << *max_element(collatz+w, collatz+r+1) << endl;
	}
	
	return 0;
}