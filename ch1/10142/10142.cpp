#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

typedef long double ld;
typedef long long ll;

typedef vector<int> vote;

bool all_tied(vector<int>& v) {
	int vote_num = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == -1) continue;
		if (vote_num == 0) vote_num = v[i];
		if (vote_num != v[i]) return false;
	}
	
	return true;
}

inline void get_best(vector<vote>& votes, set<int>& ignores, vector<int>& v, int& best, int& worst) {
	
	for (int i = 0; i < votes.size(); i++) {
		for (int j = 0; j < votes[i].size(); j++) {
			if ( ignores.count(votes[i][j]) ) continue;

			v[ votes[i][j] ]++;
			break;
		}
	}
	
	worst = best;
	for (int i = 0; i < 20; i++) {
		//cout << v[i] << " ";
		if (v[i] < 0) continue;
		if (v[i] > v[best]) best = i;
		if (v[i] < v[worst]) worst = i;
	}
	//cout << endl;

}

void solve(vector<string>& candidates, vector<vote>& votes) {
	set<int> ignores;
	vector<int> vote_count(20, -1);
	int best = 0, worst = 0;

	get_best(votes, ignores, vote_count, best, worst);
	while (!all_tied(vote_count) && (vote_count[best] <= (int) votes.size()/2) ) {
		fill(vote_count.begin(), vote_count.end(), -1);
		get_best(votes, ignores, vote_count, best, worst);
		ignores.insert(worst);
		
		//check for dups.
		for (int i = 0; i < 20; i++) {
			if (vote_count[i] == vote_count[worst]) ignores.insert(i);
		}
		
		//cout << best << " " << worst << " " << vote_count[best] <<  " " << votes.size() << " " << candidates[best] << endl;
	}
	
	for (int i = 0; i < candidates.size(); i++) {
		if (vote_count[i] == vote_count[best])
		cout << candidates[i] << endl;
	}
}

int main() {
	vector<string> candidates;
	vector<vote> votes;
	
	string line;
	int n, num_cands, c;
	cin >> n;
	while (n--) {
		candidates.clear();
		votes.clear();
		
		cin >> num_cands;
		getline(cin, line);
		for (int i = 0; i < num_cands; i++) {
			getline(cin, line);
			candidates.push_back(line);
		}
		
		while (getline(cin, line)) {
			if (line == "") break;
			
			vote v;
			stringstream ss(line);
			while (ss >> c) v.push_back(c-1);
			votes.push_back(v);
			
			// for (int i = 0; i < v.size(); i++) {
				// cout << v[i] << " ";
			// }

		}
		
		solve(candidates, votes);	
		
		if (n != 0)
		cout << endl;
	}
	
	return 0;
}