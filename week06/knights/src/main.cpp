#include <iostream>
#include <string>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
       graph &G;
      public:
       explicit edge_adder(graph &G) : G(G) {}
       void add_edge(int from, int to, long capacity) {
         // cout << "adding edge: (" << from << ", "<< to << ", " << capacity << ")" << endl; 
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

using namespace std;



int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  
  for(int tc = 0; tc < t; tc++) {
    int m, n, k, c; cin >> m >> n >> k >> c;
    
    graph G((2*n*m)+2);
    edge_adder adder(G);
    
    int in_ver = 0;
    int out_ver = n*m;
    
    int source = 2*(n*m);
    int sink = 2*(n*m)+1;
    int node = 0;
    
    for(int y = 0; y < n; y++) {
      for(int x = 0; x < m; x++) {
        int num_exits = 0;
        // simulate vertex capacity
        adder.add_edge(in_ver+node, out_ver+node, c);
        
        // add edges to connected intersections
        if(x>0)   adder.add_edge(out_ver+node, in_ver+node-1, 1);
        else num_exits++;
        if(x<m-1) adder.add_edge(out_ver+node, in_ver+node+1, 1);
        else num_exits++;
        if(y>0)   adder.add_edge(out_ver+node, in_ver+node-m, 1);
        else num_exits++;
        if(y<n-1) adder.add_edge(out_ver+node, in_ver+node+m, 1);
        else num_exits++;
        
        // add edges to sink
        if(x==0 || x==m-1)      adder.add_edge(out_ver+node, sink, num_exits);
        else if(y==0 || y==n-1) adder.add_edge(out_ver+node, sink, num_exits);
        
        node++;
      }
    }
    
    // cout << "adding kinghts" << endl;
    for(int i = 0; i < k; i++) {
      int x, y; cin >> x >> y;
      int k_node = m*y + x;
      // cout << "k_node: " << "(" << x << "," << y << ")" << "(" << source << ", " << in_ver +k_node << ")" << endl;
      adder.add_edge(source, in_ver + k_node, 1);
    }
    
    cout << boost::push_relabel_max_flow(G, source, sink) << endl;
    
  }
  
  
  return 0;
}