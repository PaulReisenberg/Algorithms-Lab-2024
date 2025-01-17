#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <limits>

// Basic type definitions
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

using namespace std;

typedef K::Point_2 P;

long floor_to_long(K::FT val_ft) {
  long val_long = (long) CGAL::to_double(val_ft);
  while(K::FT(val_long) < val_ft) val_long++;
  while(K::FT(val_long-1) >= val_ft) val_long--;
  
  return val_long;
}

void solve(int n, vector<P>& points) {
  
  Triangulation t(points.begin(), points.end());
  
  K::FT min_len(numeric_limits<int>::max());
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
    K::FT l = t.segment(e).squared_length();
    if(l < min_len)
      min_len = l;
  }
  min_len = (CGAL::sqrt(min_len)*100)/2;
  cout << floor_to_long(min_len) << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  
  
  int n; cin >> n;
  while(n) {
    vector<P> points(n);
    for(int i = 0; i < n; i++) {
      int x, y; cin >> x >> y;
      points[i] = P(x,y);
    }
    
    solve(n, points);
    cin >> n;
  }
  return 0;
}