#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long ceil_to_long(CGAL::Quotient<ET> val) {
  double i = ceil(CGAL::to_double(val));
  while(i < val) i++;
  while(i-1 >= val) i--;
  
  return i;
}

using namespace std;


void solve() {
  
  int n, m; cin >> n >> m;
  long s; cin >> s;
  long y_n_sum, y_c_sum; 
  y_n_sum = 0;
  y_c_sum = 0;
  long x_n_sum, x_c_sum; 
  x_n_sum = 0;
  x_c_sum = 0;
  
  // Define Variables
  // water canal:  a_w * x + y = c_w
  // sewage canal: x + b_s * y = c_s
  const int a_w = 0;
  const int c_w = 1;
  const int b_s = 2;
  const int c_s = 3;
  const int l_max = 4;
  int row = 0;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  vector<vector<long>> houses(n+m, {0,0});
  for(int i = 0; i < n; i++) {
    long x, y; cin >> x; cin >> y;
    houses[i] = {x,y};
    x_n_sum += x;
    y_n_sum += y;
    
    lp.set_a(c_s, row, 1); lp.set_a(b_s, row, y); lp.set_b(row, -x);
    row++;
  }
  
  for(int i = 0; i < m; i++) {
    long x, y; cin >> x; cin >> y;
    houses[n+i] = {x,y};
    x_c_sum += x;
    y_c_sum += y;
    
    lp.set_a(c_s, row, -1);lp.set_a(b_s, row, -y);lp.set_b(row, x);
    row++;
  }

  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()) {
    cout << "Y" << endl;
    return;
  }
  
  
  // Condition: Sewage pipes <= s
  if (s != -1)
  {
    lp.set_a(b_s, row, y_c_sum - y_n_sum);
    lp.set_a(c_s, row, m - n);
    lp.set_b(row, s - (x_c_sum - x_n_sum));
    row++;
  }
  
  // Condition: fresh water othorgonal to sewage
  lp.set_a(a_w, row, 1); lp.set_a(b_s, row, 1); lp.set_b(row, 0);
  row++;
  lp.set_a(a_w, row, -1); lp.set_a(b_s, row, -1); lp.set_b(row, 0);
  row++;
  
  // Set Goal
  lp.set_c(l_max, 1);
  
  for(int i = 0; i < n+m; i++) {
    // y-value of water connection: y_w = c_w - a_w * x
    // max_len >= nobels[i].y - (c_w - a_w * x)
    // max_len + (c_w - a_w * x) >= nobels[i].y
    // 1*max_len +1*c_w -x*a_w) >= nobels[i].y
    //-1*max_len -1*c_w +x*a_w) <= -nobels[i].y
    
    lp.set_a(a_w, row, houses[i][0]);
    lp.set_a(c_w, row, 1);
    lp.set_a(l_max, row, -1);
    lp.set_b(row, -houses[i][1]);
    row++;
    
    lp.set_a(a_w, row, -houses[i][0]);
    lp.set_a(c_w, row, -1);
    lp.set_a(l_max, row, -1);
    lp.set_b(row, houses[i][1]);
    row++;
  }
  
  Solution sol2 = CGAL::solve_linear_program(lp, ET());
  //cout << sol << endl;
  if(sol2.is_infeasible()) {
    cout << "B" << endl;
  } else {
    //cout << "number" << endl;
    cout << ceil_to_long(sol2.objective_value()) << endl;
  }

  
  
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--)solve();
  return 0;
}