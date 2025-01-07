#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

// Instead of using elem struct, we'll use a tuple of vectors to represent the state
using StateMap = unordered_map<int, int>;

void print_state(int top, int bot, int len, const multiset<int>& elements, const StateMap& map) {
    cout << "{" << top << "," << bot << "," << len << ",[";
    bool first = true;
    for(const auto& element : elements) {
        if (!first) cout << ",";
        cout << element;
        first = false;
    }
    cout << "],{";
    for(const auto& [k,v] : map) cout << k << "->" << v << ",";
    cout << "}}" << endl;
}

// Function to create a new state
tuple<int, int, int, multiset<int>, StateMap> create_new_state(
    int top, int bot, int len, const multiset<int>& elements, 
    const StateMap& map, int node, int next_index) {
    StateMap new_map = map;
    new_map[node] = next_index;
    return {top, bot, len, elements, new_map};
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> bri(n);
    for(int i = 0; i < n; i++) cin >> bri[i];
    
    vector<vector<int>> forward(n, vector<int>(0));
    vector<bool> ends(n, true);
    for(int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        ends[u] = false;
        forward[u].push_back(v);
    }
    
    set<int> ropes;
    queue<tuple<int, int, int, multiset<int>, StateMap>> q;
    
    // Initialize first state
    q.push({0, 0, 1, multiset<int>{bri[0]}, StateMap()});
    
    while(!q.empty()) {
        auto [curr_top, curr_bot, curr_len, curr_elements, curr_map] = q.front();
        q.pop();
        
        while(!ends[curr_bot]) {
            //print_state(curr_top, curr_bot, curr_len, curr_elements, curr_map);
            
            // Determine new bot
            int new_bot;
            if(forward[curr_bot].size() == 1) {
                new_bot = forward[curr_bot][0];
            } else if (curr_map.find(curr_bot) != curr_map.end()) {
                new_bot = forward[curr_bot][curr_map[curr_bot]];
            } else {
                for(int i = 1; i < forward[curr_bot].size(); i++) {
                    auto new_state = create_new_state(curr_top, curr_bot, curr_len, 
                                                    curr_elements, curr_map, curr_bot, i);
                    q.push(new_state);
                }
                curr_map[curr_bot] = 0;
                new_bot = forward[curr_bot][0];
            }
            curr_len++;
            
            if(curr_len <= m) {
                curr_bot = new_bot;
                curr_elements.insert(bri[new_bot]);
                
                int min_b = *curr_elements.begin();
                int max_b = *--curr_elements.end();
                
                if(curr_len == m && max_b - min_b <= k) ropes.insert(curr_top);
                continue;
            }
            
            // Determine new top
            int new_top;
            if(forward[curr_top].size() == 1) {
                new_top = forward[curr_top][0];
            } else {
                new_top = forward[curr_top][curr_map[curr_top]];
            }
            curr_len--;
            
            curr_bot = new_bot;
            curr_elements.insert(bri[curr_bot]);
            curr_elements.erase(curr_elements.find(bri[curr_top]));
            curr_top = new_top;
            
            int min_b = *curr_elements.begin();
            int max_b = *--curr_elements.end();
            
            if(curr_len == m && max_b - min_b <= k) ropes.insert(curr_top);
        }
    }
    
    if(ropes.size() > 0) {
        bool first = true;
        for(int rope : ropes) {
            if (first) cout << rope;
            else cout << " " << rope;
            first = false;
        }
        cout << endl;
    } else {
        cout << "Abort mission" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    while(t--) solve();
    return 0;
}