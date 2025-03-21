
#include "../include/matrix.hpp"
#include "../include/linalg.hpp"
#include <iostream>
#include <cmath>

/**
 * EDUCATIONAL EXAMPLE: 3D Transformations
 * 
 * This program demonstrates:
 * 1. 3D Point Representation
 * 2. Rotation Matrices
 * 3. Geometric Transformations
 * 
 * MATHEMATICAL CONCEPTS:
 * - Points in 3D space are represented as vectors
 * - Rotations preserve distances and angles
 * - Transformation matrices operate on vectors
 * 
 * APPLICATIONS:
 * - Computer Graphics
 * - Robotics
 * - Computer Vision
 * - Game Development
 */
int main() {
    std::cout << "3D Transformation Examples\n";
    std::cout << "=========================\n\n";

    // CONCEPT 1: 3D Point Creation
    // Creating a point at (1,0,0) on the x-axis
    Vector<double> point(3);
    point.at(0) = 1.0; // x-coordinate
    point.at(1) = 0.0; // y-coordinate
    point.at(2) = 0.0; // z-coordinate

    std::cout << "Original point on x-axis: (" 
              << point.at(0) << ", "
              << point.at(1) << ", "
              << point.at(2) << ")\n";
    std::cout << "• This point lies 1 unit along the x-axis\n";
    std::cout << "• It will be rotated around the z-axis\n\n";

    // CONCEPT 2: Rotation Matrix Creation
    // Creating a rotation of 45 degrees (π/4 radians) around Z axis
    double angle = M_PI / 4.0; // 45 degrees in radians
    Matrix<double> rot_z = linalg::rotation_z(angle);
    
    std::cout << "Rotation matrix around Z axis (45 degrees):\n" 
              << rot_z << "\n";
    std::cout << "• This matrix rotates points counter-clockwise\n";
    std::cout << "• The rotation preserves the distance from the z-axis\n\n";

    // CONCEPT 3: Applying Transformation
    // Convert point to matrix format for multiplication
    Matrix<double> point_matrix(3, 1);
    for (size_t i = 0; i < 3; ++i) {
        point_matrix.at(i, 0) = point.at(i);
    }

    // Perform the rotation
    Matrix<double> transformed = rot_z * point_matrix;

    std::cout << "Transformed point: ("
              << transformed.at(0, 0) << ", "
              << transformed.at(1, 0) << ", "
              << transformed.at(2, 0) << ")\n\n";

    // CONCEPT 4: Understanding the Result
    std::cout << "ANALYSIS OF TRANSFORMATION:\n";
    std::cout << "• Original length = sqrt(" 
              << point.at(0)*point.at(0) + point.at(1)*point.at(1) 
              << ") = 1.0\n";
    std::cout << "• New length = sqrt(" 
              << transformed.at(0,0)*transformed.at(0,0) + 
                 transformed.at(1,0)*transformed.at(1,0)
              << ") ≈ 1.0\n";
    std::cout << "• The length is preserved by rotation\n";
    std::cout << "• New angle is 45 degrees from x-axis\n";

    return 0;
}
