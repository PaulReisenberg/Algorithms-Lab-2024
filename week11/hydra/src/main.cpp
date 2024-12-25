// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

int dijkstra_path(const weighted_graph &G, int s, int t, std::vector<vertex_desc> &path) {
  int n = boost::num_vertices(G);
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_map.begin(), boost::get(boost::vertex_index, G))));

  int cur = t;
  path.clear(); path.push_back(cur);
  while (s != cur) {
    cur = pred_map[cur];
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());
  return dist_map[t];
}

int required_prefix_len(const vector<int>& pattern, int k) {
  int head = pattern[k-1];
  
  for(int i = k-2; i >= 0; i--)
    if(pattern[i] < head)
      return i+1;
  
  return 0;
}



int prefix_match(const vector<int>& v1, const vector<int>& v2, int k, int required_len) {
  for(int i = 1; i < k && k-i >= required_len; i++) {
    bool found = true;
    for(int j = 0; j < k - i; j++) {
      if(v1[i+j] != v2[j]) {
        found = false;
        break;
      }
    }
    if(found) return k - i;
  }
  return 0;
}

void solve() {
  int n, m, k, d;
  cin >> n >> m >> k >> d;
  //cout << "n: " << n << ", m: " << m << ", k: " << k << ", d: " << d << endl;
  
  weighted_graph G(m + 2);
  weight_map weights = boost::get(boost::edge_weight, G);
  int source = m;
  int target = m + 1;
  
  vector<vector<int>> patterns(m, vector<int>(k));
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < k; j++) {
      cin >> patterns[i][j];
    }
  }
  
  sort(patterns.begin(), patterns.end(), [] (const vector<int>& a, const vector<int>& b) {return a[a.size() - 1] < b[b.size() - 1];});
  
  
  edge_desc e;
  for(int i = 0; i < m; i++) {
    
    int head = patterns[i][k-1];
    
    if(head == 0) {
      e = boost::add_edge(source, i, G).first;
      weights[e]=k;
    } else {
      int required_len = required_prefix_len(patterns[i], k);
      //cout << "required_len: " << required_len << endl;
      int j = i - 1;
      while(j >= 0 && patterns[j][k-1] == head) j--;
      
      while(j >= 0 && patterns[j][k-1] == head-1) {
        int prefix_len = prefix_match(patterns[j], patterns[i], k, required_len);
        //cout << "j: " << j << ", i: " << i <<  " -> prefix_len: " << prefix_len << endl;  
        if(prefix_len >= required_len) {
          e = boost::add_edge(j, i, G).first;
          weights[e] = k - prefix_len;
        }
        j--;
      }
      
      if(head == n - 1) {
        e = boost::add_edge(i, target, G).first;
        weights[e] = 0;
      }
    }
  }
  
  int len = dijkstra_dist(G, source, target);
  if(len == 2147483647) cout << "Impossible!" << endl;
  else cout << len << endl;
  
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int t; cin >> t;
  while(t--) solve();
  return 0;
}


