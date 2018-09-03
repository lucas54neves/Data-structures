
 // Função retorna um valor
 // Procedimento altera o estado, não retorna um valor
 // Funções: o nome descreve o resultado
 // Procedimentos: o nome é um verbo no infinitivo (ou imperativo) que descreve a ação

#include <iostream>
#include "vetor-expansivel.hpp"

using namespace std;

int main () {
    unsigned capacidade;
    cout << "Entre com a capacidade do vetor" << endl;
    cin >> capacidade;
    Vetor vetor1(capacidade), vetor2(capacidade);
    data valor;

    for (unsigned i = 0; i < capacidade; ++i) {
        cout << "Entre com o valor para o vetor" << endl;
        cin >> valor;
        vetor1.AlteraValor(i, valor);
    }
    
    for (unsigned i = 0; i < capacidade; ++i) {
        cout << "Entre com o valor para o vetor" << endl;
        cin >> valor;
        vetor2.AlteraValor(i, valor);
    }
    
    valor = vetor1 * vetor2;
    cout << valor << endl;

    return 0;
}
