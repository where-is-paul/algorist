#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>

using namespace std;

typedef long double ld;
typedef long long ll;

map<char, char> A;
vector<string> dict;
vector<string> code;
vector<string> sorted_code;


string translate(vector<string>& code) {
	string res = "";
	for (int i = 0; i < code.size(); i++) {
		for (int j = 0; j < code[i].size(); j++) {
			res += A[code[i][j]];
		}
		
		if (i != code.size() - 1)
		res += " ";
	}
	
	return res;
}

//check if substitution cipher used is one-to-one.
//counts all the mappings of A (a->m_1, b->m_2, ...) and
//maps these m_i to F and if an m_i is mapped twice,
//then A is certainly not one-to-one.
bool injective(map<char, char>& B) {
	map<char, bool> F;
	for (char c = 'a'; c <= 'z'; c++) {
		if ( B[c] != '*' && F.count(B[c]) ) return false;
		else F[B[c]] = true;
	}
	
	return true;
}

//check if two words could possibly be transformed into each other.
//two conditions:
//1. they must have the same pattern. abb->eff works but abb->efg does not.
//2. they must maintain a one-to-one mapping.
bool match(const string& w, const string& z, map<char, char>& B) {
	
	for (int i = 0; i < w.size(); i++) {
		//checks cond 1.
		if ((B[w[i]] != '*') && (B[w[i]] != z[i])) return false;
		else B[w[i]] = z[i];
	}
	
	//checks cond 2.
	return injective(B);
}

//i - processing the ith word in sorted_code
bool backtrack(map<char, char>& A, int i) {
	if (i == sorted_code.size()) return true;
	
	map<char, char> B;
	for (int j = 0; j < dict.size(); j++) {
		if (dict[j].size() == sorted_code[i].size()) {
			B = A;
			if (match(sorted_code[i], dict[j], B)) {
				if (backtrack(B, i+1)) {
					A = B;
					return true;
				}
			}
		}
	}
	
	return false;
}

bool comp(const string& s1, const string& s2) {
	if (s1.size() == s2.size()) return true;
	return s1.size() > s2.size();
}

int main() {
	int n;
	string word, line;
	cin >> n;
	
	while (n --> 0) {
		cin >> word;
		dict.push_back(word);
	}
	sort(dict.begin(), dict.end(), comp);
	
	getline(cin, line);
	while (getline(cin, line)) {
		stringstream ss(line);
		
		for (char c = 'a'; c <= 'z'; c++) {
			A[c] = '*';
		}
		code.clear();
		sorted_code.clear();
		
		while (ss >> word) {
			code.push_back(word);
		}
		
		sorted_code.assign(code.begin(), code.end());
		sort(sorted_code.begin(), sorted_code.end(), comp);
		
		backtrack(A, 0);
		cout << translate(code) << endl;
	}
	
	return 0;
}