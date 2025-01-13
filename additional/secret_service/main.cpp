// STL includes
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <algorithm>
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

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};




vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);       // Get number of vertecies
  std::vector<int> dist_map(n);         // int (vertex_desc) -> int (distance)

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;                   // Returns distance from s to t
}

int n, m, a, s, c, d;

bool is_possible(
  vector<vector<int>>& dist_map,
  vector<int>& agents,
  vector<int>& shelters,
  int warning_time) {
 
  graph G(a + s*c + 2);
  int source = a+s*c;
  int sink = a+s*c+1;
  
  edge_adder adder(G);
  for(int i = 0; i < a; i++) adder.add_edge(source, i, 1);
  
  for(int i = 0; i < s; i++) {
    for(int j = 0; j < c; j++) {
      adder.add_edge(a + j*s + i, sink, 1);
    }
  }
  
  for(int i = 0; i < a; i++) {
    for(int j = 0; j < s; j++) {
      for(int t = 0; t < c; t++) {
        if(dist_map[i][j] <= warning_time - d*(t+1)) {
          adder.add_edge(i, a + t*s + j, 1);
        }
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, source, sink);

  return flow == a;
}

bool is_possible2(
  vector<vector<int>>& dist_map,
  vector<int>& agents,
  vector<int>& shelters,
  int warning_time) {
 
  graph G(a + s*c + 2);
  int source = a+s*c;
  int sink = a+s*c+1;
  
  edge_adder adder(G);
  for(int i = 0; i < a; i++) adder.add_edge(source, i, 1);
  
  for(int i = 0; i < s; i++) {
    for(int j = 0; j < c; j++) {
      adder.add_edge(a + j*s + i, sink, 1);
    }
  }
  
  for(int i = 0; i < a; i++) {
    for(int j = 0; j < s; j++) {
      for(int t = 0; t < c; t++) {
        if(dist_map[i][j] <= warning_time - d*(t+1)) {
          adder.add_edge(i, a + c*s + j, 1);
        }
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, source, sink);

  return flow == a;
}


void solve() {
  cin >> n >> m >> a >> s >> c >> d;
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);       // Gets the property map

  edge_desc e;
  for(int i = 0; i < m; i++) {
    char w; cin >> w;
    int x, y, z; cin >> x >> y >> z;
    e = boost::add_edge(x, y, G).first; weights[e]=z;
    if(w == 'L') {
      e = boost::add_edge(y, x, G).first;
      weights[e]=z;
    }
  }
  
  vector<int> agents(a);
  for(int i = 0; i < a; i++)
    cin >> agents[i];
  
  vector<int> shelters(s);
  for(int i = 0; i < s; i++)
    cin >> shelters[i];
    
  
  vector<vector<int>> dist_map(a, vector<int>(s));
  int max_dist = 0;
  for(int i = 0; i < a; i++) {
    vector<int> agent_dist_map = dijkstra_dist(G, agents[i]);
    
    for(int j = 0; j < s; j++) {
      dist_map[i][j] = agent_dist_map[shelters[j]];
    
      if(dist_map[i][j] != 2147483647)
        max_dist = max(max_dist, dist_map[i][j]);
    }
  }
  
  int left = 0;
  int right = max_dist + c * d;
  
  
  while(left < right) {
    int mid = (left + right)/2;
    
    if(is_possible(dist_map, agents, shelters, mid))
      right = mid;
    else
      left = mid+1;
  }
  cout << right << endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}