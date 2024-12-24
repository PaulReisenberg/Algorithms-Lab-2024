#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

struct M {
  long d;
  long t;
};

typedef tuple<long, long, int> E; // time, distance, steps

vector<E> l1;
vector<E> l2;

void build_subset_list(const vector<M>& moves, vector<E>& list, long D, long T, bool& found) {
    int n = moves.size();
    for (int s = 0; s < 1<<n; ++s) {
        long time = 0;
        long dist = 0;
        int steps = 0;
        for (int i = 0; i < n; ++i) {
            if (s & 1<<i) {
                time += moves[i].t;
                dist += moves[i].d;
                steps += 1;
            }
        }
        if (time < T) {
            if(dist >= D) {
                found = true;
                return;
            }
            list.push_back({time, dist, steps});
        }
    }
}

bool build_lists(const vector<M>& move, long D, long T) {
    int split = move.size()/2;
    vector<M> s1(move.begin(), move.begin() + split);
    vector<M> s2(move.begin()+split, move.end());
    l1 = vector<E>(0);
    l2 = vector<E>(0);
    
    bool found = false;
    build_subset_list(s1, l1, D, T, found);
    if(found) return true;
    build_subset_list(s2, l2, D, T, found);
    if(found) return true;
    
    auto time_comparator = [] (tuple<long, long, int> a, tuple<long, long, int> b) {
        return get<0>(a) < get<0>(b);
    };
    
    sort(l1.begin(), l1.end(), time_comparator);
    sort(l2.begin(), l2.end(), time_comparator);
    
    return false;
}

vector<tuple<long, long>> remove_sub_optimal(const vector<E>& list, long boost) {
    vector<tuple<long, long>> tmp;
    int k = 0;
    long best_dist = 0;
    
    while(k < list.size()) {
        long curr_time = get<0>(list[k]);
        long max_dist = get<1>(list[k]) + get<2>(list[k]) * boost;
        k++;
        
        while(k < list.size() && curr_time == get<0>(list[k])) {
            long dist = get<1>(list[k]) + get<2>(list[k]) * boost;
            max_dist = max(dist, max_dist);
            k++;
        }
        
        if(max_dist > best_dist) {
            tmp.push_back({curr_time, max_dist});
            best_dist = max_dist;
        }
    }
    
    return tmp;
}

bool reachable(long boost, long D, long T) {
    vector<tuple<long, long>> l1_tmp = remove_sub_optimal(l1, boost);
    vector<tuple<long, long>> l2_tmp = remove_sub_optimal(l2, boost);
    
    for(int i = 0; i < l1_tmp.size(); i++) {
        long time_1 = get<0>(l1_tmp[i]);
        long dist_1 = get<1>(l1_tmp[i]);
        
        int left = 0;
        int right = l2_tmp.size() - 1;
        while(left <= right) {
            int curr = (left + right)/2;
            long time_2 = get<0>(l2_tmp[curr]);
            long dist_2 = get<1>(l2_tmp[curr]);
            if(time_1 + time_2 >= T)
                right = curr - 1;
            else if (dist_1 + dist_2 < D)
                left = curr + 1;
            else
                return true;
        }
    }
    return false;
}

void solve() {
  long n, m, D, T;
  cin >> n >> m >> D >> T;
  
  vector<M> move(n);
  for(int i = 0; i < n; i++) {
    long d, t; cin >> d >> t;
    move[i] = {d, t};
  }

  vector<long> boosts(m+1);
  boosts[0] = 0;
  for(int i = 1; i < m+1; i++)
    cin >> boosts[i];
  
  if(build_lists(move, D, T)) {
    cout << 0 << endl;
    return;
  }
  
  // binary search
  int left = 0;
  int right = m+1;
  bool captured = true;
  
  while(left < right) {
    int curr = (right + left)/2;
    bool reach = reachable(boosts[curr], D, T);
    if(reach) {
      right = curr;
      captured = false;
    } else {
      left = curr + 1;
    }
  }
  
  if(captured)
    cout << "Panoramix captured" << endl;
  else
    cout << left << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) solve();
  return 0;
}