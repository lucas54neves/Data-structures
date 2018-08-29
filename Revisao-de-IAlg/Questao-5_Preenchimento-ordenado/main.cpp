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
    int vetor[8], valor, tamanho = 1, pos;
    bool naoAchou;
    cin >> vetor[0];
    ImprimeVetor(vetor, tamanho);
    for (int i = 0; i < 7; ++i) {
        cin >> valor;
        pos = 0;
        naoAchou = true;
        while (naoAchou) {
            if (vetor[pos] > valor) {
                naoAchou = false;
            } else {
                ++pos;
            }
        }
        for (int j = tamanho; j > pos; --j) {
            vetor[j] = vetor[j-1];
        }
        vetor[pos] = valor;
        ++tamanho;
        ImprimeVetor(vetor, tamanho);
    }
    return 0;
}
