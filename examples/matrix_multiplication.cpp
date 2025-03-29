#include <iostream>
#include <vector>

void matrixMultiply(const std::vector<std::vector<int>>& A, 
                   const std::vector<std::vector<int>>& B,
                   std::vector<std::vector<int>>& C) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Example matrices
    std::vector<std::vector<int>> A = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> B = {{7, 8}, {9, 10}, {11, 12}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2));

    matrixMultiply(A, B, C);

    // Print result
    for (const auto& row : C) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}