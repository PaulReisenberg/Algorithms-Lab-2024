#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <algorithm>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

struct Info {
  int comp;
  int color;
};

typedef CGAL::Triangulation_vertex_base_with_info_2<Info, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;

bool check_distance(P p1, P p2, double d_2) {
  return CGAL::squared_distance(p1, p2) <= d_2;
}


bool is_bipartite(Triangulation& t, int n, double squared_radius) {
  
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) {
    v->info() = Info({-1,-1});   // component, color
  }
  
  int component = 0;
  vector<P> color_0;
  vector<P> color_1;
  queue<Triangulation::Vertex_handle> q;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) {
    if(v->info().color != -1) continue;
    
    v->info().comp = component++;
    v->info().color = 0;
    color_0.push_back(v->point());
    q.push(v);
    while(q.size() > 0) {
      auto curr = q.front();
      q.pop();
      
      Triangulation::Vertex_circulator c = t.incident_vertices(curr);
      
      do {
        if (!t.is_infinite(c) && check_distance(curr->point(), c->point(),squared_radius)){
          
          
          if (c->info().color == curr->info().color) {
            return false;
          } else if(c->info().color == -1) {
            int color = (curr->info().color + 1) % 2;
            if(color == 0) color_0.push_back(c->point());
            if(color == 1) color_1.push_back(c->point());
            
            c->info().color = color;
            c->info().comp = curr->info().comp;
            
            q.push(c);
          }
        }
      } while (++c != t.incident_vertices(curr));
    }
  }
  
  Triangulation t0(color_0.begin(), color_0.end());
  for (auto e = t0.finite_edges_begin(); e != t0.finite_edges_end(); ++e) {
    if (t0.segment(*e).squared_length() <= squared_radius) {
      return false;
    }
  }
  
  Triangulation t1(color_1.begin(), color_1.end());
  for (auto e = t1.finite_edges_begin(); e != t1.finite_edges_end(); ++e) {
    if (t1.segment(*e).squared_length() <= squared_radius) {
      return false;
    }
  }
  
  return true;
}




void solve() {
  
  // READING INPUT START
  int n, m, r; cin >> n >> m >> r;
  vector<P> stations;
  for(int i = 0; i < n; i++) {
    int x,y; cin >> x >> y;
    stations.push_back(P(x,y));
  }
    
  vector<pair<P,P>> clues;
  for(int i = 0; i < m; i++) {
    int ax,ay,bx,by; cin >> ax >> ay >> bx >> by;
    clues.push_back(make_pair(P(ax,ay), P(bx,by)));
  }
  // READING INPUT END
  
  
  Triangulation t(stations.begin(), stations.end());
  double r_2 = r;
  r_2 = r_2 * r_2;
  if(!is_bipartite(t, n, r_2)) {
    cout << std::string(m, 'n') << endl;
    return;
  }
  
  for(int i = 0; i < m; i++) {
    const P from = clues[i].first;
    const P to = clues[i].second;
    
    if(check_distance(from, to, r_2)) {
      cout << "y";
      continue;
    }
    
    Vertex_handle t1 = t.nearest_vertex(from);
    Vertex_handle t2 = t.nearest_vertex(to);
    
    if(!check_distance(from, t1->point(), r_2) || !check_distance(to, t2->point(), r_2)) {
      cout << "n";
      continue;
    }
    
    if(t1->info().comp == t2->info().comp) {
      cout << "y";
    } else {
      cout << "n";
    }
  }
  cout << endl;
  return;
  
  
}



int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  return 0;
}