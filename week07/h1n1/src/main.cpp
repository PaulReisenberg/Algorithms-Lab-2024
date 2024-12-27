#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <algorithm>
using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<double,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;

void solve(int n) {
  int m;
  
  vector<P> infected(n);
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    infected[i] = P(x,y);
  }
  
  cin >> m;
  vector<pair<P, long>> users(m);  // Changed to store points with their distances
  for(int i = 0; i < m; i++) {
    int x, y; 
    long d;
    cin >> x >> y >> d;  // Read d along with coordinates
    users[i] = {P(x,y), d};  // Store both point and distance
  }
  
  Triangulation t(infected.begin(), infected.end());
  priority_queue<pair<double, Face_handle>> q;
  
  for(auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
    if(t.is_infinite(f)) {
      f->info() = numeric_limits<long>::max();
      q.push(make_pair(f->info(), f));
    } else {
      f->info() = 0;  
    }
  }
  
  while(!q.empty()) {
    auto curr = q.top(); q.pop();
      
    for(int i = 0; i < 3; i++) {
      auto f = curr.second;
      auto nf = f->neighbor(i);
      P p1 = f->vertex((i+1)%3)->point();
      P p2 = f->vertex((i+2)%3)->point();
      K::FT distance2 = CGAL::squared_distance(p1, p2);
      double space = min(CGAL::to_double(distance2), curr.first);
      if(nf->info() < space) {
        nf->info() = space;
        q.push(make_pair(space, nf));
      }
    }
  }
  
  for(auto [p, d] : users) {
    K::FT distance2 = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
    if(distance2 < d) {
      cout << "n";
      continue;
    }
      
    auto face = t.locate(p);
    if(d <= face->info()/4) cout << "y";
    else cout << "n";
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while(n) {
    solve(n);
    cin >> n;
  }
}