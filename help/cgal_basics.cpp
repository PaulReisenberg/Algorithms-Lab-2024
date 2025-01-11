// KERNELS AND BASIC TYPES
// ======================

/* Where to find:
- tut4 intersect.cpp -> Intersection
- tut4 miniball.cpp -> Min Enclosing Circle 
*/






// Common Kernels
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;  // Fast, for predicates only
typedef CGAL::Exact_predicates_exact_constructions_kernel K;    // Exact arithmetic, slower
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;  // With square roots

// Number Types
typedef K::FT FT;  // Field type (usually double or CGAL::Gmpq)
CGAL::to_double(x);  // Convert FT to double
FT(x);  // Convert double to FT

// 2D GEOMETRIC TYPES
// ================

// Points
typedef K::Point_2 Point_2;
Point_2 p(x, y);
p.x();  // Get x coordinate
p.y();  // Get y coordinate

// Vectors
typedef K::Vector_2 Vector_2;
Vector_2 v(p1, p2);  // Vector from p1 to p2
v.squared_length();

// Segments
typedef K::Segment_2 Segment_2;
Segment_2 s(p1, p2);
s.source();  // First endpoint
s.target();  // Second endpoint
s.squared_length();

// Rays
typedef K::Ray_2 Ray_2;
Ray_2 r(p, q);  // Ray from p through q
r.source();     // Starting point
r.direction();  // Direction vector

// Lines
typedef K::Line_2 Line_2;
Line_2 l(p, q);  // Line through p and q
l.has_on(p);     // Check if point is on line

// Circles
typedef K::Circle_2 Circle_2;
Circle_2 c(p, squared_radius);  // Center and squared radius
c.center();
c.squared_radius();

// INTERSECTIONS
// ============

// Check for intersection
bool intersect = CGAL::do_intersect(object1, object2);

// Get intersection
typedef boost::optional<boost::variant<Point_2, Segment_2>> Intersection_result;
Intersection_result result = CGAL::intersection(s1, s2);

// Handle intersection result
if (const Point_2* p = boost::get<Point_2>(&*result)) {
    // Intersection is a point
    Point_2 intersection_point = *p;
} else if (const Segment_2* s = boost::get<Segment_2>(&*result)) {
    // Intersection is a segment
    Segment_2 intersection_segment = *s;
}

// MINIMUM ENCLOSING CIRCLE
// =======================
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
Min_circle mc(points.begin(), points.end(), true);  // true for randomization
Traits::Circle c = mc.circle();

// UTILITY FUNCTIONS
// ===============

// Floor to double (for exact number types)
double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

// Numeric limits
#include <limits>
int max_int = std::numeric_limits<int>::max();
double inf = std::numeric_limits<double>::infinity();


// Optput correct format
#include <iomanip>
cout << std::fixed << std::setprecision(0);