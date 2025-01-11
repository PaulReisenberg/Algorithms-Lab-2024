/* DELAUNAY TRIANGULATION 2D
=================================
KEY PROPERTIES
- Contains MST and Nearest Neighbor Graph
- Maximizes smallest angle
- Construction: O(n log n)
- Dual of Voronoi diagram

Where to find?
- tut7 delaunay.cpp -> Basic Delaunay
- tut7 emst -> Delaunay: Ends of Edge, set percision


BASIC SETUP AND CREATION
======================== */
// Required imports
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

// Basic type definitions
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

// Creation and insertion
Triangulation t;
t.insert(pts.begin(), pts.end());
t.nearest_vertex(point);  // Find nearest vertex to given point

/* ITERATORS AND HANDLES
======================= */

// EDGES
// -----
typedef Triangulation::Edge_iterator Edge_iterator;           // Finite edges iterator
typedef Triangulation::All_edges_iterator All_edges_iterator; // All edges iterator
typedef Triangulation::Edge Edge;                            // Edge = pair<Face_handle, int>

// Edge iterator usage
for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    t.segment(e);                           // Get as K::Segment_2
    t.segment(e).squared_length();          // Get edge length
    t.is_infinite(e);                       // Check if infinite
    
    // Access edge endpoints
    e->first->vertex((e->second + 1)%3);    // First endpoint
    e->first->vertex((e->second + 2)%3);    // Second endpoint
    
    // Access adjacent faces
    Face_handle f1 = e->first;              // First adjacent face
    Face_handle f2 = f1->neighbor(e->second);// Second adjacent face
}

// VERTICES
// --------
typedef Triangulation::Vertex_iterator Vertex_iterator;         // Finite vertices iterator
typedef Triangulation::All_vertices_iterator All_vertices_iterator; // All vertices iterator
typedef Triangulation::Vertex_handle Vertex_handle;            // Handle to vertex
typedef Triangulation::Vertex Vertex;                          // Actual vertex type

// Vertex iterator usage
for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    v->point();                             // Get vertex coordinates
    t.is_infinite(v);                       // Check if infinite
    t.degree(v);                            // Get vertex degree
    
    // Get circulators
    t.incident_faces(v);                    // Face circulator
    t.incident_vertices(v);                 // Vertex circulator
    t.incident_edges(v);                    // Edge circulator
    
    Point_2 p = v->point();                 // Get as Point_2
}

// FACES
// -----
typedef Triangulation::Face_iterator Face_iterator;           // Finite faces iterator
typedef Triangulation::All_faces_iterator All_faces_iterator; // All faces iterator
typedef Triangulation::Face_handle Face_handle;              // Handle to face
typedef Triangulation::Face Face;                            // Actual face type

// Face iterator usage
for(Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); f++) {
    t.triangle(f);                          // Get as K::Triangle_2
    t.is_infinite(f);                       // Check if infinite
    f->vertex(x);                           // Get vertex (CCW order)
    f->neighbor(x);                         // Get neighbor opposite to vertex x
}

/* CIRCULATORS
============= */
// Example usage
Triangulation::Edge_circulator c = t.incident_edges(v);
do {
    if (t.is_infinite(c)) { /* handle infinite edge */ }
    // Process edge
} while (++c != t.incident_edges(v));

/* ENHANCING DATA STRUCTURES
========================== */

// Adding info to faces
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
enum Color { Black = 0, White = 1, Red = 2 };
typedef CGAL::Triangulation_face_base_with_info_2<Color,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

// Adding info to vertices
typedef CGAL::Triangulation_vertex_base_with_info_2<Color, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

// Using vertex info in construction
vector<pair<K::Point_2, Color>> info_points;
Triangulation t(info_points.begin(), info_points.end());

/* VORONOI DIAGRAM
================= */
// Accessing the dual Voronoi diagram
Face_handle f;
t.dual(f);         // Get Voronoi vertex (Point_2)
t.dual(edge);      // Get Voronoi edge (Ray_2/Line_2/Segment_2)