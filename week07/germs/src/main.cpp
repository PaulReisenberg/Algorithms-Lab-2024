#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <algorithm>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;

using namespace std;

long ceil_to_long(double x) {
  int x_val = (long) x;
  while(x_val < x) x_val++;
  while(x_val-1 >= x) x_val--;
  return x_val;
}

void solve(int n) {
  long l, b, r, t; cin >> l >> b >> r >> t;
  
  vector<P> bacteria(n);
  vector<int> infos(n);
  
  vector<pair<P,int>> points_with_info(n);
  vector<double> time_to_col(n);
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    points_with_info[i] = {P(x,y), i};
    
    double dist = min(min(abs(x-l), abs(x-r)), min(abs(y-b), abs(y-t)));
    time_to_col[i] = sqrt(dist - 0.5);
  }
  
  Triangulation tri(points_with_info.begin(), points_with_info.end());

  for(auto e = tri.finite_edges_begin(); e != tri.finite_edges_end(); e++) {
    P p1 = e->first->vertex((e->second + 1)%3)->point();
    int i1 = e->first->vertex((e->second + 1)%3)->info();
    P p2 = e->first->vertex((e->second + 2)%3)->point();
    int i2 = e->first->vertex((e->second + 2)%3)->info();
    
    double dist = CGAL::to_double(CGAL::squared_distance(p1, p2));
    double time = sqrt((sqrt(dist) - 1)/ 2);
    
    time_to_col[i1] = min(time, time_to_col[i1]);
    time_to_col[i2] = min(time, time_to_col[i2]);
  }
  
  sort(time_to_col.begin(), time_to_col.end());
  
  cout << ceil_to_long(time_to_col[0]) << " " << ceil_to_long(time_to_col[n/2]) << " " << ceil_to_long(time_to_col[n-1]) << endl; 
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int n; cin >> n;
  while(n) {
    solve(n);
    cin >> n;
  }
  return 0;
}

