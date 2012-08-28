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
vector<string> code;

char* array[] = {"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
vector<string> sample;

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
bool check_phrase(vector<string>& v) {
	if (v.size() != sample.size()) return false;
	
	for (char c = 'a'; c <= 'z'; c++) {
		A[c] = '*';
	}

	for (int i = 0; i < v.size(); i++) {
		if (v[i].size() != sample[i].size()) return false;
		if (!match(v[i], sample[i], A)) return false;
	}
	
	return true;
}

int main() {
	sample.assign(array, array+9);
	
	int cases;
	string line, word;
	vector<string> phrase;
	vector<vector<string> > phrases;
	bool solvable;
	
	cin >> cases;
	getline(cin, line);
	getline(cin, line);
	while (cases --> 0) {

		phrases.clear();
		while (getline(cin, line)) {
			if (line.empty()) break;
			phrase.clear();
			stringstream ss(line);
			while (ss >> word) phrase.push_back(word);
			phrases.push_back(phrase);
		}
		
		solvable = false;
		for (int i = 0; i < phrases.size(); i++) {
			if (check_phrase(phrases[i])) {
				solvable = true;
				break;
			}
		}
		
		
		if (solvable)
		for (int i = 0; i < phrases.size(); i++) {
			cout << translate(phrases[i]) << endl;
		}
		else cout << "No solution." << endl;
		
		if (cases != 0) cout << endl;
	}
	
	return 0;
}