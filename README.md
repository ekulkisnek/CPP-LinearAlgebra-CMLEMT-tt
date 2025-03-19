# Educational Linear Algebra in C++

This project serves as an educational resource for learning both C++ programming and linear algebra concepts. It implements fundamental linear algebra operations with a focus on clean code, performance, and mathematical accuracy.

## Educational Goals

1. C++ Programming Concepts
   - Template programming
   - RAII (Resource Acquisition Is Initialization)
   - Operator overloading
   - Memory management
   - Modern C++ features

2. Linear Algebra Concepts
   - Matrix operations
   - Vector spaces
   - Linear transformations
   - Gaussian elimination
   - System of linear equations

## Project Structure

- `include/`: Header files containing class implementations
  - `matrix.hpp`: Template matrix class
  - `vector.hpp`: Mathematical vector implementation
  - `linalg.hpp`: Linear algebra utilities

- `examples/`: Example programs demonstrating usage
  - `matrix_operations.cpp`: Basic matrix operations
  - `linear_transformations.cpp`: 3D transformations

- `tests/`: Unit tests
  - `matrix_test.cpp`: Comprehensive tests for all functionality

## Key Features

### Matrix Class
The `Matrix<T>` class provides:
- Dynamic memory allocation with RAII
- Basic matrix operations (addition, multiplication)
- Gaussian elimination
- Error checking and bounds validation

### Vector Class
The `Vector<T>` class implements:
- Dot product
- Vector norm
- Transformation operations

### Linear Algebra Utilities
The `linalg` namespace provides:
- 3D rotation matrices
- Linear system solver
- Common transformations

## Building and Running

1. Compile examples:
```bash
g++ -std=c++17 examples/matrix_operations.cpp -o matrix_ops
g++ -std=c++17 examples/linear_transformations.cpp -o linear_trans
