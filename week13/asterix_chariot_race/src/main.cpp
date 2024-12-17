#include <iostream>
#include <vector>
#include <tuple>
#include<unordered_map>
#include <numeric>
using namespace std;


tuple<int, int, int> solve_rec(
  unordered_map<int,vector<int>>& adj_map,
  vector<int>& costs,
  int root,
  int from) {
    
    vector<int> sub_p0;
    vector<int> sub_p1;
    vector<int> sub_p2;
    
    for(int neighbor : adj_map[root]) {
      if(neighbor == from) continue;
      auto [p0, p1, p2] = solve_rec(adj_map, costs, neighbor, root);
      sub_p0.push_back(p0);
      sub_p1.push_back(p1);
      sub_p2.push_back(p2);
    }
    
    int p0, p1, p2;
    int sub_p0_sum = accumulate(sub_p0.begin(), sub_p0.end(), 0);
    int sub_p1_sum = accumulate(sub_p1.begin(), sub_p1.end(), 0);
    int sub_p2_sum = accumulate(sub_p2.begin(), sub_p2.end(), 0);
    
    // calculate p0
    p0 = costs[root] + sub_p2_sum;
    
    for(int i = 0; i < sub_p0.size(); i++) {
      p0 = min(p0, sub_p0_sum - sub_p0[i] + sub_p1[i]);
    }
    
    // calculate p1
    p1 = costs[root] + sub_p2_sum;
    
    // calculate p2
    p2 = min(costs[root] + sub_p2_sum, sub_p0_sum);
    
    return make_tuple(p0, p1, p2);
  }

void solve() {
  int n; cin >> n;
  
  unordered_map<int,vector<int>> adj_map;
  for(int i = 0; i < n-1; i++) {
    int x, y; cin >> x >> y;
    if(adj_map.find(x) == adj_map.end())
      adj_map[x] = vector<int>();
      
    if(adj_map.find(y) == adj_map.end())
      adj_map[y] = vector<int>();
      
    adj_map[x].push_back(y);
    adj_map[y].push_back(x);
  }
  
  vector<int> costs(n);
  for(int i = 0; i < n; i++) {
    cin >> costs[i];
  }
  
  auto [p0, p1, p2] = solve_rec(
    adj_map,
    costs,
    0,
    -1);
    
  cout << p0 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  return 0;
}