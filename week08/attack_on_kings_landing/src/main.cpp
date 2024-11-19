#include <iostream>
#include <vector>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

// Fast I/O optimization
inline void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

vector<int> load_iv(int n) {
  vector<int> vec(n);
  for(int i = 0; i < n; i++) cin >> vec[i];
  return vec;
}

void maximum_matching(const graph& G) {
    const int n = boost::num_vertices(G);
    vector<vertex_desc> mate_map(n);
    boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    cout << boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G))) << '\n';
}

void solve() {
    int num_intersections, num_roads, num_barracks, num_plazas, distance;
    cin >> num_intersections >> num_roads >> num_barracks >> num_plazas >> distance;
    
    vector<int> barrack_locations = load_iv(num_barracks);
    vector<int> plaza_locations = load_iv(num_plazas);
    
    vector<vector<int>> adj_list(num_intersections);
    vector<vector<int>> weights(num_intersections);
    
    for(int i = 0; i < num_roads; i++) {
        int x, y, l;
        cin >> x >> y >> l;
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
        weights[x].push_back(l);
        weights[y].push_back(l);
    }
    
    // BFS optimization with single array reuse
    vector<int> distance_to_barrack(num_intersections, distance + 1);
    queue<pair<int, int>> Q;
    
    for(int barrack : barrack_locations) {
        Q.push({barrack, 0});
        
        while(!Q.empty()) {
            auto [curr_inter, curr_d] = Q.front();
            Q.pop();
            
            if(curr_d >= distance_to_barrack[curr_inter]) continue;
            distance_to_barrack[curr_inter] = curr_d;
            
            for(int i = 0; i < adj_list[curr_inter].size(); i++) {
                int to = adj_list[curr_inter][i];
                int l = weights[curr_inter][i];
                int new_dist = curr_d + l;
                if(new_dist < distance_to_barrack[to]) {
                    Q.push({to, new_dist});
                }
            }
        }
    }
    
    // Build graph with pre-filtered edges
    graph G(num_intersections + num_plazas);
    for(int i = 0; i < num_intersections; i++) {
        if(distance_to_barrack[i] > distance) continue;
        for(int j = 0; j < adj_list[i].size(); j++) {
            int to = adj_list[i][j];
            if(distance_to_barrack[to] <= distance) {
                boost::add_edge(i, to, G);
            }
        }
    }
    
    for(int i = 0; i < num_plazas; i++) {
        int plaza = plaza_locations[i];
        if(distance_to_barrack[plaza] <= distance) {
            for(int j = 0; j < adj_list[plaza].size(); j++) {
                int to = adj_list[plaza][j];
                if(distance_to_barrack[to] <= distance) {
                    boost::add_edge(i + num_intersections, to, G);
                }
            }
        }
    }
    
    maximum_matching(G);
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}