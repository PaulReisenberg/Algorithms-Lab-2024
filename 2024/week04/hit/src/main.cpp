#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;


using namespace std;


void testcase(int n) {

  long a, b, x, y; 
  cin >> a >> b >> x >> y;
  
  K::Point_2 p1(a,b);
  K::Point_2 p2(x,y);
  K::Ray_2 ray(p1, p2);
  
  bool found = false;
  long x1, y1, x2, y2;
  
  for(int i = 0; i < n; ++i) {
    cin >> x1 >> y1 >> x2 >> y2;
    
    if(!found) {
      K::Point_2 s(x1,y1);
      K::Point_2 e(x2,y2);
      K::Segment_2 seg(s,e);
      if(CGAL::do_intersect(ray, seg)) found = true;
    }
  }
  
  cout << (found ? "yes" : "no") << endl;
  
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int n;
  while(cin >> n) {
    
    if(n == 0) break;
    testcase(n);
  }
  return 0;
}