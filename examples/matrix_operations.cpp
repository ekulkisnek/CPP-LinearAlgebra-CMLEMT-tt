
#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/linalg.hpp"
#include <iostream>

/**
 * EDUCATIONAL EXAMPLE: Matrix Operations and Linear Systems
 * 
 * This program demonstrates fundamental concepts in linear algebra:
 * 1. Matrix Creation and Manipulation
 * 2. Matrix Multiplication
 * 3. Solving Systems of Linear Equations
 * 
 * MATHEMATICAL BACKGROUND:
 * - Matrices represent linear transformations
 * - Matrix multiplication combines transformations
 * - Linear systems model real-world relationships
 */
int main() {
    std::cout << "Linear Algebra Examples\n";
    std::cout << "======================\n\n";

    // CONCEPT 1: Matrix Creation
    // Creating a 2x2 matrix A representing a linear transformation
    // This matrix scales x by 3 and adds 2 times y to it
    // It also creates a weighted sum for y
    Matrix<double> A(2, 2);
    A.at(0, 0) = 3; A.at(0, 1) = 2;  // First row: 3x + 2y
    A.at(1, 0) = 1; A.at(1, 1) = 1;  // Second row: x + y

    std::cout << "Matrix A (Transformation Matrix):\n" << A << "\n";
    std::cout << "• First row represents: 3x + 2y\n";
    std::cout << "• Second row represents: x + y\n\n";

    // CONCEPT 2: Another Transformation Matrix
    // Matrix B represents another transformation
    Matrix<double> B(2, 2);
    B.at(0, 0) = 1; B.at(0, 1) = 2;
    B.at(1, 0) = 3; B.at(1, 1) = 4;

    std::cout << "Matrix B (Second Transformation):\n" << B << "\n";

    // CONCEPT 3: Matrix Multiplication
    // Composing transformations A and B
    // Result represents applying B's transformation after A's
    std::cout << "Matrix Multiplication (A * B):\n";
    std::cout << "This represents composed transformations:\n";
    std::cout << (A * B) << "\n";

    // CONCEPT 4: Solving Linear Systems
    // System of equations:
    // 3x + 2y = 7
    // x + y = 3
    Vector<double> b(2);
    b.at(0) = 7;  // Right-hand side of first equation
    b.at(1) = 3;  // Right-hand side of second equation

    std::cout << "\nSOLVING LINEAR SYSTEM:\n";
    std::cout << "Equations:\n";
    std::cout << "3x + 2y = 7  (Equation 1)\n";
    std::cout << "x + y = 3    (Equation 2)\n\n";

    // Using Gaussian elimination to solve the system
    Vector<double> solution = linalg::solve_linear_system(A, b);
    std::cout << "Solution:\n";
    std::cout << "x = " << solution.at(0) << " (verify: " << solution.at(0) << " is the x-coordinate)\n";
    std::cout << "y = " << solution.at(1) << " (verify: " << solution.at(1) << " is the y-coordinate)\n";

    // Verification section
    std::cout << "\nVERIFICATION:\n";
    std::cout << "Equation 1: 3(" << solution.at(0) << ") + 2(" << solution.at(1) << ") = " 
              << (3 * solution.at(0) + 2 * solution.at(1)) << " ≈ 7\n";
    std::cout << "Equation 2: " << solution.at(0) << " + " << solution.at(1) << " = "
              << (solution.at(0) + solution.at(1)) << " = 3\n";

    return 0;
}
