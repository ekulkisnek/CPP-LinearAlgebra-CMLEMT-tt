#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/linalg.hpp"
#include <gtest/gtest.h>
#include <cmath>

class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code
    }
};

TEST_F(MatrixTest, MatrixConstruction) {
    Matrix<double> m(2, 2);
    EXPECT_EQ(m.get_rows(), 2);
    EXPECT_EQ(m.get_cols(), 2);
    EXPECT_EQ(m.at(0, 0), 0.0);
}

TEST_F(MatrixTest, MatrixMultiplication) {
    Matrix<double> A(2, 2);
    A.at(0, 0) = 1; A.at(0, 1) = 2;
    A.at(1, 0) = 3; A.at(1, 1) = 4;

    Matrix<double> B(2, 2);
    B.at(0, 0) = 5; B.at(0, 1) = 6;
    B.at(1, 0) = 7; B.at(1, 1) = 8;

    Matrix<double> C = A * B;
    EXPECT_EQ(C.at(0, 0), 19);
    EXPECT_EQ(C.at(0, 1), 22);
    EXPECT_EQ(C.at(1, 0), 43);
    EXPECT_EQ(C.at(1, 1), 50);
}

TEST_F(MatrixTest, VectorOperations) {
    Vector<double> v(3);
    v.at(0) = 1;
    v.at(1) = 2;
    v.at(2) = 2;

    EXPECT_EQ(v.norm(), 3.0);
}

TEST_F(MatrixTest, LinearTransformations) {
    double angle = M_PI / 2.0; // 90 degrees
    Matrix<double> rot = linalg::rotation_z(angle);
    
    Vector<double> v(3);
    v.at(0) = 1;
    v.at(1) = 0;
    v.at(2) = 0;

    Matrix<double> v_matrix(3, 1);
    for (size_t i = 0; i < 3; ++i) {
        v_matrix.at(i, 0) = v.at(i);
    }

    Matrix<double> result = rot * v_matrix;
    
    EXPECT_NEAR(result.at(0, 0), 0.0, 1e-10);
    EXPECT_NEAR(result.at(1, 0), 1.0, 1e-10);
    EXPECT_NEAR(result.at(2, 0), 0.0, 1e-10);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
