#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <algorithm>
#include <iostream>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_with_info_2<bool,K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 Point;
typedef std::pair<Point,bool> IPoint;

using namespace std;

int getLargestComp(const vector<IPoint>& planets, int k, double r_2) {
  Delaunay t(planets.begin() + k, planets.end());
  int largest_comp = 0;
  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    v->info() = false;
  }
    
  
  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    if(v->info()) continue;
    
    stack<Delaunay::Vertex_handle> s; s.push(v);
    int size = 0;

    while(s.size() > 0) {
      auto curr = s.top(); s.pop();
      
      if(curr->info()) continue;
      curr->info() = true;
      size++;
      
      auto vi = t.incident_vertices(curr);
      do {
        if(!t.is_infinite(vi) && CGAL::squared_distance(curr->point(), vi->point()) <= r_2)
          s.push(vi);
      } while (++vi != t.incident_vertices(curr));
    }
    largest_comp = max(size, largest_comp);
  }

  return min(k, largest_comp);
}


void solve() {
  int n; cin >> n;
  double r; cin >> r;
  double r_2 = r * r;
  
  vector<IPoint> planets;
  planets.reserve(n);
  
  for(int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    planets.emplace_back(K::Point_2(x, y), false);
  }
  
  if(n <= 3) {
    cout << 1 << endl;
    return;
  }
  
  // perform binary search
  int min = 1;
  int max = n/2;
  int max_alliance = 1;
  
  while(min <= max) {
    int k = (min + max)/2;
    int alliance = getLargestComp(planets, k, r_2);
    max_alliance = std::max(max_alliance, alliance);
    
    if(alliance == k)
      min = k + 1;
    else
      max = k - 1;
  }
  cout << max_alliance << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  return 0;
}