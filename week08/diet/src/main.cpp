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

void solve(int n, int m) {
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  
  for(int row = 0; row < n; row++) {
    lp.set_b(2*row, -load_int());
    lp.set_b(2*row+1, load_int());
  }
  
  for(int var = 0; var < m; var++) {
    lp.set_c(var, load_int());
    for(int row = 0; row < n; row++) {
      int amount = load_int();
      lp.set_a(var, 2*row, -amount);
      lp.set_a(var, 2*row+1, amount);
    }
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) cout << "No such diet." << endl;
  else cout << floor_to_int(s.objective_value()) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n, m;
  while(true) {
    cin >> n >> m;
    if(!n && !m) return 0;
    solve(n,m); 
  }
}