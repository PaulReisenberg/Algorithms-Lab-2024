#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int ceil_to_int(CGAL::Quotient< ET > val) {
  int i = floor(CGAL::to_double(val));
  while(i < val) i++;
  while(i-1 >= val) i--;
  return i;
}

void solve(int p, int a, int b) {
  
  if(p == 1) {
    Program lp (CGAL::SMALLER, true, 0, false, 0);
    const int X = 0;
    const int Y = 1;
    
    lp.set_a(X, 0, 1);  lp.set_a(Y, 0, 1); lp.set_b(0, 4);
    lp.set_a(X, 1, 4);  lp.set_a(Y, 1, 2); lp.set_b(1, a*b);
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);
    
    lp.set_c(X, a);
    lp.set_c(Y, -b);
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_unbounded()) {
      cout << "unbounded" << endl;
    } else if (s.is_infeasible()) {
      cout << "no" << endl;
    } else {
      cout << -ceil_to_int(s.objective_value()) << endl;
    }
  } else {
    Program lp (CGAL::LARGER, false, 0, true, 0);
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, -4);
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_a(Z, 1, 1); lp.set_b(1, -1*a*b);
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, -1);
    
    lp.set_c(X, a);
    lp.set_c(Y, b);
    lp.set_c(Z, 1);
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_unbounded()) {
      cout << "unbounded" << endl;
    } else if (s.is_infeasible()) {
      cout << "no" << endl;
    } else {
      cout << ceil_to_int(s.objective_value()) << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int p, a, b;
  while(true) {
    cin >> p; cin >> a; cin >> b;
    if(p == 0) return 0;
    solve(p,a,b);
  }
  return 0;
}