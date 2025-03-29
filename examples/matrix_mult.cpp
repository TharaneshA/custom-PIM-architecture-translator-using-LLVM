#include <iostream>
#include <vector>

void matrixMultiply(const std::vector<std::vector<int>>& A, 
                   const std::vector<std::vector<int>>& B,
                   std::vector<std::vector<int>>& C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    const int N = 16;
    std::vector<std::vector<int>> A(N, std::vector<int>(N));
    std::vector<std::vector<int>> B(N, std::vector<int>(N));
    std::vector<std::vector<int>> C(N, std::vector<int>(N, 0));
    
    // Initialize matrices with different patterns
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) % 10;  // Diagonal pattern
            B[i][j] = (i * j) % 7;   // Checkerboard-like pattern
        }
    }
    
    matrixMultiply(A, B, C, N);
    
    // Print result
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}