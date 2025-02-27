#include <iostream>
#include <string>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <queue>
using namespace std;

typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;
// Interior Property Maps
typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

using namespace std;


void solve() {
  int n, m;
  cin >> n >> m;
  
  graph G(n + 2);
  edge_adder adder(G);
  int source = n;
  int sink = n + 1;
  int sum_b = 0;
  
  for (int i = 0; i < n; i ++) {
    int b; cin >> b;
    if (b > 0) {
      adder.add_edge(source, i, b);  
      sum_b += b;
    } else {
      adder.add_edge(i, sink, -b);  
    }
  }
  
  for(int i = 0; i < m; i++) {
    int x, y, d; cin >> x >> y >> d;
    adder.add_edge(x, y, d);
  }
  
  int flow = boost::push_relabel_max_flow(G, source, sink);
  if(flow < sum_b) cout << "yes" << endl;
  else cout << "no" << endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}



