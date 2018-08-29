#include <iostream>

using namespace std;

int main() {
    int linha, coluna;
    cin >> linha >> coluna;
    int matrizA[linha][coluna];
    for (int i = 0; i < linha; ++i) {
        for (int j = 0; j < coluna; ++j) {
            cin >> matrizA[i][j];
        }
    }
    
    int matrizB[coluna][linha];
    for (int i = 0; i < coluna; ++i) {
        for (int j = 0; j < linha; ++j) {
            matrizB[i][j] = matrizA[j][i];
        }
    }
    
    for (int i = 0; i < coluna; ++i) {
        for (int j = 0; j < linha; ++j) {
            cout << matrizB[i][j];
            if (j < (linha - 1)) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    }
    
    return 0;
}
