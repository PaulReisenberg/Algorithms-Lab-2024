#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct Edge {
  long to;
  long time;
};
struct R {
  long galons;
  long lps;
  long time;
  long time_to_node;
};
vector<vector<Edge>> adj_list;
vector<long> galons_per_chamber;
R traverse(long node) {
  
  vector<R> sub_rets;
  for(Edge e : adj_list[node]) {
    R r = traverse(e.to);
    r.time_to_node = e.time;
    sub_rets.push_back(r);
  }
  
  sort(sub_rets.begin(), sub_rets.end(), [](R a, R b) {
    long lose_a = a.lps * (b.time + 2*b.time_to_node);// + b.lps*b.time_to_node;
    long lose_b = b.lps * (a.time + 2*a.time_to_node);// + a.lps*a.time_to_node;
    
    return lose_a > lose_b;
  });
  
  long time = 0;
  long galons = galons_per_chamber[node];
  long lps = 0;
  for(R r : sub_rets) {
    time += r.time_to_node;
    galons += r.galons - time * r.lps;
    time += r.time + r.time_to_node;
    lps += r.lps;
  }
  
  return {galons, lps+1, time};
}
void solve() {
  long n; cin >> n;
  galons_per_chamber = vector<long>(n+1, 0);
  for(long i = 1; i <= n; i++) cin >> galons_per_chamber[i];
  
  long u, v, l;
  adj_list = vector<vector<Edge>>(n+1);
  queue<vector<long>> Q;
  for(long i = 0; i < n; i++) {
    cin >> u; cin >> v; cin >> l;
    adj_list[u].push_back({v, l});
  }
  R r = traverse(0);
  cout << r.galons << endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  long t; cin >> t;
  for(long i = 0; i < t; i++) solve();
  
  
  return 0;
}