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

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
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
  int n; cin >> n;
  
  graph G(n*n+2);
  edge_adder adder(G);
  int sink = n*n;
  int source = n*n +1;
  
  int total = 0;
  for(int y = 0; y < n; y++) {
    for(int x = 0; x < n; x++) {
      int square; cin >> square;
      if(square == 0) continue;
      
      total++;
      int index = y * n + x;
      bool is_black = (x+y) & 1;
      
      if(is_black) {
        adder.add_edge(source, index, 1);
      } else {
        adder.add_edge(index, sink, 1);
        continue;
      }
      
      
      vector<vector<int>> opps = {
        {x+2, y+1},{x+2, y-1},{x+1, y+2},{x+1, y-2},
        {x-2, y+1},{x-2, y-1},{x-1, y+2},{x-1, y-2}
      };
      
      for(vector<int> pos : opps) {
        int x_n = pos[0];
        int y_n = pos[1];
        if(x_n<0 || x_n>=n) continue;
        if(y_n<0 || y_n>=n) continue;
          
        int index_next = n * y_n + x_n;
        adder.add_edge(index, index_next, 1);
      }
    }
  }
  int flow = boost::push_relabel_max_flow(G, source, sink);
  cout << total - flow << endl;
}



int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) solve();
}

