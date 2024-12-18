#include <iostream>
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

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    //cout << "(" << from << ", " << to << "), cap: " << capacity << ", cost: " << cost << endl;
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
  }
};


void solve() {
  int e, w, m, d, p, l;
  cin >> e >> w >> m >> d >> p >> l;
  //cout << "e: " << e << ", w: " << w << endl;
  graph G(2*e + 2*w + 4);
  edge_adder adder(G);
  int east_easy = 0;
  int east_hard = e;
  int west_easy = 2*e;
  int west_hard = 2*e + w;
  int int_in = 2*e + 2*w;
  int int_out= 2*e + 2*w + 1;
  int source = 2*e + 2*w + 2;
  int sink = 2*e + 2*w + 3;
  
  for(int i = 0; i < m; i++) {
    int u, v, r; cin >> u >> v >> r;
    adder.add_edge(east_easy+u, west_easy+v, 1, r);
  }
  
  for(int i = 0; i < d; i++) {
    int u, v, r; cin >> u >> v >> r;
    adder.add_edge(east_hard+u, west_hard+v, 1, r);
  }
  
  for(int i = 0; i < e; i++) {
    adder.add_edge(source, east_easy + i, l, 0);
    adder.add_edge(int_in, east_easy + i, p, 0);
    adder.add_edge(int_in, east_hard + i, p, 0);
  }
  if(p - e*l < 0) {
    cout << "No schedule!" << endl;
    return;
  }
  adder.add_edge(source, int_in, p - e*l, 0);
  
  
  for(int i = 0; i < w; i++) {
    adder.add_edge(west_easy + i, sink, l, 0);
    adder.add_edge(west_easy + i, int_out, p, 0);
    adder.add_edge(west_hard + i, int_out, p, 0);
  }
  if(p - w*l < 0) {
    cout << "No schedule!" << endl;
    return;
  }
  adder.add_edge(int_out, sink, p - w*l, 0);
    
  
  int flow = boost::push_relabel_max_flow(G, source, sink);
  //cout << "flow: " << flow << endl;
  if(flow < p) {
    cout << "No schedule!" << endl;
    return;
  }
    
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  int cost = boost::find_flow_cost(G);
  cout << cost << endl;
  //cout << "-------------" << endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  return 0;
}