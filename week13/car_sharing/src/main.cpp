#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <unordered_map>
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

  int n, num_stations;
  cin >> n >> num_stations;
  
  int num_cars = 0;
  vector<int> stations(num_stations);
  for(int i = 0; i < num_stations; i++) {
    cin >> stations[i];
    num_cars += 1;
  }
  
  int max_time = 100000;
  int s, t, d, a, p;
  vector<vector<int>> to_idx(num_stations, vector<int>(max_time+1, -1));
  
  int idx = 0;
  int source = idx++;
  int sink = idx++;
  vector<tuple<int, int, int, int>> edges;
  for(int i = 0; i < n; i++) {
    cin >> s >> t >> d >> a >> p;
    s--;
    t--;
    
    if(to_idx[s][d] == -1)
      to_idx[s][d] = idx++;
    
    if(to_idx[t][a] == -1)
      to_idx[t][a] = idx++;
    
    edges.emplace_back(to_idx[s][d], to_idx[t][a], 1, 100*(a-d)-p);
  }
  
  vector<int> last(num_stations);
  for(int i = 0; i < num_stations; i++) {
    
    if(to_idx[i][0] == -1)
      to_idx[i][0] = idx++;
    last[i] = to_idx[i][0];
    
    edges.emplace_back(source, to_idx[i][0], stations[i], 0);
    
    
    if(to_idx[i][max_time] == -1)
      to_idx[i][max_time] = idx++;
      
    edges.emplace_back(to_idx[i][max_time], sink, 1000, 0);
    //adder.add_edge(to_idx[i][0], to_idx[i][max_time], stations[i], 0);
  }
  
  vector<int> last_time(num_stations, 0);
  for(int j = 0; j < num_stations; j++) {
    for(int i = 1; i <= max_time; i++) {
      if(to_idx[j][i] != -1) {
        edges.emplace_back(last[j], to_idx[j][i], 1000, 100*(i - last_time[j]));
        last[j] = to_idx[j][i];
        last_time[j] = i;
      }
    }
  }
  
  
  graph G(idx);
  edge_adder adder(G);
  for(auto [x1, x2, x3, x4] : edges) {
    adder.add_edge(x1, x2, x3, x4);
  }
  
  
  int flow = boost::push_relabel_max_flow(G, source, sink);
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  int cost = boost::find_flow_cost(G);
  int max_cost = 0;
  for(int stat : stations) max_cost += 100*max_time * stat;
  
  cout << max_cost - cost << endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) solve();
  return 0;
}