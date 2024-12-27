#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;


void solve() {
  
  int n; cin >> n;
  vector<int> parasols(n);
  for(int i = 0; i < n; i++) {
    cin >> parasols[i];
  }
  
  sort(parasols.begin(), parasols.end());
  
  int i = 0;
  int j = 0;
  int left;
  int right;
  
  int max_p = 0;
  int min_d = 201;
  int count = 1;
  std::vector<int> sols = {parasols[0]};
  
  while(true) {
    left = parasols[i];
    right = parasols[j];
    
    if(right - left <= 200 && count > max_p) {
        max_p = count;
        min_d = (right-left+1) / 2;
        
        if((right-left) % 2 == 0) 
          sols = {left + min_d};
        else 
          sols = {left + min_d-1, left + min_d};
          
      } else if (right - left <= 200 && count == max_p) {
        int d = (right-left+1) / 2;
        if(d < min_d) {
          min_d = d;
          if((right-left) % 2 == 0) 
            sols = {left + min_d};
          else 
            sols = {left + min_d - 1, left + min_d};
        
        } else if (d == min_d) {
          if((right-left) % 2 == 0) {
            sols.push_back(left+d);
          } else {
            sols.push_back(left+d-1);
            sols.push_back(left+d);
          } 
        }
    }
    
    if (i == j || right - left <= 200) {
      j++;
      count++;
    } else {
      i++;
      count--;
    }
    if(j >= parasols.size()) break;
    
  }
  
  std::cout << max_p << " " << min_d << std::endl;
  
  for(int i = 0; i < sols.size() - 1; i++) {
    std::cout << sols[i] << " ";
  }
  std::cout << sols[sols.size() - 1] << std::endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}