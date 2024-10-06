#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int algorithm(int n, int m, int r_pos, int b_pos, vector<vector<int>>& transitions) {
  
  vector<vector<int>> dp(n+1, {n+1, -1});
  
  // init base case: {min, max}
  dp[n] = {0,0};
  
  for(int p = n-1; p > 0; p--) {
    //Min Case
    for(int v : transitions[p]) if (dp[v][1]+1 < dp[p][0]) dp[p][0] = dp[v][1]+1;
    
    //Max Case
    for(int v : transitions[p]) if (dp[v][0]+1 > dp[p][1]) dp[p][1] = dp[v][0]+1;
  }
  
  if(dp[r_pos][0] < dp[b_pos][0]) return 0;
  else if(dp[r_pos][0] == dp[b_pos][0]) return (dp[b_pos][0]+1) % 2;
  else return 1;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    
    int n, m; cin >> n >> m;
    int r, b; cin >> r >> b;
    
    vector<vector<int>> forward(n+1, vector<int>(0));
    int u;
    int v;
    
    for (int i = 0; i < m; i++) {
      cin >> u >> v;
      forward[u].push_back(v);
    }
    
    int res = algorithm(n, m, r, b, forward);
    cout << res << endl;
  }
  
  return 0;
}