#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;


typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef Triangulation::Face_iterator Face_iterator;           // Finite faces iterator
typedef Triangulation::All_faces_iterator All_faces_iterator; // All faces iterator
typedef Triangulation::Face_handle Face_handle;              // Handle to face
typedef Triangulation::Face Face;                            // Actual face type

typedef K::Point_2 P;

using namespace std;

long floor_to_long(K::FT val) {
  long l = (long) CGAL::to_double(val);
  while(K::FT(l) > val) l--;
  while(K::FT(l+1) < val) l++;
  return l;
}

//long get_takeoff(K::FT d_2, long r) {
//  K::FT s = (d_2 - 4*r*r - 4*r*s)/4;
//}

void solve() {
  int n, m;cin >> n >> m;
  long r; cin >> r;
  
  vector<P> trees(n);
  for(int i = 0; i < n; i++) {
    long x, y; cin >> x >> y;
    trees[i] = P(x,y);
  }
  
  vector<P> balloons(m);
  vector<long> size(m);
  long max_s = 0;
  for(int i = 0; i < m; i++) {
    long x, y, s; cin >> x >> y >> s;
    balloons[i] = P(x,y);
    size[i] = s;
    max_s = max(max_s, s);
  }
  
  Triangulation t(trees.begin(), trees.end());
  
  // 1. determine max s for takeoff for each triangle
  vector<K::FT> clearance;
  int id = 0;
  for(auto f = t.all_faces_begin(); f != t.all_faces_end(); f++) {
    if(t.is_infinite(f)) {
      f->info() = id++;
      clearance.push_back(CGAL::square(2*(max_s+r)));
    } else {
      P center = t.dual(f);
      P closest = t.nearest_vertex(center)->point();
      clearance.push_back(CGAL::squared_distance(center, closest));
      f->info() = id++;
    }
  }
  // print_takeoff(takeoff);
  
  
  
  // 2. Start BFS from all triangles with and update max takeoff clearance possible
  vector<bool> updated(id, false);     // if face was updated it has nothing to offer anymore
  for(auto f = t.finite_faces_begin(); f != t.finite_faces_end(); f++) {
    
    if(updated[f->info()]) continue;
    
    queue<Face_handle> q; q.push(f);
    while(!q.empty()) {
      auto curr = q.front(); q.pop();
      
      for(int i = 0; i < 3; i++) {
        auto edge = make_pair(curr, i);
        K::FT sq_edge_len = t.segment(edge).squared_length();
        int n = curr->neighbor(i)->info();
        if(clearance[curr->info()] > clearance[n] && sq_edge_len > clearance[n]) {
          clearance[n] = min(sq_edge_len, clearance[curr->info()]);
          updated[n] = true;
          q.push(curr->neighbor(i));
        }
      }
    }
  }
  
  for(int i = 0; i < m; i++) {
    P nearest = t.nearest_vertex(balloons[i])->point();
    
    K::FT move_dist = size[i] + r;
    if(CGAL::squared_distance(balloons[i], nearest) < CGAL::square(move_dist)) {
      cout << "n";
      continue;
    }
    
    if(clearance[t.locate(balloons[i])->info()] < CGAL::square(2*move_dist)) {
      cout << "n";
      continue;
    }
    cout << "y";
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  t = 5;
  while(t--) solve();
  return 0;
}