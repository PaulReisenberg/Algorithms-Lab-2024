#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

typedef boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::undirectedS,
        boost::no_property,
        boost::property<boost::edge_weight_t, int>
        > Graph;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap;


class CustomWeightMap {
    map<Edge, int>& m_map;
public:
    typedef Edge key_type;
    typedef int value_type;
    typedef int reference;
    typedef boost::readable_property_map_tag category;

    CustomWeightMap(map<Edge, int>& map) : m_map(map) {}

    friend int get(const CustomWeightMap& cwm, Edge e) {
        return cwm.m_map.at(e);
    }
};

void algorithm( int n, int e, int s, int a, int b, 
                Graph& g, vector<map<Edge, int>>& weight_maps) {
  
  WeightMap total_w_map = boost::get(boost::edge_weight, g);
  
  for(map<Edge, int> w_map : weight_maps) {
    std::vector<Edge> spanning_tree;
    boost::kruskal_minimum_spanning_tree(
      g, 
      back_inserter(spanning_tree),
      boost::weight_map(CustomWeightMap(w_map)));
      
    for(Edge e: spanning_tree) {
      total_w_map[e] = min(total_w_map[e], w_map[e]);
    }
      
  }
  
  vector<int> d(n);
  boost::dijkstra_shortest_paths(
    g,
    a,
    boost::distance_map(boost::make_iterator_property_map(
      d.begin(), boost::get(boost::vertex_index, g)))
    .weight_map(total_w_map)
  );
    
  cout << d[b] << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
    Graph g(n);
    int u, v, w;
    vector<map<Edge, int>> weight_maps(s);
    
    for (int j = 0; j < e; j++) {
      cin >> u >> v;
      Edge edge = boost::add_edge(u, v, 999999, g).first;
      for(int k = 0; k < s; k++) {
        cin >> w;
        weight_maps[k][edge] = w;
      }
    }
    for(int j = 0; j < s; j++) cin >> w;
    
    algorithm(n, e, s, a, b, g, weight_maps);
  }
  
  return 0;
}