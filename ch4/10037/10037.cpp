#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;

//we'll peel off the people in pairs until no more remain.
//let a and b be the times of the fastest and 2nd fastest.
//let A and B be the times of the slowest and 2nd slowest.
//two strategies:
//1. ab then a back
//	 AB then b back
//   ==> takes 2b + a + A to ferry AB over.
//2. aA then a back
//	 aB then a back
//	 ==> takes 2a + A + B to ferry AB over.

//1 is better than 2 iff 2b+a+A<2a+A+B
//					 iff 2b<a+B

int main() {
	int cases, n, t, ans, i;
	vector<int> people;
	vector<pii> forward;
	vector<int> back;
	int a, b, A, B;
	
	cin >> cases;
	while (cases --> 0) {
		forward.clear();
		back.clear();
		
		cin >> n;
		for (i = 0; i < n; i++) {
			cin >> t;
			people.push_back(t);
		}
		
		ans = 0;
		sort(people.begin(), people.end());
		while (people.size() > 1) {
			a = people[0];
			b = people[1];
			A = people[people.size() - 1];
			B = people[people.size() - 2];
			
			if (2*b < a + B) {
				//option 1.
				forward.push_back(make_pair(a, b)); //ab
				back.push_back(a); //a
				forward.push_back(make_pair(B, A)); //AB
				back.push_back(b); //b
				
				ans += a+2*b+A;
			} else {
				//option 2.
				forward.push_back(make_pair(a, A)); //aA
				ans += A;
				if (people.size() > 2) {
					back.push_back(a); //a
					forward.push_back(make_pair(a, B)); //aB
					
					ans += a+B;
					if (people.size() > 3) {
						back.push_back(a); //a
						ans += a;
					}
				}
			}
			
			people.pop_back();
			people.pop_back();
			if (people.size() == 1) people.pop_back();
		}
		if (people.size() == 1) {
			forward.push_back(make_pair(people[0], -1));
			ans += people[0];
			people.pop_back();
		}
		
		cout << ans << endl;
		for (i = 0; i < back.size(); i++) {
			cout << forward[i].first << " " << forward[i].second << endl;
			cout << back[i] << endl;
		}
		
		if (!forward.empty())
		if (forward[i].second > 0)
		cout << forward[i].first << " " << forward[i].second << endl;
		else
		cout << forward[i].first << endl;
		
		if (cases != 0)
		cout << endl;
	}
	
	return 0;
}