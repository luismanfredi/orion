#include "orion/matrix.hpp"
#include <iostream>

int main() {
    Matrix A{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Matrix B(3, 3, 1.5);

    std::cout << "Matrix A:\n";
    std::cout << A << "\n\n";

    std::cout << "Rows A: " << A.rows() << "\n\n";
    std::cout << "Columns A: " << A.cols() << "\n\n";

    std::cout << "Matrix B:\n";
    std::cout << B << "\n\n";

    std::cout << "A + B:\n";
    std::cout << A + B << "\n\n";

    std::cout << "A * B:\n";
    std::cout << A * B << "\n\n";

    std::cout << "A * 2:\n";
    std::cout << A * 2 << "\n\n";

    std::cout << "Transpose A:\n";
    std::cout << A.transpose() << "\n";

    return 0;
}