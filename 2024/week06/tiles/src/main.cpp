#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
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
         // cout << "adding edge: (" << from << ", "<< to << ")" << endl; 
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




int main() {
  
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  
  for(int l = 0; l < t; l++) {
    
    int x, y; cin >> x >> y;
    
    int n = x*y+2;
    graph G(n);
    edge_adder adder(G);
    char v;
    
    int node = 1;
    int squares = 0;

    for(int j = 0; j < y; j++) {
      for(int i = 0; i < x; i++) {
      
        cin >> v;
        if(v == '.') {
          squares++;
          if((i+j) % 2 == 0) {
            adder.add_edge(0, node, 1);  // add edge from source
            if(i>0) adder.add_edge(node, node-1, 1);
            if(i<x-1) adder.add_edge(node, node+1, 1);
            if(j>0) adder.add_edge(node, node-x, 1);
            if(j<y-1) adder.add_edge(node, node+x, 1);
          } else {
              adder.add_edge(node, n-1, 1);  // add edge to sink
          }
        }
        node++;
      } 
    }
    if(squares % 2 != 0) {
      cout << "no" << endl;
    } else {
      long flow = boost::push_relabel_max_flow(G, 0, n-1);

      if (flow == squares/2) cout << "yes" << endl;
      else cout << "no" << endl;
    }
    
  }
  
  
  
  
  
  return 0;
}