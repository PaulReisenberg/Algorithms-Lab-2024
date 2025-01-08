#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <unordered_map>
#include <limits>
#include <set>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 P;
typedef Delaunay::Vertex_handle VH;

using namespace std;

typedef K::Point_2 P;

typedef std::pair<P,int> IP;
int n, h;
long s;

int encode(int u, int v) {
  if(u < v)
    return u * n + v;
  else
    return v * n + u;
}


void solve() {
  cin >> n >> s >> h;
  
  K::FT inf = std::numeric_limits<double>::max(); 
  
  vector<IP> trees(n);
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    trees[i] = {P(x,y), i};
  }
  
  Delaunay t(trees.begin(), trees.end());
  
  int a_2 = 0;
  int a_3 = 0;
  int a_s = 0;
  int a_max = 0;
  
  // Calculating a_2
  K::FT sq_d_2 = inf;
  for (auto e=t.finite_edges_begin(); e!=t.finite_edges_end(); ++e){
    
    auto v1=e->first->vertex((e->second+1)%3);
    auto v2=e->first->vertex((e->second+2)%3);
    K::FT sq_len = CGAL::squared_distance(v1->point(), v2->point());
    if(sq_len < sq_d_2) {
      sq_d_2 = sq_len;
      a_2 = 1;
    } else if(sq_len == sq_d_2) {
      a_2++;
    }
  }
  
  
  // Calculating a_3
  K::FT sq_d_3 = inf;
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); f++){
    if (t.is_infinite(f)) continue;
    
    P center = t.dual(f);
    K::FT sq_len = CGAL::squared_distance(center, f->vertex(1)->point());
    if(sq_len < sq_d_3) {
      sq_d_3 = sq_len;
      a_3 = 1;
    } else if(sq_len == sq_d_3) {
      a_3++;
    }
  }
  
  // Calculating a_s
  map<int, K::FT> d_min;
  map<int, K::FT> d_max;
  for(auto f = t.all_faces_begin(); f != t.all_faces_end(); f++) {
    
    if(t.is_infinite(f)) {
      // As explaind, we know that d_max is infite of the edge at the edge of the triangulation
      
      for(int i = 0; i < 3; i++) {
        if(t.is_infinite(f->vertex(i))) {
          int id_1 = f->vertex((i+1)%3)->info();
          int id_2 = f->vertex((i+2)%3)->info();
          d_max[encode(id_1, id_2)] = inf;
        }
      }
    } else {
      for(int i = 0; i < 3; i++) {
        auto v1 = f->vertex((i+1)%3);
        auto v2 = f->vertex((i+2)%3);
        int edge_id = encode(v1->info(), v2->info());
        
        P center = t.dual(f);
        K::FT dist_center = CGAL::squared_distance(v1->point(), center);

        
        if(d_min.find(edge_id) == d_min.end() || dist_center < d_min[edge_id]) d_min[edge_id] = dist_center;
        if(d_max.find(edge_id) == d_max.end() || dist_center > d_max[edge_id]) d_max[edge_id] = dist_center;

        // As explained check if we are in state (1) or (2)
        P mid = CGAL::midpoint(v1->point(), v2->point());
        P closest = t.nearest_vertex(mid)->point();
        if(closest == v1->point() || closest == v2->point())
          d_min[edge_id] = CGAL::squared_distance(mid, v1->point());
        
      }
    }
  }
  
  K::FT s_exact(s); 
  for(auto it = d_min.begin(); it != d_min.end(); it++) {
    auto edge = it->first;
    if(s_exact >= d_min[edge] && s_exact <= d_max[edge])
      a_s ++;
  }
  
  
  // Calculate a_max
  map<K::FT, int> enter_count;
  map<K::FT, int> leave_count;
  set<K::FT> unique_bounds;
  
  for (const auto& entry : d_min) {
      auto edge = entry.first;
      K::FT min_val = d_min[edge];
      K::FT max_val = d_max[edge];
  
      enter_count[min_val]++;
      leave_count[max_val]++;
  
      unique_bounds.insert(min_val);
      unique_bounds.insert(max_val);
  }
  
  int current_active = 0;
  for (const auto& bound : unique_bounds) {
      current_active += enter_count[bound];
      a_max = max(a_max, current_active);
      current_active -= leave_count[bound];
  }

  
  
  cout << a_2 << " " << a_3 << " " << a_s << " " << a_max << endl;


}



int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  return 0;
}