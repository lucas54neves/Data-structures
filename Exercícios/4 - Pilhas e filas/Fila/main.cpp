#include <iostream>
#include "fila-encadeada.hpp"
#include "noh.hpp"

using namespace std;

int main() {
    Fila teste;
    
    for (Dado i = 0; i < 15; ++i) {
        teste.Enfileirar(i);
    }
    
    cout << "Primeiro elemento: " << teste.PrimeiroElemento() << endl;
    cout << "Último elemento: " << teste.UltimoElemento() << endl;
    cout << "Tamanho: " << teste.Tamanho() << endl;
    
    for (Dado i = 0; i < 15; ++i) {
        cout << teste.Desenfileirar() << " ";
    }
    cout << endl;
    
    return 0;
}
