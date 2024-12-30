



// Iterate over all finite vertices
for(auto v = t.finite_vertices_begin(); v < t.finite_vertices_end(); v++) {}


// Iterate over all finite edges
for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {}

// check distance of edge
t.segment(*e).squared_length()

