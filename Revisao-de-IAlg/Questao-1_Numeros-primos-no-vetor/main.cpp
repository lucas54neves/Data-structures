#include <iostream>

using namespace std;

bool VerificaPrimo(int num) {
    if (num <= 2) {
        return true;
    } else {
        for (int i = 2; i < num; ++i) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
}

int main() {
    int valor, vetor[9];
    for (int i = 0; i < 9; ++i) {
        cin >> valor;
        vetor[i] = valor;
    }
    
    for (int i = 0; i < 9; ++i) {
        if (VerificaPrimo(vetor[i])) {
            cout << vetor[i] << " " << i << endl;
        }
    }
    
    return 0;
}
