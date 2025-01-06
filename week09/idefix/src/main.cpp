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


P load_p() {
  int x, y; cin >> x; cin >> y;
  return P(x,y);
}

enum Type { BONE, EDGE };

struct Event {
  long at;      // 4*d^2 when this event is triggerd
  Type type;    // Either a new oak or new bone can be reached
  int from;
  int to;
};

vector<int> vertex_to_comp;  // vertex -> component
vector<vector<int>> comp_to_vertex;  // component -> vertex
vector<int> bones; // component -> bones

int merge_comps(int comp1, int comp2) {
  
  int min_comp = min(comp1, comp2);
  int max_comp = max(comp1, comp2);
  
  for(int v : comp_to_vertex[max_comp])
    vertex_to_comp[v] = min_comp;
  
  comp_to_vertex[min_comp].insert(
    comp_to_vertex[min_comp].end(),
    comp_to_vertex[max_comp].begin(),
    comp_to_vertex[max_comp].end());
  
  comp_to_vertex[max_comp] = {};
  bones[min_comp] += bones[max_comp];
  return min_comp;
}

void solve() {
  long n, m, s, k;
  cin >> n; cin >> m; cin >> s; cin >> k;
  vector<pair<P,int>> oaks(n);
  
  for(int i = 0; i < n; i++) {
    oaks[i] = make_pair(load_p(),i);
  }
  
  Triangulation t(oaks.begin(), oaks.end());
  vector<Event> events(m);
  for(int i = 0; i < m; i++) {
    P bone = load_p();
    auto v = t.nearest_vertex(bone);
    long r_2 = CGAL::squared_distance(v->point(), bone);
    events[i] = {4*r_2, BONE, i, v->info()};
  }
  
  int index = m;
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    auto from = e->first->vertex((e->second + 1) % 3);
    auto to = e->first->vertex((e->second + 2) % 3);
    long d_2 = CGAL::squared_distance(from->point(), to->point());
    events.push_back({d_2, EDGE, from->info(), to->info()});
  }
  
  sort(events.begin(), events.end(), [](Event a, Event b) {
    return a.at < b.at;
  });
  
  // Kruskal Algorithm
  vertex_to_comp = vector<int>(n);  // vertex -> component
  comp_to_vertex = vector<vector<int>>(n, {0});  // vertex -> component
  bones = vector<int>(n, 0);      // component -> num bones
  for(int i = 0; i < n; i++) {
    vertex_to_comp[i] = i; 
    comp_to_vertex[i] = {i};
  }

  int current_bones = 0;
  int a = 0;
  long q = -1;
  for(Event e : events) {
    if(e.type == BONE) {
      bones[vertex_to_comp[e.to]]++;
      current_bones = max(current_bones, bones[vertex_to_comp[e.to]]);
    } else {
      int comp1 = vertex_to_comp[e.from];
      int comp2 = vertex_to_comp[e.to];
      if(comp1 == comp2) continue;
      
      int min_comp = merge_comps(comp1, comp2);
      current_bones = max(current_bones, bones[min_comp]);
    }
    
    if(e.at <= s) a = current_bones;
    if(current_bones >= k && q == -1) q = e.at;
  }
  
  cout << a << " " << q << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  //solve();
  while(t--) solve();
  return 0;
}