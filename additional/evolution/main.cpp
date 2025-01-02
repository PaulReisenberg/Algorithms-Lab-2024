#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

void solve() {
  int n, q; cin >> n >> q;
  
  vector<string> names(n);
  unordered_map<string, int> ids;
  vector<int> ages(n);
  
  for(int i = 0; i < n; i++) {
    string name; cin >> name;
    int a; cin >> a;
    
    names[i] = name;
    ids[name] = i;
    ages[i] = a;
  }
  
  vector<int> backward(n, -1);
  vector<bool> leaf(n, true);
  for(int i = 0; i < n-1; i++) {
    string s, p; cin >> s >> p;
    backward[ids[s]] = ids[p];
    leaf[ids[p]] = false;
  }
  
  
  vector<pair<int, int>> indices(n);
  vector<vector<int>> lists;
  vector<bool> visited(n, false);
  for(int i = 0; i < n; i++) {
    if(!leaf[i]) continue;
    
    int list_index = lists.size();
    int pos = 0;
    vector<int> list;
    
    for(int curr = i; curr != -1; curr = backward[curr]) {
      list.push_back(curr);
      indices[curr] = {list_index, pos};
      pos++;
    }
    lists.push_back(list);
  }
  
  for(int i = 0; i < q; i++) {
    string s; cin >> s;
    int b; cin >> b;
    
    int ind = indices[ids[s]].first;
    int pos = indices[ids[s]].second;
    int left = pos+1;
    int right = lists[ind].size()-1;
    
    
    while(left < right) {
      int middle = (left + right)/2 + 1;
      int ancestor = lists[ind][middle];
      if(ages[ancestor] > b)
        right = middle-1;
      else
        left = middle;
    }
    
    if (i == q-1) cout << names[lists[ind][left]] << endl;
    else cout << names[lists[ind][left]] << " ";
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}