#include <iostream>

using namespace std;

int main() {
    int matriz[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cin >> matriz[i][j];
        }
    }
    int maior = matriz[0][0], linha = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (matriz[i][j] > maior) {
                maior = matriz[i][j];
                linha = i;
            }
        }
    }
    int menor = matriz[linha][0], coluna = 0;
    for (int i = 0; i < 10; ++i) {
        if (matriz[linha][i] < menor) {
            menor = matriz[linha][i];
            coluna = i;
        }
    }
    
    cout << menor << endl;
    cout << linha << " " << coluna << endl;
    
    return 0;
}
