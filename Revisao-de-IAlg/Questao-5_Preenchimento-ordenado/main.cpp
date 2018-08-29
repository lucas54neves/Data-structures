#include <iostream>

using namespace std;

void ImprimeVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        cout << vetor[i];
        if (i < (tamanho - 1)) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}

int main() {
    int vetor[8], valor, tamanho = 0;
    for (int i = 0; i < 8; ++i) {
        cin >> valor;
        if (tamanho == 0) {
            vetor[0] = valor;
            ++tamanho;
        } else {
            for (int j = 0; j < tamanho; ++j) {
                if (valor < vetor[j]) {
                    for (int k = tamanho; k > j; --j) {
                        vetor[k] = vetor[k-1];
                    }
                }
                vetor[j] = valor;
                j = tamanho;
            }
            ++tamanho;
        }
        ImprimeVetor(vetor, tamanho);
    }
    return 0;
}
