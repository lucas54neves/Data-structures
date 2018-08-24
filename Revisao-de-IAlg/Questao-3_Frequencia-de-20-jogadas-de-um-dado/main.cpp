#include <iostream>

using namespace std;

int main() {
    int jogadas[20], resultado;
    for (int i = 0; i < 20; ++i) {
        cin >> resultado;
        jogadas[i] = resultado;
    }
    
    float total[6], frequencia[6];
    for (int i = 0; i < 6; ++i) {
        total[i] = 0;
    }
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (jogadas[j] == (i + 1)) {
                total[i] = total[i] + 1;
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        frequencia[i] = (total[i] / 20.0);
    }
    
    for (int i = 0; i < 6; ++i) {
        cout << (i + 1) << ": " << frequencia[i] << endl;
    }
    
    return 0;
}
