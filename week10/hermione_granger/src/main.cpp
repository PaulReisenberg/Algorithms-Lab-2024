#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <algorithm>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve() {
  int f,m,c,g, d, s;
  cin >> f; cin >> m; cin >> c; cin >> g; cin >> d; cin >> s;
  
  // record position of each slitherin and the information he/she leaks
  
  typedef pair<P, int> IPoint;
  vector<IPoint> points;
  vector<vector<int>> info(s);
  
  
  for(int i = 0; i < s; i++) {
    int x, y, m, c, g; 
    cin >> x; cin >> y; cin >> m; cin >> c; cin >> g;
    points.push_back({P(x,y), i});
    info[i] = {m, c, g};
  }
  Triangulation t;
  t.insert(points.begin(), points.end());
  
  // record the "best" DA member for each slitherin
  vector<vector<int>> nearest_d(s, {-1, -1, -1, -1});
  for(int i = 0; i < d; i++) {
    int x_i, y_i, f_i; 
    cin >> x_i; cin >> y_i; cin >> f_i;
    // just give me the code to find the colosest point in the triangulation
    int j = t.nearest_vertex(P(x_i, y_i))->info();
    
    if(nearest_d[j][0] == -1 || nearest_d[j][0] > f_i) {
      nearest_d[j][0] = f_i;
      nearest_d[j][1] = info[j][0];
      nearest_d[j][2] = info[j][1];
      nearest_d[j][3] = info[j][2];
    }
  }
  
  Program lp (CGAL::LARGER, true, 0, true, 24);
  lp.set_b(0, m);
  lp.set_b(1, c);
  lp.set_b(2, g);
  
  int var = 0;
  for(int i = 0; i < s; i++) {
      if(nearest_d[i][0] == -1) continue;
      lp.set_c(var, nearest_d[i][0]);// cout << "var: " << var << endl;
      //cout << "f_i: " << nearest_d[i][0] << endl;
      lp.set_a(var, 0, nearest_d[i][1]);// cout << "m_i: " <<  nearest_d[i][1] << endl;
      lp.set_a(var, 1, nearest_d[i][2]);// cout << "c_i: " <<  nearest_d[i][2] << endl;
      lp.set_a(var, 2, nearest_d[i][3]);// cout << "g_i: " <<  nearest_d[i][3] << endl;
      var++;
  }
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  //cout << sol << endl;
  if (sol.is_infeasible()) {
    cout << "H" << endl;
  } else if (sol.is_unbounded()) {
    cout << "L" << endl;
  } else {
    double sol_val = CGAL::to_double(sol.objective_value());
    if(sol_val <= f)
      cout << "L" << endl;
    else
      cout << "H" << endl;
  }
  
  
}



int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) {
    solve();
  }
  return 0;
}