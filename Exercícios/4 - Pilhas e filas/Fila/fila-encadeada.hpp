#ifndef FILA_ENCADEADA_HPP
#define FILA_ENCADEADA_HPP

#include "noh.hpp"

typedef int Dado;

class Fila {
    public:
        Fila();
        ~Fila();
        bool Vazia();
        void Enfileirar(Dado d);
        Dado Desenfileirar();
        Dado PrimeiroElemento();
        Dado UltimoElemento();
        unsigned int Tamanho();
    private:
        Noh* mPrimeiro;
        Noh* mUltimo;
        unsigned int mTamanho;
        void RemoverTodos();
};

#endif // FILA-ENCADEAD_HPP
