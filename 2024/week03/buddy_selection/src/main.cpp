#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_desc;

int main() {
  
  ios_base::sync_with_stdio(false);
  int num_cases; cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++) {
    
    int n, c, f; cin >> n >> c >> f;
    vector<vector<string>> chs(n);
    
    for (int i = 0; i < n; i++) {
      string ch;
      for(int j = 0; j < c; j++) {
        cin >> ch;
        chs[i].push_back(ch);
      }
      sort(chs[i].begin(), chs[i].end());
    }
    
    Graph g(n);
    
    for(int u = 0; u < n; u++) {
      for(int v = 0; v < n; v++) {
        int sim, i, j; sim=i=j=0;
        
        while(i < c && j < c) {
          if(chs[u][i] == chs[v][j]) { sim++; i++; j++;} 
          else if (chs[u][i] < chs[v][j]) i++;
          else j++;
        }
        
        if(sim > f) boost::add_edge(u,v,g);
      }
    }
    vector<vertex_desc> mate(n);
    edmonds_maximum_cardinality_matching(g, &mate[0]);
    int matching_size = boost::matching_size(g, &mate[0]);
    
    if (matching_size * 2 >= n) cout << "not optimal" << endl;
    else cout << "optimal" << endl;
      
  }
  
  return 0;
}