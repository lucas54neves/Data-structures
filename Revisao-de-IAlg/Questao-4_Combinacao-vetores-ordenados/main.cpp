#include <iostream>

using namespace std;

int main() {
    int vetor1[5], vetor2[5], vetor3[10];
    for (int i = 0; i < 5; ++i) {
        cin >> vetor1[i];
    }
    for (int i = 0; i < 5; ++i) {
        cin >> vetor2[i];
    }
    
    int i1 = 0, i2 = 0;
    for (int i = 0; i < 10; ++i) {
        if (vetor1[i1] <= vetor2[i2]) {
            vetor3[i] = vetor1[i1];
            ++i1;
        } else {
            vetor3[i] = vetor2[i2];
            ++i2;
        }
    }
    
    for (int i = 0; i < 10; ++i) {
        cout << vetor3[i];
        if (i < 9) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
    
    return 0;
}
