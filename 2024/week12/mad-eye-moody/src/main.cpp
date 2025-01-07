#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <algorithm>
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

using namespace std;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
    // cout << "(" << from << ", " << to << "), cap: " << capacity << ", cost: " << cost << endl;
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
    return e;
  }
};

void solve() {
  int n, m, s, p;
  cin >> n >> m >> s >> p;
  graph G(n+1);
  int source = n;
  int sink = p;
  edge_adder adder(G);
  
  auto c_map = boost::get(boost::edge_capacity, G);
  edge_desc to_source = adder.add_edge(source, s, 1, 0);
  
  for(int i = 0; i < m; i++) {
    int u, v, c, d;
    cin >> u >> v >> c >> d;
    
    adder.add_edge(u, v, c, d);
    adder.add_edge(v, u, c, d);
  }

  int flow = boost::push_relabel_max_flow(G, source, sink);
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  int shortes_path = boost::find_flow_cost(G);
  
  long lower = 1;
  long upper;
  
  // find upper
  while(true) {
    upper = lower * 2;
    c_map[to_source] = upper;
    
    flow = boost::push_relabel_max_flow(G, source, sink);
    if (flow < upper) break;
    boost::successive_shortest_path_nonnegative_weights(G, source, sink);
    long cost = boost::find_flow_cost(G);
    

    
    if (upper * shortes_path != cost) break;
    lower = upper;
    
    
  }
  
  // binary search
  while(lower < upper - 1) {
    long size = (upper + lower) / 2;
    c_map[to_source] = size;
    
    flow = boost::push_relabel_max_flow(G, source, sink);
    if (flow < size) {
      upper = size;
      //cout << upper << " not possible 1" << endl;
    } else {
      boost::successive_shortest_path_nonnegative_weights(G, source, sink);
      long cost = boost::find_flow_cost(G);
      
      if(size * shortes_path == cost) {
        lower = size;
      } else {
        upper = size;
        //cout << upper << " not possible 2"  << endl;
      }
    }
  }
  cout << lower << endl;
}





int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  return 0;
}