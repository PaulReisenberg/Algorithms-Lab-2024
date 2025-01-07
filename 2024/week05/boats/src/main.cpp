#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct VectorComparator {
    bool operator()(const std::vector<int>& lhs, const std::vector<int>& rhs) const {
        
        if (lhs.size() < 2 || rhs.size() < 2) {
            // Handle the case where a vector doesn't have enough elements
            return lhs.size() < rhs.size();
        }
        return lhs[1] < rhs[1];
    }
};

void algorithm(int n, set<vector<int>, VectorComparator>& boats) {
  
  // num boats, last boat, last position
  vector<int> dp = {1, (*boats.begin())[1], -99999};
  
  for(vector<int> boat : boats) {
    int l = boat[0];
    int r = boat[1];
    //cout << "l: " << l << ", r: " << r << endl;
    // we can park a new boat without removing the last boat
    if(dp[1] <= r) {
      
      int rightmost = l + r - min(l, r - dp[1]);
      dp = {dp[0]+1, rightmost,dp[1]};
    
    // we can park a new boat but have to remove the last boat
    } else if(dp[2] <= r) {
      int rightmost = l + r - min(l, r - dp[2]);
      if(rightmost < dp[1])
        dp = {dp[0], rightmost, dp[2]};
    }
  }

  cout << dp[0] << endl;
}



int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  int n, l, p;
  
  
  for(int i = 0; i < t; i++) {
    cin >> n;
    //vector<vector<int>> boats(n, {0,0});
    set<vector<int>, VectorComparator> boats;
    for(int i = 0; i < n; i++) {
      cin >> l >> p;
      boats.insert({l,p});
    }
    
    //for(vector<int> boat : boats)
    //  cout << "l: "<< boat[0] << " , r: " <<  boat[1] << endl;
    algorithm(n, boats);
  }
  
}