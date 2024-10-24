#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <CGAL/Gmpq.h>

using namespace std;



int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  for(int k = 0; k < t; k++) {
    int64_t n; cin >> n;
    
    vector<tuple<int64_t, int64_t, int64_t, int>> bikers(n);
    
    for(int i = 0; i < n; i++) {
      cin >> get<0>(bikers[i]) >> get<1>(bikers[i]) >> get<2>(bikers[i]);
      get<3>(bikers[i]) = i;
    }
    
    sort(bikers.begin(), bikers.end(), [](const tuple<int64_t,int64_t, int64_t, int>& a, const tuple<int64_t, int64_t, int64_t, int>& b) {
      return get<0>(a) < get<0>(b);
    });
    
    
    vector<CGAL::Gmpq> slopes(n);
    vector<bool> possible(n, true);
    
    for(int i = 0; i < n; i++)
      slopes[i] = CGAL::Gmpq(get<2>(bikers[i]) - get<0>(bikers[i]), get<1>(bikers[i]));
    
    
  
    CGAL::Gmpq best_slope = slopes.front();
    for(int i = 1; i < n; i++) {
      if(best_slope > slopes[i]) { // bikers cross
        if(CGAL::abs(best_slope) <= CGAL::abs(slopes[i])) { // best_slope is winning
          possible[get<3>(bikers[i])] = false;
        } else {
          best_slope = slopes[i];
        }
      } else {
        if (CGAL::abs(best_slope) >= CGAL::abs(slopes[i])) {
          best_slope = slopes[i];
        }
      }
    }
    
    best_slope = slopes.back();
    for(int i = n - 2; i >= 0; i--) {
      if(best_slope < slopes[i]) { // bikers cross
        if(CGAL::abs(best_slope) < CGAL::abs(slopes[i])) { // best_slope is winning
          possible[get<3>(bikers[i])] = false;
        } else {
          best_slope = slopes[i];
        }
      } else {
        if (CGAL::abs(best_slope) >= CGAL::abs(slopes[i])) {
          best_slope = slopes[i];
        }
      }
    }
    
    // print results
    for(int j = 0; j < n; j++) if(possible[j]) cout << j << " ";
    cout << endl;
  }
  
}