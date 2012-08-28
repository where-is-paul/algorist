#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef long double ld;
typedef long long ll;

typedef vector<vector<int> > graph;
graph g;
vector<int> height;

const int len = 104729;
vector<vector<pair<string, int> > > table(len);

ll hash(string& s) {
	ll res = 0, alpha = 1;
	for (int i = 0; i < s.size(); i++) {
		res = (res + alpha*int(s[i])) % len;
		alpha = (alpha*26) % len;
	}
	
	return res;
}

void insert(string& s, int& i) {
	table[hash(s)].push_back(make_pair(s, i));
}

pair<string, int> find(string& s) {
	ll h = hash(s);
	for (int i = 0; i < table[h].size(); i++) {
		if (table[h][i].first.compare(s) == 0) {
			return table[h][i];
		}
	}
	
	return make_pair("",-1);
}

void insert(int x, int y) {
	g[x].push_back(y);
}

void all_combos(string& s, vector<string>& v) {
	v.clear();
	string word = s;
	//substitutions
	for (int i = 0; i < s.size(); i++) {
		for (char c = s[i]+1; c <= 'z'; c++) {
			word[i] = c;
			v.push_back(word);
		}
		word[i] = s[i];
	}
	
	//insertions
	for (int i = 0; i < s.size(); i++) {
		word.insert(word.begin()+i, 'a');
		for (char c = s[i]+1; c <= 'z'; c++) {
			word[i] = c;
			v.push_back(word);
		}
		word.erase(word.begin()+i);
	}
	
	word.insert(word.end(),'a');
	for (char c = 'a'; c <= 'z'; c++) {
		word[word.size()-1]=c;
		v.push_back(word);
	}
	word.erase(word.begin()+word.size()-1);
	
	//deletions
	for (int i = 0; i < s.size()-1; i++) {
		if (word[i] >= word[i+1]) continue;
		word.erase(word.begin()+i);
		v.push_back(word);
		word.insert(word.begin()+i, s[i]);
	}

}

void construct_graph(vector<string>& words) {
	for (int i = 0; i < words.size(); i++) {
		insert(words[i], i);
	}
	g.resize(words.size());
	height.resize(words.size(), 1);
	
	vector<string> neighbours;
	pair<string, int> elem;
	for (int i = 0; i < words.size(); i++) {
		all_combos(words[i], neighbours);
		for (int j = 0; j < neighbours.size(); j++) {
			elem = find(neighbours[j]);
			if (elem.second > 0) {
				insert(i, elem.second);
			}
		}
	}
}

int dfs(int& s) {
	if (height[s] != 1) return height[s];
	int res = height[s];
	
	for (int i = 0; i < g[s].size(); i++) {
		res = max(res, 1+dfs(g[s][i]));
	}
	
	height[s] = res;
	return res;
}


int main() {
	string word;
	vector<string> words, v;
	while (cin >> word) words.push_back(word);
	
	construct_graph(words);
	
	int res = 0;
	for (int i = 0; i < words.size(); i++) {
		res = max(res, dfs(i));
	}
	
	cout << res << endl;
	
	return 0;
}