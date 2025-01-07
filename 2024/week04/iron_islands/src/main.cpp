#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int algorithm(int n, int k, int w, vector<vector<int>>& water_ways) {
  
  int max_score = 0;
  unordered_map<int, vector<int>> ps;   // record Partial Scores
  
  for(int u = 0; u < w; u++) {
    vector<int> ww = water_ways[u];
    int left, right; left = right = 0;
    int sum = ww[0];
    
    while(true) {
      int score = right - left + 1;
      if(sum == k) max_score = max(max_score, score);  
      
      if (left == 0 && right > 0) {
        if(ps.find(sum-ww[0]) == ps.end()) 
          ps[sum-ww[0]] = {u, score-1, -1};
        else if(score-1 > ps[sum-ww[0]][1]) 
          ps[sum-ww[0]] = {u, score-1, ps[sum-ww[0]][1]};
      }
      
      if(sum < k && left == 0 && ps.find(k - sum) != ps.end()) {
        if(ps[k - sum][0] < u)
          max_score = max(max_score, score + ps[k - sum][1]);
        else if (ps[k - sum][2] != -1)
          max_score = max(max_score, score + ps[k - sum][2]);
      }
      
      if(sum < k || right == left) {
        right += 1;
        if (right >= ww.size()) break;
        sum += ww[right];
      } else if (sum >= k) {
        sum -= ww[left];
        left += 1;
      }
    }
  }
  return max_score;
}


int main() {
  
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    
    int n, k, w; cin >> n >> k >> w;
    
    vector<int> men_required(n);
    for(int i = 0; i < n; i++) {
      int men; cin >> men;
      men_required[i] = men;
    }
    
    vector<vector<int>> water_ways(w);
    for(int i = 0; i < w; i++) {
      int l; cin >> l;
      for(int j = 0; j < l; j++) {
        int island; cin >> island;
        water_ways[i].push_back(men_required[island]);//.insert(water_ways[i].begin(), men_required[island]);
      }
    }
    
    int res = algorithm(n, k, w, water_ways);
    cout << res << endl;
  }
  
  return 0;
}