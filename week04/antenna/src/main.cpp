#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 Point;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;



using namespace std;


double ceil_to_double(const K::FT& x) {
 double a = ceil(CGAL::to_double(x));
 while (a < x) a += 1;
 while (a >= x+1) a -= 1;
 return a;
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int n;
  
  while(cin >> n) {
    if(n == 0) return 0;
    
    long x, y;
    vector<Point> points;
    for(int i = 0; i < n; i++) {
      cin >> x >> y;
      points.push_back(Point(x,y));
    }

    Min_circle  mc(points.begin(), points.end(), true);
    Traits::Circle c = mc.circle();
    cout << long(ceil_to_double(CGAL::sqrt(c.squared_radius()))) << endl; 
  }
  return 0;
}