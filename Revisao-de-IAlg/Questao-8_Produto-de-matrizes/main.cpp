#include <iostream>

using namespace std;

int main() {
    int matrizA[4][5], matrizB[5][2], matrizC[4][2];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> matrizA[i][j];
        }
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> matrizB[i][j];
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            matrizC[i][j] = 0;
        }
    }
    for (int linha = 0; linha < 4; ++linha) {
        for (int coluna = 0; coluna < 2; ++coluna) {
             matrizC[linha][coluna] = 0;
            for (int i = 0; i < 5; ++i) {
                matrizC[linha][coluna] = matrizC[linha][coluna] + matrizA[linha][i]*matrizB[i][coluna];
            }
        }
    }
        
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << matrizC[i][j];
            if (j == 1) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }
    
    return 0;
}
