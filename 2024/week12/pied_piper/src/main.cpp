#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef std::vector<std::vector<std::pair<int,long>>> adjacency;
typedef std::vector<std::vector<long>> dp;

void solve() {
  
  int n, m; std::cin >> n >> m;
  adjacency fwd_adj(n, std::vector<std::pair<int, long>>());
  adjacency bwd_adj(n, std::vector<std::pair<int, long>>());
  dp dp(n, std::vector<long>(n, -1));

  for (int i = 0; i < m; i++) {
    int u, v, f; std::cin >> u >> v >> f;

    if (u < v)
      fwd_adj[u].push_back({v, f});
    else
      bwd_adj[v].push_back({u, f});
  }
  
  dp[0][0] = 0;

  for(int total = 0; total < 2*n; total++) {
    for(int i = 0; i < n; i++) {
      int j = total - i;
      
      if (j < 0 || (i == j && i != 0) || j >= n || dp[i][j] == -1)
        continue;
      
      for(const auto [to, rats] : fwd_adj[i])
        if(to > j || to == n-1)
          dp[to][j] = max(dp[to][j], dp[i][j] + rats);
      
      
      for(const auto [to, rats] : bwd_adj[j])
        if(to > i || to == n-1)
          dp[i][to] = max(dp[i][to], dp[i][j] + rats);
    }
  }
  cout << dp[n-1][n-1] << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) solve();
  return 0;
}