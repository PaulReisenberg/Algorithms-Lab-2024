#include <iostream>
#include <vector>
using namespace std;

// Static DP array like in the fast solution
static int dp[101][100001];

int algorithm(int n, int m, int k, const vector<int>& defense_values) {
    // Store only sequence lengths at each ending position
    vector<int> sequence_length(n, 0);
    
    // Find all valid sequences with sliding window
    int sum = 0;
    int start = 0;
    
    for(int end = 0; end < n; end++) {
        sum += defense_values[end];
        
        while(sum > k) {
            sum -= defense_values[start++];
        }
        
        if(sum == k) {
            sequence_length[end] = end - start + 1;
        }
    }
    
    // Initialize DP
    for(int i = 0; i <= n; i++) {
        dp[0][i] = 0;
    }
    for(int i = 1; i <= m; i++) {
        dp[i][0] = -1;
    }
    
    // Fill DP table
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            const int len = sequence_length[j-1];
            if(len && dp[i-1][j-len] != -1) {
                dp[i][j] = max(dp[i-1][j-len] + len, dp[i][j-1]);
            } else {
                dp[i][j] = dp[i][j-1];
            }
        }
    }
    
    return dp[m][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    while(t--) {
        int n, m, k;
        cin >> n >> m >> k;
        
        vector<int> defense_values(n);
        for(auto& x : defense_values) cin >> x;
        
        int res = algorithm(n, m, k, defense_values);
        cout << (res == -1 ? "fail\n" : to_string(res) + '\n');
    }
}