#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

// Define the graph type with edge weights
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, 
                              boost::no_property, 
                              boost::property<boost::edge_weight_t, int>> weighted_graph;


typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

void algorithm(int n, const weighted_graph& G) {
  vector<vertex_desc> predecessors(n);
  vector<int> distances(n);
  std::vector<edge_desc> mst;
  
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  auto weight_map = boost::get(boost::edge_weight, G);
  
  int mst_weight = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) { 
    mst_weight += weight_map[*it];
  }

  boost::dijkstra_shortest_paths(G, 0, // Start from vertex 0
        boost::predecessor_map(boost::make_iterator_property_map(predecessors.begin(), get(boost::vertex_index, G)))
        .distance_map(boost::make_iterator_property_map(distances.begin(), get(boost::vertex_index, G))));
        

  int max_distance = 0;
  
  for (int i = 0; i < n; ++i)
    if (distances[i] > max_distance) 
      max_distance = distances[i];
  
  cout << mst_weight << " " << max_distance << endl;
}




int main() {
  
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    
    int n, m; cin >> n >> m;
    
    weighted_graph G(n);
    int u;
    int v;
    int w;
    
    for (int i = 0; i < m; i++) {
      cin >> u >> v >> w;
      boost::add_edge(u, v, w,  G);
    }
    
    algorithm(n, G);
  }
  
  return 0;
}