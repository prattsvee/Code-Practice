#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Function to generate a random integer between 1 and max
int randomInt(int max) {
    return rand() % max + 1;
}

// Function to create an n x n matrix filled with random integers
std::vector<std::vector<int>> generateRandomMatrix(int n, int max) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = randomInt(max);
        }
    }
    return matrix;
}

// Function to print a matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int num : row) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }
}

// Function to perform standard matrix multiplication
std::vector<std::vector<int>> standardMatrixMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Function to add two matrices
std::vector<std::vector<int>> matrixAdd(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Function to subtract two matrices
std::vector<std::vector<int>> matrixSubtract(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Function to perform Strassen's matrix multiplication
std::vector<std::vector<int>> strassenMatrixMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();

    // Base case: If the matrix size is 1x1, just multiply the elements
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // Divide matrices into four submatrices
    int halfSize = n / 2;
    std::vector<std::vector<int>> A11(halfSize, std::vector<int>(halfSize));
    std::vector<std::vector<int>> A12(halfSize, std::vector<int>(halfSize));
    std::vector<std::vector<int>> A21(halfSize, std::vector<int>(halfSize));
    std::vector<std::vector<int>> A22(halfSize, std::vector<int>(halfSize));

    std::vector<std::vector<int>> B11(halfSize, std::vector<int>(halfSize));
    std::vector<std::vector<int>> B12(halfSize, std::vector<int>(halfSize));
    std::vector<std::vector<int>> B21(halfSize, std::vector<int>(halfSize));
    std::vector<std::vector<int>> B22(halfSize, std::vector<int>(halfSize));

    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + halfSize];
            A21[i][j] = A[i + halfSize][j];
            A22[i][j] = A[i + halfSize][j + halfSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + halfSize];
            B21[i][j] = B[i + halfSize][j];
            B22[i][j] = B[i + halfSize][j + halfSize];
        }
    }

    // Compute intermediate matrices
    std::vector<std::vector<int>> M1 = strassenMatrixMultiply(matrixAdd(A11, A22), matrixAdd(B11, B22));
    std::vector<std::vector<int>> M2 = strassenMatrixMultiply(matrixAdd(A21, A22), B11);
    std::vector<std::vector<int>> M3 = strassenMatrixMultiply(A11, matrixSubtract(B12, B22));
    std::vector<std::vector<int>> M4 = strassenMatrixMultiply(A22, matrixSubtract(B21, B11));
    std::vector<std::vector<int>> M5 = strassenMatrixMultiply(matrixAdd(A11, A12), B22);
    std::vector<std::vector<int>> M6 = strassenMatrixMultiply(matrixSubtract(A21, A11), matrixAdd(B11, B12));
    std::vector<std::vector<int>> M7 = strassenMatrixMultiply(matrixSubtract(A12, A22), matrixAdd(B21, B22));

    // Calculate the submatrices of the result
    std::vector<std::vector<int>> C11 = matrixAdd(matrixSubtract(matrixAdd(M1, M4), M5), M7);
    std::vector<std::vector<int>> C12 = matrixAdd(M3, M5);
    std::vector<std::vector<int>> C21 = matrixAdd(M2, M4);
    std::vector<std::vector<int>> C22 = matrixAdd(matrixAdd(matrixSubtract(M1, M2), M3), M6);

    // Combine submatrices to get the result
    std::vector<std::vector<int>> result(n, std::vector<int>(n));
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            result[i][j] = C11[i][j];
            result[i][j + halfSize] = C12[i][j];
            result[i + halfSize][j] = C21[i][j];
            result[i + halfSize][j + halfSize] = C22[i][j];
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " n" << std::endl;
        return 1;
    }
	int myMAX;
    int n = std::atoi(argv[1]);
    int sqrt_myMAX = static_cast<int>(std::sqrt(myMAX/n)); // Calculate the square root of INT_MAX
    int max_random = sqrt_myMAX; // Use the square root value
    
    if ((n & (n - 1)) != 0) {
        std::cerr << "Error: n should be a power of 2." << std::endl;
        return 1;
    }

	srand(static_cast<unsigned>(time(nullptr))); // Seed for random number generation


    std::vector<std::vector<int>> A = generateRandomMatrix(n, max_random);
    std::vector<std::vector<int>> B = generateRandomMatrix(n, max_random);

    std::cout << "Matrix A:\n";
    printMatrix(A);
    std::cout << "Matrix B:\n";
    printMatrix(B);

    std::cout << "Standard Matrix Multiplication A*B:\n";
    std::vector<std::vector<int>> standardResult = standardMatrixMultiply(A, B);
    printMatrix(standardResult);

    std::cout << "Strassen's Matrix Multiplication A*B:\n";
    std::vector<std::vector<int>> strassenResult = strassenMatrixMultiply(A, B);
    printMatrix(strassenResult);

    return 0;
}

