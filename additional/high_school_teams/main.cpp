#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

int n, k, total;

void build_ref_combs(vector<vector<int>>& refs, int len, int k) {
    
  refs[0].push_back(0);
  
  for(int i = 1; i <= k; i++) {
    refs[i] = {};
    for(int j = 0; j < refs[i-1].size(); j++) {
      int last_1 = len - 1;
      
      while(last_1 > 0 && !(refs[i-1][j] & 1 << last_1))
        last_1--;
      
      if(refs[i-1][j] & 1 << last_1) last_1++;
      
      for(int r = last_1; r < len; r++) {
        refs[i].push_back(refs[i-1][j] | 1 << r);
      } 
    }
  }
  
}

void solve() {
  cin >> n; cin >> k;
  
  
  vector<int> l1(n/2);
  for(int i = 0; i < n/2; i++) {
    cin >> l1[i];
    total += l1[i];
  }
  
  vector<int> l2(n - n/2);
  for(int i = 0; i < n - n/2; i++) {
    cin >> l2[i];
    total += l2[i];
  }
  
  // build all referee combinations
  // store in [num_refs] = list of combinations in binary
  int len = n/2;
  vector<vector<int>> refs1(min(k,len)+1, vector<int>(0));
  build_ref_combs(refs1, len, min(k,len));
  
  len = n - n/2;
  vector<vector<int>> refs2(min(k,len)+1, vector<int>(0));
  build_ref_combs(refs2, len, min(k,len));

  vector<map<int, int>> teams(k+1);
  len = n/2;
  
  for(int i = 0; i <= min(len, k); i++) { // number of refs
    
    for(int s = 0; s < 1 << (len-i); s++) {
      
      for(int ref : refs1[i]) {
        int j = 0;
        int team_a = 0;
        int team_b = 0;
        
        for(int p = 0; p < len; p++) {
          if(ref & 1 << p) continue;  // player p is a ref
          
          if(s & 1 << j++) // player p is in team a
            team_a += l1[p];
          else
            team_b += l1[p];
        }
        int diff = abs(team_a - team_b);
        if(teams[i].find(diff) == teams[i].end())
          teams[i][diff] = 0;
        teams[i][diff]++;
      }
    }
  }
  
  len = n - n/2;
  int total = 0;
  
  for(int i = 0; i <= min(len, k); i++) { // number of refs
    
    for(int s = 0; s < 1 << (len-i); s++) {
      
      for(int ref : refs2[i]) {
        int j = 0;
        int team_a = 0;
        int team_b = 0;
        
        for(int p = 0; p < len; p++) {
          if(ref & 1 << p) continue;  // player p is a ref
          
          if(s & 1 << j++) // player p is in team a
            team_a += l2[p];
          else
            team_b += l2[p];
        }
        int diff = abs(team_a - team_b);
        
        for(int r = 0; r <= k - i; r++) {
          if(teams[r].find(diff) != teams[r].end())
            if(diff == 0)
              total += teams[r][diff];
            else
              total += teams[r][diff]/2;
        }
        
      }
    }
  }

  cout << total << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}