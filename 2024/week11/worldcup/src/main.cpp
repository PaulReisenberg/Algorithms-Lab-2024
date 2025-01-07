#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef K::Point_2 P;

using namespace std;

struct W {
  long x;
  long y;
  long s;
  long a;
};

struct S {
  long x;
  long y;
  long d;
  long u;
};

struct L {
  long x;
  long y;
  long r;
};


int n, m, c;

int x(int w, int s) { // amount of beer transported from w to s
  return w * m + s;
}


long floor_to_long(const CGAL::Quotient<CGAL::Gmpz>& x)  // Change this
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void solve() {
  
  cin >> n >> m >> c;
  
  vector<P> points(n+m);
  vector<W> warehouses(n);
  for(int i = 0; i < n; i++) {
    long x, y, s, a; cin >> x >> y >> s >> a;
    points[i] = P(x,y);
    warehouses[i] = {x,y,s,a};
  }
  
  vector<S> stadiums(m);
  for(int i = 0; i < m; i++) {
    long x, y, d, u; cin >> x >> y >> d >> u;
    points[n+i] = P(x,y);
    stadiums[i] = {x,y,d,u};
  }
  
  vector<vector<long>> revenues(n, vector<long>(m));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      long r; cin >> r;
      revenues[i][j] = r * 100;
    }
  }
  
  vector<L> lines(c);
  for(int i = 0; i < c; i++) {
    long x, y, r; cin >> x >> y >> r;
    lines[i] = {x,y,r};
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);

  
  // CONSTRAINTS
  int ROW = 0;
  // Stadium upper bound alcohol
  for(int j = 0; j < m; j++) {
    for(int i = 0; i < n; i++) {
      //if(warehouses[i].a > 0 && warehouses[i].s > 0)
      lp.set_a(x(i, j), ROW, warehouses[i].a);
    }
    lp.set_b(ROW, stadiums[j].u * 100);
    ROW++;
  }
  
  // Stadium total demand
  for(int j = 0; j < m; j++) {
    for(int i = 0; i < n; i++) {
      //if(warehouses[i].s > 0) {
      lp.set_a(x(i, j), ROW, 1);
      lp.set_a(x(i, j), ROW+1, -1);
      //}
    }
    lp.set_b(ROW, stadiums[j].d);
    lp.set_b(ROW+1, -stadiums[j].d);
    ROW += 2;
  }
  
  // Warehouses total supply
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      lp.set_a(x(i,j), ROW, 1);
    }
    lp.set_b(ROW, warehouses[i].s);
    ROW++;
  }
  
  
  Triangulation t(points.begin(), points.end());
  for(L line : lines) {
    long r_2 = line.r * line.r;
    long dist = CGAL::squared_distance(P(line.x, line.y), t.nearest_vertex(P(line.x,line.y))->point());
    bool contains =  dist < r_2;
    
    if(contains) {
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
          long dist_w = CGAL::squared_distance(P(line.x, line.y), P(warehouses[i].x, warehouses[i].y));
          long dist_s = CGAL::squared_distance(P(line.x, line.y), P(stadiums[j].x, stadiums[j].y));
          if((dist_w < r_2 && dist_s > r_2) || (dist_w > r_2 && dist_s < r_2))
            revenues[i][j] -= 1;
        }
      }
    }
  }

  // Define Goal
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      //if(revenues[i][j] != 0 && warehouses[i].s > 0)
      lp.set_c(x(i,j), -revenues[i][j]);
    }
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible())
    cout << "no" << endl;
  else
    std::cout << floor_to_long(-s.objective_value()/100) << std::endl;
  
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) solve();
  
  return 0;
}