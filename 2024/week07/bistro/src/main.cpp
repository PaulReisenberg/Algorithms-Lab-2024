#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Iterator_range.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K>::Vertex_handle Vertex;
typedef Triangulation::Finite_faces_iterator Face_iterator;


//typedef CGAL::Iterator_range<CGAL::Point_iterator> PI;

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(0);
  
  int n, m;
  cin >> n;
  while(n != 0) {
    
    vector<P> pts;
    pts.reserve(n);
    
    for(int i = 0; i < n; i++) {
      int x,y; cin >> x >> y;
      pts.emplace_back(x, y);
    }
    
    Triangulation t(pts.begin(), pts.end());
    cin >> m;
    for(int i = 0; i < m; i++) {
      int x, y; cin >> x >> y;
      P p = P(x,y);
      K::FT distance2 = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
      cout<< distance2 << "\n";
    }
    cin >> n;
  }
}
