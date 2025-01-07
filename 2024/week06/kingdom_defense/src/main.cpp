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
  
  int tc; cin >> tc;
  
  for(int counter = 0; counter < tc; counter++) {
    int l, p; cin >> l >> p;
    
    int total_v = l+2;
    graph G(total_v);
    edge_adder adder(G);
    
    
    int source = total_v-1;
    int sink = total_v-2;
    int needed_flow = 0;
    
    vector<int> supply(l,0);
    vector<int> demand(l,0);
    for(int i = 0; i < l; i++) {
      cin >> supply[i];
      cin >> demand[i];
    }
    
    int node = l;
    int f, t, min_c, max_c;
    for(int i = 0; i < p; i++) {
      cin >> f >> t >> min_c >> max_c;
      demand[f] += min_c;
      supply[t] += min_c;
      adder.add_edge(f, t, max_c - min_c);
    }
    
    for(int i = 0; i < l; i++) {
      if(supply[i] > demand[i]) {
        adder.add_edge(source, i, supply[i] - demand[i]);
      } else if (demand[i] > supply[i]) {
        adder.add_edge(i, sink, demand[i] - supply[i]);
        needed_flow += demand[i] - supply[i];
      }
    }
    
    int flow = boost::push_relabel_max_flow(G, source, sink);
    if(flow == needed_flow) cout << "yes" << endl;
    else cout << "no" << endl;
  }
  
  
  return 0;
}