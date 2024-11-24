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
  
  int n, m; cin >> n; cin >> m;
  graph G(n + 2);
  edge_adder adder(G);
  
  int source = n;
  int sink = n+1;
  int max_cost = 200;
  
  vector<int> limits(n-1);
  for(int i = 0; i < n-1; i++) {
    int c; cin >> c;
    limits[i] = c;
    adder.add_edge(source, i, c, 0);
    adder.add_edge(i+1, sink, c, 0);
    adder.add_edge(i, i+1, c, max_cost);
    
  }
  
  vector<vector<vector<int>>> foods(n, vector<vector<int>>(n, vector<int>()));
  for(int i = 0; i < m; i++) {
    int a, b, d; cin >> a; cin >> b; cin >> d;
    foods[a][b].push_back(d);
  }
  
  vector<int> products(n, 0);
  int total_food = 0;
  for(int i = 0; i < n-1; i++) {
    int min_cap = INT32_MAX;
    for(int j = i+1; j < n; j++) {
      min_cap = min(min_cap, limits[j-1]);
      int num_foods = foods[i][j].size();
      
      if(min_cap < num_foods) {
        sort(foods[i][j].begin(), foods[i][j].end(), [] (int f1, int f2) { return f1 > f2;});
        num_foods = min_cap;
      }
      
      for(int k = 0; k < num_foods; k++) {
        adder.add_edge(i, j, 1, (j - i) * max_cost - foods[i][j][k]);
      }
    }
  }
  
  int flow = boost::push_relabel_max_flow(G, source, sink);
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  int cost = boost::find_flow_cost(G);
  
  cout << flow * max_cost - cost << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) solve();
  return 0;
}