#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel KE;
typedef KE::Point_2 P;
typedef KE::Segment_2 S;
typedef KE::Ray_2 R;


using namespace std;

double floor_to_double(const KE::FT& x) {
 double a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}

void testcase(int n) {

  // Load data
  long a, b, x, y; 
  cin >> a >> b >> x >> y;
  P p1(a,b), p2(x,y);
  R ray(p1, p2);
  
  long x1, y1, x2, y2;
  vector<S> segs;
  for(int i = 0; i < n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    P s(x1,y1), e(x2,y2);
    S seg(s,e);
    segs.push_back(seg);
  }
  
  random_shuffle(segs.begin(), segs.end());
  
  
  S ray_seg;
  bool found_first = false;
  
  for(int i = 0; i < n; ++i) {
    
    if((!found_first && CGAL::do_intersect(ray, segs[i])) || (found_first && CGAL::do_intersect(ray_seg, segs[i]))) {
      auto o = !found_first ? CGAL::intersection(ray, segs[i]) : CGAL::intersection(ray_seg, segs[i]);
      found_first = true;
      
      if (const P* op = boost::get<P>(&*o)) {
        ray_seg = S(p1, *op);
      } else if (const S* os = boost::get<S>(&*o)) {
        P source = os->source();
        P target = os->target();
        
        if (CGAL::has_larger_distance_to_point(p1, target, source))
          ray_seg = S(p1, source);
        else
          ray_seg = S(p1, target);
      }
      
    }
  }
  if (!found_first)
    cout << "no" << endl;
  else {
    p2 = ray_seg.target();
    cout << long(floor_to_double(p2.x())) << " " << long(floor_to_double(p2.y())) << endl;   
  }
  
}


int main() {
  ios_base::sync_with_stdio(false);
  
  int n;
  while(cin >> n) {
    if(n == 0) return 0;
    testcase(n);
  }
}