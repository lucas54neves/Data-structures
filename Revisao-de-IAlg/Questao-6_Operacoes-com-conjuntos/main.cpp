#include <iostream>

using namespace std;

int main() {
    int tam1, tam2;
    cin >> tam1 >> tam2;
    int vetor1[tam1], vetor2[tam2];
    for (int i = 0; i < tam1; ++i) {
        cin >> vetor1[i];
    }
    for (int i = 0; i < tam2; ++i) {
        cin >> vetor2[i];
    }
    
    // Interceção
    for (int i = 0; i < tam1; ++i) {
        for (int j = 0; j < tam2; ++j) {
            if (vetor1[i] == vetor2[j]) {
                cout << vetor1[i] << " ";
            }
        }
    }
    cout << endl;
    
    // União
    for (int i = 0; i < tam1; ++i) {
         cout << vetor1[i] << " ";
    }
    bool existe = false;
    for (int i = 0; i < tam2; ++i) {
        for (int j = 0; j < tam1; ++j) {
            if (vetor2[i] == vetor1[j]) {
                existe = true;
            }
        }
        if (not existe) {
            cout << vetor2[i] << " ";
        }
        existe = false;
    }
    cout << endl;
    
    return 0;
}
