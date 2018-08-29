#include <iostream>

using namespace std;

int main() {
    int matriz[10][10], aux[10][10], vetor[10];
    
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cin >> matriz[i][j];
        }
    }
    
    // Cópia para a matriz auxiliar
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            aux[i][j] = matriz[i][j];
        }
    }
    // 1. a linha 2 com a linha 8
    for (int i = 0; i < 10; ++i) {
        vetor[i] = aux[1][i];
        aux[1][i] = aux[7][i];
        aux[7][i] = vetor[i];
    }
    // Impressão da matriz
    cout << "1." << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << aux[i][j];
            if (j == 9) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }
    
    // Cópia para a matriz auxiliar
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            aux[i][j] = matriz[i][j];
        }
    }
    // 2. a coluna 4 com a coluna 10
    for (int i = 0; i < 10; ++i) {
        vetor[i] = aux[i][3];
        aux[i][3] = aux[i][9];
        aux[i][9] = vetor[i];
    }
    // Impressão da matriz
    cout << "2." << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << aux[i][j];
            if (j == 9) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }
    
    // Cópia para a matriz auxiliar
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            aux[i][j] = matriz[i][j];
        }
    }
    int principal[10], secundaria[10];
    // 3. a diagonal principal com a diagonal secundária
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == j) {
                principal[i] = matriz[i][j];
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i + j == 9) {
                secundaria[i] = matriz[i][j];
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == j) {
                aux[i][j] = secundaria[i];
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i + j == 9) {
                aux[i][j] = principal[i];
            }
        }
    }
    // Impressão da matriz
    cout << "3." << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << aux[i][j];
            if (j == 9) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }
    
    // Cópia para a matriz auxiliar
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            aux[i][j] = matriz[i][j];
        }
    }
    // 4. a linha 5 com a coluna 10
    for (int i = 0; i < 10; ++i) {
        vetor[i] = aux[4][i];
        aux[4][i] = aux[i][9];
        aux[i][9] = vetor[i];
    }
    // Impressão da matriz
    cout << "4." << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << aux[i][j];
            if (j == 9) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }
    
    return 0;
}
