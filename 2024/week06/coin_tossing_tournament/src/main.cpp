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
         //cout << "adding edge: (" << from << ", "<< to << ", " << capacity << ")" << endl; 
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
  
  for(int counter = 0; counter < t; counter++) {
    int n, m; cin >> n >> m;
    int a,b,c;
    vector<int> sb(n, 0);
    
    graph G(n+2);
    edge_adder adder(G);
    
    int source = n;
    int sink = n+1;
    int missing = 0;
    
    for(int i = 0; i < m; i++) {
      cin >> a >> b >> c;
      
      if(c == 1) {
        sb[a]++;
      } else if (c == 2) {
        sb[b]++;
      } else {
        int match = n+2+i;
        missing++;
        
        adder.add_edge(source, match, 1);
        adder.add_edge(match, a, 1);
        adder.add_edge(match, b, 1);
      }
    }
    
    int total_diff = 0;
    bool possible = true;
    for(int i = 0; i < n; i++) {
      int score; cin >> score;
      int diff = score - sb[i];
      if (diff < 0) possible = false;
      total_diff += diff;
      adder.add_edge(i, sink, diff);
    }
    
    if(!possible || total_diff != missing || boost::push_relabel_max_flow(G, source, sink) != total_diff) cout << "no" << endl;
    else cout << "yes" << endl;
    
  }
  
  return 0;
}
