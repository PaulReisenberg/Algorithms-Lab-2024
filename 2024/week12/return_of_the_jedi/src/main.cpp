#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

vector<edge_desc> kruskal(const weighted_graph &G, const weight_map& weights) {
    vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
    return mst;
}

void solve() {
    int n, t;
    cin >> n >> t;
    
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;
    
    vector<vector<int>> adj_list(n, vector<int>(n));
    for(int j = 1; j <= n-1; j++) {
        for(int k = 1; k <= n-j; k++) {
            int from = j-1;
            int to = j + k - 1;
            int weight;
            cin >> weight;
            
            adj_list[from][to] = weight;
            adj_list[to][from] = weight;
            e = boost::add_edge(from, to, G).first;
            weights[e] = weight;
        }
    }
    
    vector<edge_desc> mst_lea = kruskal(G, weights);
    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<vector<int>> neighbors(n);
    int min_cost = 0;

    // Build MST adjacency list and mark used edges
    for (const auto& edge : mst_lea) {
        int from = boost::source(edge, G);
        int to = boost::target(edge, G);
        min_cost += adj_list[from][to];
        
        neighbors[from].push_back(to);
        neighbors[to].push_back(from);
        used[from][to] = used[to][from] = true;
    }
    
    // Precompute maximum edge weights for all paths in MST
    vector<vector<int>> max_path_weight(n, vector<int>(n, 0));
    for (int u = 0; u < n; u++) {
        vector<int> stack;
        stack.push_back(u);
        vector<bool> visited(n, false);
        visited[u] = true;
        
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            
            for (int w : neighbors[v]) {
                if (!visited[w]) {
                    visited[w] = true;
                    max_path_weight[u][w] = max(adj_list[v][w], max_path_weight[u][v]);
                    stack.push_back(w);
                }
            }
        }
    }
    
    // Find minimum difference using precomputed maximum weights
    int min_diff = numeric_limits<int>::max();
    for (int from = 0; from < n; from++) {
        for (int to = from + 1; to < n; to++) {
            if (!used[from][to]) {
                int edge_len = adj_list[from][to];
                min_diff = min(min_diff, edge_len - max_path_weight[from][to]);
            }
        }
    }
    
    cout << min_cost + min_diff << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) solve();
    
    return 0;
}