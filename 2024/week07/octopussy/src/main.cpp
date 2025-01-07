#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> read_iv(int n) {
  vector<vector<int>> vec(n);
  int x;
  for(int i = 0; i < n; i++) {
    cin >> x;
    vec[i] = {i, x}; 
  }
  return vec;
}


void solve() {
  int n; cin >> n;
  vector<vector<int>> times = read_iv(n);
  sort(times.begin(), times.end(),  [](const vector<int>& a, const vector<int>& b) {
         return a[1] < b[1];
    });
  
  vector<bool> defused(n, false);
  
  int time = 0;
  for(int j = 0; j < n; j++) {
    int i = times[j][0];          // index of the next bomb that has to be defused
    if(defused[i]) continue;
    
    queue<int> Q; Q.push(i);
    while(!Q.empty()) {
      int current = Q.front(); Q.pop();
      if(defused[current]) continue;
      
      defused[current] = true;
      time++;
      if(current >= (n-1)/2) continue;
      
      Q.push(2*current+1);
      Q.push(2*current+2);
    }
    if(time > times[j][1]) {
      cout << "no" << endl;
      return;
    }
  }
  cout << "yes" << endl;
  return;
  
  
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) solve();
  return 0;
}