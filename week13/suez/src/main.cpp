#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

double floor_to_double(const CGAL::Quotient<ET> &x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

struct Point {
  int x;
  int y;
};

void solve() {
  int n, m, h, w;
  cin >> n >> m >> h >> w;
  
  std::vector<Point> nails(n);
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    nails[i] = { x, y };
  }

  std::vector<Point> occupied(m);
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    occupied[i] = { x, y }; 
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0);
  int row = 0;
  
  // Constraints for other nails
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      
      long x_diff = abs(nails[i].x - nails[j].x);
      long y_diff = abs(nails[i].y - nails[j].y);
      
      if(x_diff * h >= y_diff * w) {
        lp.set_a(i, row, w);
        lp.set_a(j, row, w);
        lp.set_b(row, 2 * x_diff);
      } else {
        lp.set_a(i, row, h);
        lp.set_a(j, row, h);
        lp.set_b(row, 2 * y_diff);
      }
      
      
      
      row++;
    }
  }
  
  // Constraints for other posters
  for(int i = 0; i < n; i++) {
    IT upper_bound = IT(DBL_MAX);
    for(int j = 0; j < m; j++) {
      int x_diff = abs(nails[i].x - occupied[j].x);
      int y_diff = abs(nails[i].y - occupied[j].y);
      
      IT bound = max(IT(2*x_diff - w, w), IT(2*y_diff - h, h));
      upper_bound = min(bound, upper_bound);
    }
    lp.set_u(i, true, upper_bound);
  }
  
  
  // Goal: Maximize Perimiter
  for(int i = 0; i < n; i++) {
    lp.set_c(i, -2*(w+h));
  }
  
   Solution s = CGAL::solve_linear_program(lp, ET());
  
  // The floor of the minimum is the ceiling of the maximum.
  std::cout << long(-floor_to_double(s.objective_value())) << std::endl;
  
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  return 0;
}