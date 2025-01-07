#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int algorithm(int n, int m, int k, vector<int>& suv) {
  
  vector<vector<int>> dp(n, vector<int>(n+1, 0));
  
  if((n-1) % m == k) for(int i = 0; i < n; i++) dp[i][1] = suv[i];
  
  for(int l = 2; l <= n; l++) {
    for(int i = 0; i < n-l+1; i++) {
      
      if((n-l) % m == k) dp[i][l] = max(dp[i+1][l-1] + suv[i], dp[i][l-1] + suv[i+l-1]);
      else dp[i][l] = min(dp[i+1][l-1], dp[i][l-1]);
    }
  }
  return dp[0][n];
}

int main() {
  
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    
    int n; cin >> n;
    int m; cin >> m;
    int k; cin >> k;
    
    vector<int> suveniers;
    
    for (int i = 0; i < n; i++) {
      int v; cin >> v;
      suveniers.push_back(v);
    }
    
    int res = algorithm(n, m, k, suveniers);
    cout << res << endl;
  }
  
  return 0;
}