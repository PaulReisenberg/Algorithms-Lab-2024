#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

void solve() {
  int n; cin >> n;
  
  vector<int> word_count(n);
  for(int i = 0; i < n; i++)
    cin >> word_count[i];

  unordered_map<long, vector<long>> pos_to_words;
  set<long> pos;
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < word_count[i]; j++) {
      long p; cin >> p;
      if(pos_to_words.find(p) == pos_to_words.end()) {
        pos.insert(p);
        pos_to_words[p] = {};
      }
      pos_to_words[p].push_back(i);
    }
  }
  
  // Sliding Window
  vector<long> pos_vec(pos.begin(), pos.end());
  vector<int> count(n);
  int missing = n;
  
  long left, right, min_snip;
  left = right = 0;
  min_snip = pos_vec[pos_vec.size() - 1] - pos_vec[0] + 1;
  
  for(long w : pos_to_words[pos_vec[right]])
    if(++count[w] == 1) missing--;
  
  while(right < pos_vec.size()) {
    
    if(missing == 0)
      min_snip = min(min_snip, pos_vec[right] - pos_vec[left] + 1);
    
    if(missing == 0 && left < right) {
      // move left
      for(long w : pos_to_words[pos_vec[left]])
        if(--count[w] == 0) missing++;
      left++;
      
    } else {
      // move right
      right++;
      for(long w : pos_to_words[pos_vec[right]])
        if(++count[w] == 1) missing--;
    }
  }
  
  cout << min_snip << endl;
  
  
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}