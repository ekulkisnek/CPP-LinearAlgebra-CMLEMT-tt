#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/linalg.hpp"
#include <iostream>

/**
 * This example demonstrates basic matrix operations and solving
 * a system of linear equations.
 */
int main() {
    std::cout << "Linear Algebra Examples\n";
    std::cout << "======================\n\n";

    // Create a 2x2 matrix
    Matrix<double> A(2, 2);
    A.at(0, 0) = 3; A.at(0, 1) = 2;
    A.at(1, 0) = 1; A.at(1, 1) = 1;

    std::cout << "Matrix A:\n" << A << "\n";

    // Create another 2x2 matrix
    Matrix<double> B(2, 2);
    B.at(0, 0) = 1; B.at(0, 1) = 2;
    B.at(1, 0) = 3; B.at(1, 1) = 4;

    std::cout << "Matrix B:\n" << B << "\n";

    // Matrix multiplication
    std::cout << "A * B:\n" << (A * B) << "\n";

    // Solve system of linear equations
    // 3x + 2y = 7
    // x + y = 3
    Vector<double> b(2);
    b.at(0) = 7;
    b.at(1) = 3;

    std::cout << "Solving system of equations:\n";
    std::cout << "3x + 2y = 7\n";
    std::cout << "x + y = 3\n\n";

    Vector<double> solution = linalg::solve_linear_system(A, b);
    std::cout << "Solution:\n";
    std::cout << "x = " << solution.at(0) << "\n";
    std::cout << "y = " << solution.at(1) << "\n";

    return 0;
}
