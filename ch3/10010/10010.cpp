#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef long double ld;
typedef long long ll;

#define SIZE 55

int m, n;
char grid[SIZE][SIZE];
void reset(int m, int n) {
	for (int i = 0; i < m; i++)
	for (int j = 0; j < n; j++)
	grid[i][j] = 0;
}

bool check(int i, int j, string& s) {
	bool res = true;
	
	//check columns
	if (i + s.size() - 1 < m) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i+x][j] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "1 " << res << endl;
	res = true;
	if (i - s.size() + 1 >= 0) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i-x][j] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "2 " << res << endl;
	//check rows
	res = true;
	if (j + s.size() - 1 < n) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i][j+x] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "3 " << res << endl;
	res = true;
	if (j - s.size() + 1 >= 0) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i][j-x] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "4 " << res << endl;
	//check diags
	res = true;
	if (j + s.size() - 1 < n && i + s.size() - 1 < m) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i+x][j+x] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "5 " << res << endl;
	res = true;
	if (j + s.size() - 1 < n && i - s.size() + 1 < m) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i-x][j+x] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "6 " << res << endl;
	res = true;
	if (j - s.size() + 1 < n && i + s.size() - 1 < m) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i+x][j-x] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "7 " << res << endl;
	res = true;
	if (j - s.size() + 1 < n && i - s.size() + 1 < m) {
		for (int x = 0; x < s.size(); x++) {
			if (grid[i-x][j-x] != s[x]) res = false;
		}
		if (res) return true;
	}
	
	//cout << "8 " << res << endl;
	return false;
}

pair<int, int> query(string& s) {
	for (int i = 0; i < m; i++)
	for (int j = 0; j < n; j++)
	if (check(i, j, s)) return make_pair(i, j);
	
	return make_pair(-1, -1);
}

int main() {
	int cases, queries;
	pair<int, int> coords;
	string line;
	cin >> cases;
	
	while (cases --> 0) {
		cin >> m >> n;
		
		getline(cin, line);
		for (int i = 0; i < m; i++) {
			getline(cin, line);
			for (int j = 0; j < n; j++) {
				grid[i][j] = tolower(line[j]);
			}
		}
		
		cin >> queries;
		getline(cin, line);
		while (queries --> 0) {
			getline(cin, line);
			for (int i = 0; i < line.size(); i++) line[i] = tolower(line[i]);
			coords = query(line);
			cout << coords.first+1 << " " << coords.second+1 << endl;
		}
		
		if (cases != 0)
		cout << endl;
	}
	
	return 0;
}