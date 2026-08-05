#include <iostream>
#include <iomanip>

void addMatrix(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]);
void subMatrix(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]);
void mulMatrix(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]);
void transposeMatrix(const int matrix[3][3], int result[3][3]);
int detMatrix(const int matrix[3][3]);

int main() {

    int matrix1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int result[3][3];
    int det;


    std::cout << "A + B:\n";

    addMatrix(matrix1, matrix2, result);
    
    for(int i = 0; i < 3; i++){
        std::cout << "|";

        for(int j = 0; j < 3; j++){
            std::cout << std::setw(4)<< result[i][j];
        }

        std::cout << " |\n";
    }

    std::cout << "A - B:\n";

    subMatrix(matrix1, matrix2, result);
    
    for(int i = 0; i < 3; i++){
        std::cout << "|";

        for(int j = 0; j < 3; j++){
            std::cout << std::setw(4)<< result[i][j];
        }

        std::cout << " |\n";
    }

    std::cout << "A * B:\n";

    mulMatrix(matrix1, matrix2, result);
    
    for(int i = 0; i < 3; i++){
        std::cout << "|";

        for(int j = 0; j < 3; j++){
            std::cout << std::setw(4)<< result[i][j];
        }

        std::cout << " |\n";
    }

    std::cout << "At:\n";

    transposeMatrix(matrix1, result);
    
    for(int i = 0; i < 3; i++){
        std::cout << "|";

        for(int j = 0; j < 3; j++){
            std::cout << std::setw(4)<< result[i][j];
        }

        std::cout << " |\n";
    }

    std::cout << "|A|:\n";

    det = detMatrix(matrix1);
    
    std::cout << det << '\n';

    return 0;
}
void addMatrix(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
           result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}
void subMatrix(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
           result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}
void mulMatrix(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            int sum = 0;
            for(int k = 0; k < 3; k++){
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }
}
void transposeMatrix(const int matrix[3][3], int result[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
           result[j][i] = matrix[i][j];
        }
    }
}
int detMatrix(const int matrix[3][3]){
    int diagonal1 = matrix[0][0] * matrix[1][1] * matrix[2][2];
    int diagonal2 = matrix[0][1] * matrix[1][2] * matrix[2][0];
    int diagonal3 = matrix[0][2] * matrix[1][0] * matrix[2][1];

    int positive = diagonal1 + diagonal2 + diagonal3;

    int diagonal4 = matrix[0][2] * matrix[1][1] * matrix[2][0];
    int diagonal5 = matrix[0][0] * matrix[1][2] * matrix[2][1];
    int diagonal6 = matrix[0][1] * matrix[1][0] * matrix[2][2];

    int negative = diagonal4 + diagonal5 + diagonal6;

    return positive - negative;
}