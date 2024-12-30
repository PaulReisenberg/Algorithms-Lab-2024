#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int floor_to_int(CGAL::Quotient<ET> val) {
  int i = floor(CGAL::to_double(val));
  while(i > val) i--;
  while(i+1 < val) i++;
  return i;
}

using namespace std;

int load_int() {
  int n; cin >> n; return n;
}

vector<int> load_int_vec(int n) {
  vector<int> vec(n);
  for(int i = 0; i < n; i++) cin >> vec[n];
  return vec;
}

int eucl_norm(vector<int> vals) {
  int sum = 0;
  for(int i = 0; i < vals.size(); i++) 
    sum += vals[i]*vals[i];
  return sqrt(sum);
}

void solve(int n) {
  int d = load_int();
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  int radius = d;
  lp.set_l(radius, true, 0);
  lp.set_c(radius, -1);
  
  for(int row = 0; row < n; row++) {
    vector<int> a(d);
    
    // build LP
    for(int i = 0; i < d; i++) {
      cin >> a[i];
      lp.set_a(i, row, a[i]);
    }
    int norm = floor(eucl_norm(a));
    
    int b = load_int();
    lp.set_a(radius, row, norm);
    lp.set_b(row, b);
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_unbounded()) 
    cout << "inf" << endl;
  else {
    long sol = CGAL::to_double(s.objective_value()) * -1;
    if(sol < 0) cout << "none" << endl;
    else cout << sol << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  while(true) {
    cin >> n;;
    if(!n) return 0;
    solve(n); 
  }
}