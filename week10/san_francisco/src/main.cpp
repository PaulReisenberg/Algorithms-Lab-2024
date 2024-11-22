#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
  int to;
  int points;
};

int max_points(const vector<Edge>& edges) {
  int x = 0;
  for(Edge e : edges) {
    x = max(x, e.points);
  }
  return x;
}

void solve() {
  long n, m, x, k;
  cin >> n; cin >> m; cin >> x; cin >> k;
  
  vector<vector<Edge>> graph(n);
  for(int i = 0; i < m; i++) {
    int u, v, p; cin >> u; cin >> v; cin >> p;
    graph[u].push_back({v,p});
  }
  vector<bool> outgoing(n);
  for(int i = 0; i < n; i++)
    outgoing[i] = graph[i].size() > 0;
  
  for(int i = 0; i < n; i++)
    for(int j = 0; j < graph[i].size(); j++)
      if(!outgoing[graph[i][j].to]) graph[i][j].to = 0;
  
  
  vector<vector<long>> dp(k+1, vector<long>(n));
  
  for(int i = 1; i <= k; i++) {
    for(int j = 0; j < n; j++) {
      long max_points = 0;
      for(Edge e : graph[j])
        max_points = max(max_points, e.points + dp[i-1][e.to]);

      dp[i][j] = max_points;
    }
    if(dp[i][0] >= x) {
      cout << i << endl;
      return;
    }
  }
  
  

  
  cout << "Impossible" << endl;
}





int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  return 0;
}

