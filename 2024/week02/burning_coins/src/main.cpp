#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int algorithm(int n, vector<int>& coins) {
  
  vector<vector<int>> dp(n, vector<int>(n+1, 0));
  
  // dp[i][l] -> problem at index i with length l
  if(n%2 != 0) for(int i = 0; i < n; i++) dp[i][1] = coins[i];
  
  for(int l = 2; l <= n; l++) {
    for(int i = 0; i <= n-l; i++) {
      
      if((n-l)%2 == 0) { // We can take a coin
        dp[i][l] = max(coins[i]+dp[i+1][l-1], coins[i+l-1] +dp[i][l-1]);
      
      } else {  // Our opponent takes a coin
        dp[i][l] = min(dp[i+1][l-1], dp[i][l-1]);
      }
    }
  }
  return dp[0][n];
}

int main() {
  
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    int n; cin >> n;
    vector<int> coins;
    
    for (int i = 0; i < n; i++) {
      int v; cin >> v;
      coins.push_back(v);
    }
    
    int res = algorithm(n, coins);
    cout << res << endl;
  }
  
  return 0;
}