#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;




void algorithm(int n, int m, vector<int>& strengths, vector<int>& weights) {
  
  
  sort(weights.begin(), weights.end(), greater<>());
  sort(strengths.begin(), strengths.end(), greater<>());
  
  if(weights[0] > strengths[0]) {
    cout << "impossible" << endl;
    return;
  }
  
  //cout << "n: " << n << ", m: " << m << endl;
  
  int left = (m + n - 1) / n;
  int right = m;
  //cout << "left: " << left << ", right:" << right << endl;
  
  int t = (left + right)/2;
  
  while(left != right) {
    
    // check if possible
    bool check = true;
    for(int i = 0; i < (m + t - 1)/t; i++) {
      if(weights[i*t] > strengths[i]) {
        check = false;
        break;
      }
    }
    
    // update t
    if(check) {
      right = t;
      t = (left + right)/2;
    } else {
      left = t+1;
      t = (left + right)/2;
    }
  }

  cout << t * 2 + (t - 1)*1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  for(int i = 0; i < t; i++) {
    int n, m; cin >> n >> m;
    
    vector<int> strengths;
    int s;
    for(int j = 0; j < n; j++) {
      cin >> s;
      strengths.push_back(s);
    }
    
    vector<int> weights(m);
    int w;
    for(int j = 0; j < m; j++) {
      cin >> w;
      weights[j] = w;
    }
    
    algorithm(n,m,strengths, weights);
  }
  
}