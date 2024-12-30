#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <vector>

using namespace boost;

typedef adjacency_list<listS, vecS, undirectedS, no_property,
        property< edge_weight_t, int >> graph_t;

typedef graph_traits< graph_t >::vertex_descriptor vertex_descriptor;

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  int n, m, k, x, y;
  for(int i = 0; i < t; i++) {
      std::cin >> n >> m >> k >> x >> y;
      
      
      graph_t g(n*(1 + k));
      int a,b,c,d;
      for(int j = 0; j < m; j++) {
        std::cin >> a >> b >> c >> d;
        
        if(d == 0)
          for(int i = 0;i <= k; i++)
            boost::add_edge(a+(i*n), b+(i*n), c, g);
        else
          for(int i = 0;i < k; i++) {
            boost::add_edge(a+(i*n), b +     i*n, c, g);
            boost::add_edge(a+(i*n), b + (i+1)*n, c, g);
            boost::add_edge(b+(i*n), a + (i+1)*n, c, g);
          }
            
      }
      
    
    std::vector< vertex_descriptor > p(num_vertices(g));
    std::vector< int > distance(num_vertices(g));
    
    dijkstra_shortest_paths(g, x,
        predecessor_map(make_iterator_property_map(
                            p.begin(), get(boost::vertex_index, g)))
            .distance_map(boost::make_iterator_property_map(
                distance.begin(), get(boost::vertex_index, g))));
      

    std::cout << distance[y + k * n] << std::endl;
  }
}