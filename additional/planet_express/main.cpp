#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
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
  
  vector<int> teles(T);
  map<int, int> tel_to_id;
  for(int i = 0; i < T; i++) {
    cin >> teles[i];
  }
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i = 0; i < m; i++) {
     int u, v, c; cin >> u >> v >> c;
     e = boost::add_edge(v, u, G).first; weights[e]=c;
  }
  
  std::vector<int> component_map(n);  // We MUST use such a vector as an Exterior Property Map: Vertex -> Component
  int nscc = boost::strong_components(G,
    boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G)));
  
  vector<int> comp_count(n, -1);
  for(int i = 0; i < T; i++) {
    comp_count[component_map[teles[i]]]++;
  }

  // Add new edges
  for(int tel : teles) {
    weights[boost::add_edge(tel, n + component_map[tel], G).first] = 0;
    weights[boost::add_edge(n + component_map[tel], tel, G).first] = comp_count[component_map[tel]];
  }
  
  // Dijkstra
  vector<int> dist_map = dijkstra_dist(G, n-1);
  
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