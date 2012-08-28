#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <queue>
#include <string.h>
#include <algorithm>

using namespace std;

typedef long double ld;
typedef long long ll;

typedef queue<int> vote;

inline void scan_votes(vector<vote>& v, int& best, int& worst, int n) {
	for (int i = 0; i < n; i++) {
		if (v[i].empty()) continue;
		if (v[i].size() > v[best].size()) best = i;
		if (v[worst].empty() || (v[i].size() < v[worst].size()) ) worst = i;
	}
}

inline void get_best(vector<vote>& votes, vector<vote>& v) {
	for (int i = 0; i < votes.size(); i++) {
		v[ votes[i].front() ].push(i);
	}
}

bool all_tied(vector<vote>& v) {
	int vote_num = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].empty()) continue;
		if (vote_num == 0) vote_num = v[i].size();
		if (vote_num != v[i].size()) return false;
	}
	
	return true;
}

void solve(vector<string>& candidates, vector<vote>& votes) {
	vector<vote> vote_count(20);
	int best = 0, worst = 0;

	get_best(votes, vote_count);
	scan_votes(vote_count, best, worst, candidates.size());
	
	int i, j, k;
	if (!votes.empty())
	while (!all_tied(vote_count) && (vote_count[best].size() <= (int) votes.size()/2)) {
		while (!vote_count[worst].empty()) {
			k = vote_count[worst].front();
			vote_count[worst].pop();
	
			votes[k].pop();
			vote_count[ votes[k].front() ].push(k);
		}

		scan_votes(vote_count, best, worst, candidates.size());
	}
	
	for (int i = 0; i < candidates.size(); i++) {
		if (vote_count[i].size() == vote_count[best].size())
		cout << candidates[i] << endl;
	}
}

int main() {
	vector<string> candidates;
	vector<vote> votes;
	
	string line;
	int n, num_cands, c;
	cin >> n;
	while (n --> 0) {
		candidates.clear();
		votes.clear();
		
		cin >> num_cands;
		getline(cin, line);
		for (int i = 0; i < num_cands; i++) {
			getline(cin, line);
			candidates.push_back(line);
		}
		
		while (getline(cin, line)) {
			if (line.empty()) break;
			
			vote v;
			stringstream ss(line);
			while (ss >> c) v.push(c-1);
			votes.push_back(v);
		}
		
		solve(candidates, votes);
		
		if (n != 0)
		cout << endl;
	}
	
	return 0;
}