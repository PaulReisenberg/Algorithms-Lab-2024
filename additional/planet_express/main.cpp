#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <set>
#include <queue>
#include <map>
// Graph Definition
typedef boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::directedS,
    boost::no_property, 
    boost::property<boost::edge_weight_t, int>> weighted_graph;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<weighted_graph>::adjacency_iterator adjacency_it;
typedef boost::graph_traits<weighted_graph>::edge_iterator edge_it;

using namespace std;


vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);       // Get number of vertecies
  std::vector<int> dist_map(n);         // int (vertex_desc) -> int (distance)

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;                   // Returns distance from s to t
}


void solve() {
  int n, m, k, T;
  cin >> n >> m >> k >> T;
  
  vector<int> id_to_tel(T);
  map<int, int> tel_to_id;
  for(int i = 0; i < T; i++) {
    int tel; cin >> tel;
    id_to_tel[i] = tel;
    tel_to_id[tel] = i;
  }
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i = 0; i < m; i++) {
     int u, v, c; cin >> u >> v >> c;
     // cout << "(" << u << "," << v << ")" << endl;
     e = boost::add_edge(u, v, G).first; weights[e]=c;
  }
  
  
  // Compute the links
  vector<set<int>> id_to_links(T);
  vector<int> visited(T, false);
  vector<int> link_cost(T);
  
  for(int i = 0; i < T; i++) {
    queue<int> q; q.push(id_to_tel[i]);
    vector<int> vis(n, false);
    set<int> links;
    
    while(!q.empty()) {
      int c_v = q.front(); q.pop();
      if(vis[c_v]) continue;
      vis[c_v] = true;
      
      if(tel_to_id.find(c_v) != tel_to_id.end()) {   // Tel node
        int c_id = tel_to_id[c_v];
        if(visited[c_id]) {
          links.insert(id_to_links[c_id].begin(), id_to_links[c_id].end());
          continue;
        } else {
          links.insert(c_id);
        }
      }
      
      adjacency_it ai_beg, ai_end;
      for (boost::tie(ai_beg, ai_end) = boost::adjacent_vertices(c_v, G); ai_beg != ai_end; ++ai_beg) {
          
          q.push(*ai_beg);
      }
    }
    visited[i] = true;
    id_to_links[i] = links;
    link_cost[i] = links.size() - 1;
  }
  
  
  // Create new Graph with reversed edges
  weighted_graph G_2(n);
  weight_map weights_2 = boost::get(boost::edge_weight, G_2);
  edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
      int src = boost::source(*e_beg, G);
      int trgt = boost::target(*e_beg, G);
      e = boost::add_edge(trgt, src, G_2).first; weights_2[e]=weights[*e_beg];
  }

  // Add new edges (previously computed links)
  for(int i = 0; i < T; i++) {
    for(auto it = id_to_links[i].begin(); it != id_to_links[i].end(); it++) {
      int from = id_to_tel[i];
      int to = id_to_tel[*it];
      if(from != to) {
        e = boost::add_edge(from, to, G_2).first; weights[e]=link_cost[i];
      }
    }
  }
  
  // Dijkstra, find closest warehouse
  vector<int> dist_map = dijkstra_dist(G_2, n-1);
  int min_dist = dist_map[0];
  for(int i = 1; i < k; i++)
    min_dist = min(min_dist, dist_map[i]);
  
  if(min_dist <= 1000000)
    cout << min_dist << endl;
  else
    cout << "no" << endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}