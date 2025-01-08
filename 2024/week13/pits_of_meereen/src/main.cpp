#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vvvvi = vector<vvvi>;
using vvvvvi = vector<vvvvi>;
using vvvvvvi = vector<vvvvvi>;

int n, k, m; 

void solve() {
  cin >> n >> k >> m;
  
  vector<int> type(n);
  for(int i = 0; i < n; i++)
    cin >> type[i];
  
  vvvvvvi dp(n, vvvvvi(k+1, vvvvi(k+1, vvvi(k+1, vvi(k+1, vi(29, -1))))));
  
  for(int f = n-1; f >= 0; f--) {
    for(int n1 = 0; n1 < k+1; n1++) {
      for(int n2 = 0; n2 < k+1; n2++) {
        if(n1 == k && n2 != k) continue; // pruning invalid "no fighter" combinations
        for(int s1 = 0; s1 < k+1; s1++) {
          for(int s2 = 0; s2 < k+1; s2++) {
            
            // prune impossible states
            if(s1 == k && s2 != k) continue; // pruning invalid "no fighter" combinations
            if(f > 0 && s1 == k && n1 == k) continue; // pruning based on predecessor
            if(f > 0 && s1 != type[f-1] && type[f-1] != n1) continue; // pruning based on predecessor
            if(f > 1 && m == 3 && s1 != type[f-2] && s2 != type[f-2] && n1 != type[f-2] && n2 != type[f-2]) continue; // pruning based on pre-predecessor
            
            for(int d = -10 - (f%2); d <= 10 + (f%2); d+=2) {
              
              int type_f = type[f];
              
              // calculate score north
              int distinct_n = 1;
              if(n1 != k && type_f != n1) distinct_n++;
              if(m == 3 && n2 != k && n2 != n1 && n2 != type_f) distinct_n++;
              
              int d_n = d+1;
              
              int score_n = 1000 * distinct_n - pow(2, abs(d_n));
              
              // calculate score south
              int distinct_s = 1;
              if(s1 != k && type_f != s1) distinct_s++;
              if(m == 3 && s2 != k && s2 != s1 && s2 != type_f) distinct_s++;
              
              int d_s = d-1;
              
              int score_s = 1000 * distinct_s - pow(2, abs(d_s));
              
              
              if(f == n-1) {
                dp[f][n1][n2][s1][s2][d+11] = max(score_n, score_s);
              } else {
                int sub_n = -1;
                if(d_n <= 11)
                  sub_n = dp[f+1][type_f][n1][s1][s2][d_n + 11];
                
                int sub_s = -1;
                if(d_s >= -11)
                  sub_s = dp[f+1][n1][n2][type_f][s1][d_s + 11];
                
                if((score_n < 0 && score_s < 0)
                || (score_n < 0 && sub_s < 0)
                || (score_s < 0 && sub_n < 0)) {
                  dp[f][n1][n2][s1][s2][d+11] = -1;
                } else {
                  dp[f][n1][n2][s1][s2][d+11] = max(
                    score_n + sub_n,
                    score_s + sub_s
                  );
                }
              }
            }
          }
        }
      }
    }
  }
  cout << dp[0][k][k][k][k][11] << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}