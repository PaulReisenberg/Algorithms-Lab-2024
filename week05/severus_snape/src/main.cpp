#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void algorithm(int n, int m, int a, int b, int P, int H, int W,
              const vector<pair<int,int>>& type_a, const vector<int>& type_b) {
    // Optimize memory by using pair for type_a
    // dp[x][y] maximum amount of magical power we can gain from
    // x potions while getting at least y happiness
    vector<vector<long long>> dp1(n + 1, vector<long long>(H + 1, -1));
    dp1[0][0] = 0;
    vector<vector<long long>> dp2 = dp1;

    // Dynamic programming to compute maximum power for each combination
    for (int i = 0; i < n; i++) {
        for (int p = 1; p <= n; p++) {
            for (int h = 0; h <= H; h++) {
                int p_gain = type_a[i].first;
                int h_gain = type_a[i].second;

                int prev_h = max(h - h_gain, 0);
                if (dp1[p-1][prev_h] != -1) {
                    dp2[p][h] = max(dp1[p][h], dp1[p-1][prev_h] + p_gain);
                } else {
                    dp2[p][h] = dp1[p][h];
                }
            }
        }
        dp1 = dp2;
    }

    // Sort type B potions in descending order for optimal selection
    vector<int> sorted_b = type_b;
    sort(sorted_b.begin(), sorted_b.end(), greater<int>());

    // Find minimum combination of potions that satisfies requirements
    long long w_level = 0;
    for (int b_count = 0; b_count <= m; b_count++) {
        // Calculate accumulated wit from type B potions
        if (b_count > 0) {
            if (b_count > sorted_b.size()) break;
            w_level += sorted_b[b_count - 1];
        }

        // Find minimum number of type A potions needed
        for (int a_count = 0; a_count <= n; a_count++) {
            if (dp1[a_count][H] == -1) continue;

            long long p_level = dp1[a_count][H] - b_count * (long long)b;
            long long final_wit = w_level - a_count * (long long)a;

            if (p_level >= P && final_wit >= W) {
                cout << a_count + b_count << endl;
                return;
            }
        }
    }
    cout << "-1" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, a, b, P, H, W;
        cin >> n >> m >> a >> b >> P >> H >> W;

        vector<pair<int,int>> type_a(n);
        for (int i = 0; i < n; i++) {
            cin >> type_a[i].first >> type_a[i].second;
        }

        vector<int> type_b(m);
        for (int i = 0; i < m; i++) {
            cin >> type_b[i];
        }

        algorithm(n, m, a, b, P, H, W, type_a, type_b);
    }
    return 0;
}