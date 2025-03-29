#include <iostream>
#include "matrix.h"

int main() {
    // Define input matrices
    Matrix A(4, 4);
    Matrix B(4, 4);
    
    // Initialize matrices with sample values
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            A.set(i, j, i + j);
            B.set(i, j, i * j);
        }
    }
    
    // Perform matrix multiplication
    Matrix C = A * B;
    
    // Print result
    std::cout << "Result Matrix C:" << std::endl;
    C.print();
    
    return 0;
}