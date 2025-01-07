#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <unordered_set>

using namespace std;


typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Triangle_2<K> T;
typedef CGAL::Line_2<K> L;



int algorithm(int m, int n, const vector<P>& points, const vector<vector<P>>& tps) {
  
  vector<T> triangles;
  vector<vector<int>> covered_legs(n, vector<int>(0));
  
  for (int i = 0; i < n; i++) {

    auto o1 = CGAL::intersection(L(tps[i][0], tps[i][1]), L(tps[i][2], tps[i][3]));
    P v1 = *boost::get<P>(&*o1);
    auto o2 = CGAL::intersection(L(tps[i][2], tps[i][3]), L(tps[i][4], tps[i][5]));
    P v2 = *boost::get<P>(&*o2);
    auto o3 = CGAL::intersection(L(tps[i][4], tps[i][5]), L(tps[i][0], tps[i][1]));
    P v3 = *boost::get<P>(&*o3);
    
    bool covered_prev = false;
    for(int j = 0; j < m; j++) {
      auto or0 = CGAL::orientation(v1, v2, points[j]);
      auto or1 = CGAL::orientation(v2, v3, points[j]);
      auto or2 = CGAL::orientation(v3, v1, points[j]);
    
      bool covered = (or0 <= 0 && or1 <= 0 && or2 <= 0) || (or0 >= 0 && or1 >= 0 && or2 >= 0);
      if (covered) {
        if(covered_prev) covered_legs[i].push_back(j-1);
        covered_prev = true;
      } else covered_prev = false;
    }
  }
  
  int min_cost = n;
  int left = 0;
  int right = 0;
  
  vector<int> times_covered(m-1, 0);
  for(int leg : covered_legs[0]) times_covered[leg]++;
  int missing = m-1 - covered_legs[0].size();
  
  while(true) {
    if(missing == 0 && right-left+1 < min_cost) min_cost = right-left+1;
    
    if(missing == 0) {
      if(left == right) return 1;
      
      for(int leg : covered_legs[left])
        if(--times_covered[leg] == 0) missing++;

      left ++;
    } else if(missing > 0) {
      right++;
      if(right >= n) return min_cost; 
      
      for(int leg : covered_legs[right])
        if(++times_covered[leg] == 1) missing--;
    }
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  for(int i = 0; i < t; i++) {
    int m, n; cin >> m >> n;
    vector<P> points;
    int x, y;
    for(int j = 0; j < m; j++) {
      cin >> x >> y;
      points.push_back(P(x,y));
    }
    
    vector<vector<P>> triangles(n);
    for(int j = 0; j < n; j++) {
      int a, b;
      for(int k = 0; k < 6; k++) {
        cin >> a >> b;
        triangles[j].push_back(P(a, b));
      }
    }
    
    int min_cost = algorithm(m,n,points, triangles);
    cout << min_cost << endl;
  }
  return 0;
}