#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <algorithm>

#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef K::Point_2 P;

struct Edge {
  int from;
  int to;
  long d;
};


vector<pair<P,int>> load_ipvec(int n) {
  vector<pair<P,int>> vec;
  vec.reserve(n);
  
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x; cin >> y;
    vec.emplace_back(P(x,y), i);
  }
  return vec;
}


int get_f(int k, const vector<int>& cluster_counts) {
  int c1 = cluster_counts[0];
  int c2 = cluster_counts[1];
  int c3 = cluster_counts[2];
  int c4 = cluster_counts[3];
  
  if(k == 1) {
    return c1 + c2 + c3 + c4;
  } else if (k == 2) {
    return c2 + c3 + c4 + c1/2;
  } else if (k == 3) {
    int sum = c3 + c4;
    if(c1 < c2) {
      sum += c1;
      sum += (c2 - c1)/2;
    } else if (c1 > c2) {
      sum += c2;
      sum += (c1 - c2)/3;
    } else {
      sum += c1;
    }
    return sum;
  } else { // k == 4
    int sum = c4;
    sum += c2/2; 
    c2 = c2 % 2;
    int matched13 = min(c1, c3);
    sum += matched13;
    c1 -= matched13;
    c3 -= matched13;
    
    if(c1 == 0) {
      sum += (c2 + c3)/2;
    } else { //c3 == 0
      sum += c1/4;
      c1 = c1 % 4;
      if(c1 >= 2 && c2 >= 1) 
        sum++;
    }
    return sum;
  }
  
}




void solve() {
  
  long n, k, f_0, s_0;
  cin >> n; cin >> k; cin >> f_0; cin >> s_0;
  long f_sol, s_sol; f_sol = s_sol = -1;
  //cout << "n: " << n <<  ", k: " << k << ", f_0: " << f_0 << ", s_0: " << s_0 << endl;
  vector<pair<P,int>> tents = load_ipvec(n);
  Triangulation t(tents.begin(), tents.end());
  
  vector<Edge> edges;
  for(auto edge = t.finite_edges_begin(); edge != t.finite_edges_end(); ++edge) {
    int from = edge->first->vertex((edge->second+1)%3)->info();
    int to = edge->first->vertex((edge->second+2)%3)->info();
    long d = t.segment(edge).squared_length();
    edges.push_back({from, to, d});
  }
  sort(edges.begin(), edges.end(), [](Edge a, Edge b) {return a.d < b.d;});
  
  vector<int> rank(n);
  vector<int> parent(n);
  boost::disjoint_sets<int*, int*> dsets(&rank[0], &parent[0]);
  for(int i = 0; i < n; i++) dsets.make_set(i);
  
  vector<int> cluster_sizes(n, 1);
  vector<int> cluster_counts = {n, 0, 0, 0};
  
  s_sol = edges[0].d;
  f_sol = s_0 <= edges[0].d ? n/k : 1;
  
  for(int i = 0; i < edges.size(); i++) {
    //cout << "s_sol: " << s_sol << ", f_sol: " << f_sol << endl;
    Edge e = edges[i];
    int set1 = dsets.find_set(e.from);
    int set2 = dsets.find_set(e.to);
    //cout << "from: " << e.from << ", to: " << e.to << endl;
    //cout << "set1: " << set1 << ", set2: " << set2 << endl;
    if(set1 != set2) {
      int size1 = cluster_sizes[set1];
      int size2 = cluster_sizes[set2];
      cluster_counts[min(size1, 4)-1]--;
      cluster_counts[min(size2, 4)-1]--;
        
      dsets.union_set(set1, set2);
      int new_size = size1 + size2;
      cluster_sizes[set1] = cluster_sizes[set2] = new_size;
        
      cluster_counts[min(new_size, 4)-1]++;
    }
    
    //cout << "1: " << cluster_counts[0] << ", 2: " << cluster_counts[1] << ", 3: "  << cluster_counts[2] << ", 4: "  << cluster_counts[3] << endl;
    
    if(i < edges.size()-1 && edges[i].d < edges[i+1].d) {
      int f = get_f(k, cluster_counts);
      //cout << "f: " << f << endl;
      if(f >= f_0)
        s_sol = edges[i+1].d;
      if(f > f_sol && s_0 <= edges[i+1].d)
        f_sol = f;
    }
  }
  cout << s_sol << " " << f_sol << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  return 0;
}