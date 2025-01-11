/* LINEAR PROGRAMMING IN CGAL
============================
Feasible if min{num constraints, num edges} < 200

BASIC SETUP
=========== */
// Required imports
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>



// 1. INPUT TYPES (IT)
typedef int IT;                  // For small integers
typedef long IT;                // For larger integers
typedef CGAL::Gmpz IT;         // For arbitrary precision integers
typedef CGAL::Gmpq IT;         // For arbitrary precision rationals

// 2. EXACT TYPES (ET)
typedef CGAL::Gmpz ET;         // If input coefficients are integers (includes int/long/Gmpz)
typedef CGAL::Gmpq ET;         // If input coefficients are rationals (Gmpq)


// 3. PROGRAM / SOLUTION TYPE
typedef CGAL::Quadratic_program<IT> Program;     // Program type
typedef CGAL::Quadratic_program_solution<ET> Solution; // Solution type



/* PROGRAM CREATION
================= */
// Create program with different options
Program lp (CGAL::SMALLER,     // Default relation for constraints (SMALLER, EQUAL, LARGER)
           true,              // Has non-negative variables? (true = x ≥ 0)
           0,                 // Lower bound value if above is false
           false,             // Has upper bound?
           0);               // Upper bound value if above is true

/* SETTING UP THE PROGRAM
======================= */
// Setting coefficients
lp.set_a(var_idx, constr_idx, value);  // Set coefficient in constraint matrix A
lp.set_b(constr_idx, value);           // Set right-hand side b
lp.set_c(var_idx, value);              // Set objective function coefficient
lp.set_c0(value);                      // Set constant term in objective function

// Setting bounds
lp.set_l(var_idx, true, value);        // Set lower bound for variable
lp.set_u(var_idx, true, value);        // Set upper bound for variable

/* SOLVING THE PROGRAM
==================== */
Solution s = CGAL::solve_linear_program(lp, ET());

// Check solution status
s.is_optimal();      // Has optimal solution
s.is_infeasible();   // No feasible solution exists
s.is_unbounded();    // Solution is unbounded

// Get solution values
s.objective_value(); // Value of objective function (CGAL::Quotient<ET>)


// CODE SNIPPTES

long ceil_to_long(CGAL::Quotient<ET> val) {
  double i = ceil(CGAL::to_double(val));
  while(i < val) i++;
  while(i-1 >= val) i--;
  
  return i;
}