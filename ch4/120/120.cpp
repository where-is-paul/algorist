#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

typedef long double ld;
typedef long long ll;

vector<int> pancakes;

//flips the rest of the pancakes from the ith (including) to the end.
void flip(int i) {
	reverse(pancakes.begin() + i, pancakes.end());
	cout << i+1 << " ";
}

//flips the pancake in the ith position to the jth position
void flip_to(int i, int j) {
	if (i != pancakes.size() - 1)
	flip(i); //ith pancake now at end
	flip(j); //ith pancake now at jth, jth at end
}

void pancake_sort() {
	int min;
	for (int i = 0; i < pancakes.size(); i++) {
		min = i;
		for (int j = i; j < pancakes.size(); j++) {
			if (pancakes[min] < pancakes[j]) min = j;
		}
		
		if (i != min)
		flip_to(min, i);
	}
	
	cout << 0 << endl;
}

int main() {
	string line;
	int n;
	while (getline(cin, line)) {
		cout << line << endl;
		pancakes.clear();
		stringstream ss(line);
		while (ss >> n) pancakes.push_back(n);
		reverse(pancakes.begin(), pancakes.end());
		pancake_sort();
	}
	return 0;
}