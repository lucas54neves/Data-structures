#include <iostream>

using namespace std;

bool VerificaNuloNegativo(int num) {
    if (num <= 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int valor, vetor[10];
    for (int i = 0; i < 10; ++i) {
        cin >> valor;
        vetor[i] = valor;
    }

    for (int i = 0; i < 10; ++i) {
        if (not VerificaNuloNegativo(vetor[i])) {
            cout << vetor[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
