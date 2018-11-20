#include <iostream>
#include "fila-encadeada.hpp"
#include "noh.hpp"

Fila::Fila() {
    mPrimeiro = NULL;
    mUltimo = NULL;
    mTamanho = 0;
}

Fila::~Fila() {
    RemoverTodos();
}

bool Fila::Vazia() {
    return mPrimeiro == NULL;
}

void Fila::Enfileirar(Dado d) {
    Noh* novo = new Noh(d);
    
    if (Vazia()) {
        mPrimeiro = novo;
    } else {
        mUltimo->mProximo = novo;
    }
    mUltimo = novo;
    
    ++mTamanho;
}

Dado Fila::Desenfileirar() {
    Noh* deletado = mPrimeiro;
    Dado removido = mPrimeiro->mDado;
    
    mPrimeiro = mPrimeiro->mProximo;
    if (Vazia()) {
        mUltimo = NULL;
    }
    
    delete deletado;
    --mTamanho;
    return removido;
}

Dado Fila::PrimeiroElemento() {
    return mPrimeiro->mDado;
}

Dado Fila::UltimoElemento() {
    return mUltimo->mDado;
}

void Fila::RemoverTodos() {
    while (mPrimeiro != NULL) {
        Noh* deletado = mPrimeiro;
        mPrimeiro = mPrimeiro->mProximo;
        delete deletado;
        --mTamanho;
    }
    mUltimo = NULL;
}

unsigned Fila::Tamanho() {
    return mTamanho;
}
