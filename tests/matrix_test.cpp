
#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/linalg.hpp"
#include <gtest/gtest.h>
#include <cmath>

/**
 * EDUCATIONAL TEST SUITE
 * 
 * This file demonstrates:
 * 1. Unit Testing Principles
 * 2. Test-Driven Development (TDD)
 * 3. Matrix Operations Verification
 * 4. Linear Algebra Property Testing
 * 
 * TESTING CONCEPTS:
 * - Each test should verify one specific behavior
 * - Tests should be independent and repeatable
 * - Edge cases should be considered
 * - Use descriptive test names
 */
class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code runs before each test
        // Good practice: Initialize commonly used objects here
    }
};

/**
 * TEST CASE: Matrix Construction
 * 
 * Verifies:
 * 1. Correct dimension initialization
 * 2. Default value initialization
 * 3. Memory allocation success
 */
TEST_F(MatrixTest, MatrixConstruction) {
    Matrix<double> m(2, 2);
    EXPECT_EQ(m.get_rows(), 2) << "Matrix should have 2 rows";
    EXPECT_EQ(m.get_cols(), 2) << "Matrix should have 2 columns";
    EXPECT_EQ(m.at(0, 0), 0.0) << "Default value should be 0.0";
}

/**
 * TEST CASE: Matrix Multiplication
 * 
 * Verifies:
 * 1. Basic matrix multiplication
 * 2. Mathematical correctness
 * 3. Dimensional compatibility
 * 
 * Mathematical Background:
 * [1 2] × [5 6] = [19 22]
 * [3 4]   [7 8]   [43 50]
 */
TEST_F(MatrixTest, MatrixMultiplication) {
    // Create first matrix
    Matrix<double> A(2, 2);
    A.at(0, 0) = 1; A.at(0, 1) = 2;
    A.at(1, 0) = 3; A.at(1, 1) = 4;

    // Create second matrix
    Matrix<double> B(2, 2);
    B.at(0, 0) = 5; B.at(0, 1) = 6;
    B.at(1, 0) = 7; B.at(1, 1) = 8;

    // Perform multiplication and verify results
    Matrix<double> C = A * B;
    EXPECT_EQ(C.at(0, 0), 19) << "First element of product incorrect";
    EXPECT_EQ(C.at(0, 1), 22) << "Second element of product incorrect";
    EXPECT_EQ(C.at(1, 0), 43) << "Third element of product incorrect";
    EXPECT_EQ(C.at(1, 1), 50) << "Fourth element of product incorrect";
}

/**
 * TEST CASE: Vector Operations
 * 
 * Verifies:
 * 1. Vector norm calculation
 * 2. Pythagorean theorem application
 * 3. Basic vector properties
 * 
 * Mathematical Background:
 * For vector (1,2,2), norm = √(1² + 2² + 2²) = √9 = 3
 */
TEST_F(MatrixTest, VectorOperations) {
    Vector<double> v(3);
    v.at(0) = 1;  // x component
    v.at(1) = 2;  // y component
    v.at(2) = 2;  // z component

    EXPECT_EQ(v.norm(), 3.0) << "Vector norm calculation incorrect";
}

/**
 * TEST CASE: Linear Transformations
 * 
 * Verifies:
 * 1. Rotation matrix properties
 * 2. Transformation accuracy
 * 3. Trigonometric calculations
 * 
 * This test rotates (1,0,0) by 90° around Z-axis,
 * expecting result (0,1,0)
 */
TEST_F(MatrixTest, LinearTransformations) {
    double angle = M_PI / 2.0; // 90 degrees
    Matrix<double> rot = linalg::rotation_z(angle);
    
    Vector<double> v(3);
    v.at(0) = 1; // Point on x-axis
    v.at(1) = 0;
    v.at(2) = 0;

    // Convert vector to matrix for multiplication
    Matrix<double> v_matrix(3, 1);
    for (size_t i = 0; i < 3; ++i) {
        v_matrix.at(i, 0) = v.at(i);
    }

    // Apply rotation
    Matrix<double> result = rot * v_matrix;
    
    // Verify rotation results with small error tolerance
    EXPECT_NEAR(result.at(0, 0), 0.0, 1e-10) << "X coordinate after rotation";
    EXPECT_NEAR(result.at(1, 0), 1.0, 1e-10) << "Y coordinate after rotation";
    EXPECT_NEAR(result.at(2, 0), 0.0, 1e-10) << "Z coordinate after rotation";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
