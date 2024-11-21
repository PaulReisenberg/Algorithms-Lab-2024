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
  }
};


void solve() {
  
  int N, M, S; cin >> N; cin >> M; cin >> S;
  
  graph G(S + M + N + 2);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  int source = S + M + N;
  int sink = S + M + N + 1;
  int s_offset = 0;
  int m_offset = S;
  int n_offset = S + M;
  int max_cost = 999999999;
  
  for(int i = 0; i < S; i++) {
    int limit; cin >> limit;
    adder.add_edge(s_offset+i, sink, limit, 0);
  }
  
  for(int i = 0; i < M; i++) {
    int state; cin >> state;
    adder.add_edge(m_offset+i, s_offset+state-1, 1, 0);
  }
  
  for(int i = 0; i < N; i++) {
    adder.add_edge(source, n_offset+i, 1, 0);
    
    // Connect each person to each state
    for(int j = 0; j < S; j++)
      adder.add_edge(n_offset+i, s_offset+j, 1, max_cost);
    
    // Connect each person to each property
    for(int j = 0; j < M; j++) {
      int bid; cin >> bid;
      adder.add_edge(n_offset+i, m_offset+j, 1, max_cost-bid);
    }
  }

  int flow = boost::push_relabel_max_flow(G, source, sink);
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  int cost = boost::find_flow_cost(G);
    
  int total = 0;
  for(int i = 0; i < S; i++) {
    for(int j = 0; j < M; j++) {
      auto edge_pair = boost::edge(s_offset+i, m_offset+j, G);
      if(!edge_pair.second) continue;
      total += rc_map[edge_pair.first];
    }
  }
  cout << total << " " << max_cost * flow - cost << endl;
}




int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) solve();
  return 0;
}