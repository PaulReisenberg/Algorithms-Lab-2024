#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace std;

// Defining the graph data structure: https://www.boost.org/doc/libs/1_86_0/libs/graph/doc/adjacency_list.html
typedef boost::adjacency_list<
                  boost::vecS,                                // Using vector to store outgoing edges of each vertecie
                  boost::vecS,                                // Using vector to store the vertecies
                  boost::undirectedS,                         // Using undirected graph
                  boost::no_property,                         // vertex properties: None
                  boost::property<boost::edge_name_t, int>    // edge properties: use a "random" property to get a property map later 
                  > Graph;

// Define a property map for the biconnected_components function
// https://www.boost.org/doc/libs/1_86_0/libs/graph/doc/biconnected_components.html
typedef boost::property_map<Graph, boost::edge_name_t>::type ComponentMap;

void algorithm(int n, int m, Graph& g) {
  
  // call biconnected_components with "repurposed" property map
  ComponentMap componentmap = boost::get(boost::edge_name, g);
  size_t num_comps = boost::biconnected_components(g, componentmap);
  
  
  typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;
  typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
  typedef boost::graph_traits<Graph>::edge_descriptor Edge;
  
  vector<int> componentsize(num_comps);
  EdgeIt ebeg, eend;
  for (tie(ebeg, eend) = boost::edges(g); ebeg != eend; ++ebeg) {
        componentsize[componentmap[*ebeg]]++;
  }
  
  vector<std::pair<int,int> > bridges;
  for(boost::tie(ebeg, eend) = boost::edges(g); ebeg != eend; ++ebeg) {
    if (componentsize[componentmap[*ebeg]] == 1) { 
      int u = source(*ebeg, g);
      int v = target(*ebeg, g); 
      bridges.push_back(make_pair(min(u,v), max(u,v)));
    }
  }
  
  sort(bridges.begin(), bridges.end());
  cout << bridges.size() << endl;
  for(size_t i = 0; i < bridges.size(); i++) {
    cout << bridges[i].first << " " << bridges[i].second << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    int n, m; cin >> n >> m;
    
    Graph g(n);
    int u, v;
    
    for (int j = 0; j < m; j++) {
      cin >> u >> v;
      boost::add_edge(u, v, g);
    }
    
    algorithm(n, m, g);
  }
  
  return 0;
}