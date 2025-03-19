#include "../include/matrix.hpp"
#include "../include/linalg.hpp"
#include <iostream>
#include <cmath>

/**
 * This example demonstrates 3D transformations using rotation matrices.
 */
int main() {
    std::cout << "3D Transformation Examples\n";
    std::cout << "=========================\n\n";

    // Create a 3D point (vector)
    Vector<double> point(3);
    point.at(0) = 1.0; // x
    point.at(1) = 0.0; // y
    point.at(2) = 0.0; // z

    std::cout << "Original point: (" 
              << point.at(0) << ", "
              << point.at(1) << ", "
              << point.at(2) << ")\n\n";

    // Rotate 45 degrees around Z axis
    double angle = M_PI / 4.0; // 45 degrees
    Matrix<double> rot_z = linalg::rotation_z(angle);
    
    std::cout << "Rotation matrix around Z axis (45 degrees):\n" << rot_z << "\n";

    // Apply transformation
    Matrix<double> point_matrix(3, 1);
    for (size_t i = 0; i < 3; ++i) {
        point_matrix.at(i, 0) = point.at(i);
    }

    Matrix<double> transformed = rot_z * point_matrix;

    std::cout << "Transformed point: ("
              << transformed.at(0, 0) << ", "
              << transformed.at(1, 0) << ", "
              << transformed.at(2, 0) << ")\n";

    return 0;
}
