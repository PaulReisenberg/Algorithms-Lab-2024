
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

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
// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
    //cout << "(" << from  << ", " << to << ") -> " << capacity << ", " << cost << endl; 
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
  
  int n, m, s, f;
  cin >> n >> m >> s >> f;
  
  graph G(n + 2);
  int source = n;
  int sink = n+1;
  edge_adder adder(G);
  
  int out_source = 0;
  for(int i = 0; i < m; i++) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    adder.add_edge(a, b, c, d);
    adder.add_edge(b, a, c, d);
    
    if(a == s || b == s)
      out_source += c;
  }
  auto source_e = adder.add_edge(source, s, 1, 0);
  adder.add_edge(f, sink, out_source, 0);
  
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  int sp = boost::find_flow_cost(G);
  
  
  int left = 1;
  int right = out_source;
  
  
  while(left < right) {
    int mid = (left + right)/2 + 1;
    
    G.remove_edge(source_e);
    source_e = adder.add_edge(source, s, mid, 0);
    
    boost::successive_shortest_path_nonnegative_weights(G, source, sink);
    int cost = boost::find_flow_cost(G);
  
    if(cost == sp * mid) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  cout << left << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}