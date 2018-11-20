#include <iostream>
#include "vetor-expansivel.hpp"

using namespace std;

// Construtor padrão
Vetor::Vetor(unsigned capacidade)
    : mVetDados(new data[capacidade]),
    mTamanho(capacidade),
    mCapacidade(capacidade) { // inicializacao
}

// Construtor de cópia
Vetor::Vetor(Vetor& vet) {
    mTamanho = vet.mTamanho;
    mCapacidade = 0;
    mVetDados = new data[mTamanho];
    for (unsigned i = 0; i < mTamanho; ++i) {
        mVetDados[i] = vet.mVetDados[i];
    }
}

// Destrutor
Vetor::~Vetor() {
    delete[] mVetDados;
    mTamanho = 0;
    mCapacidade = 0;
}

// Retorna o valor de uma posição dada
data Vetor::Valor(unsigned pos) {
    data valor = mVetDados[pos];
    return valor;
}

// Verifica se um valor existe no vetor
bool Vetor::Existe(data valor) {
    for (unsigned i = 0; i < mTamanho; ++i) {
        if (mVetDados[i] == valor) {
            return true;
        }
    }
    return false;
}

// Altera um valor de uma posição dada
void Vetor::AlteraValor(unsigned pos, data valor) {
    mVetDados[pos] = valor;
}

// Retorna uma posição de um valor dado
unsigned Vetor::Posicao(data valor) {
    if (Existe(valor)) {
        for (unsigned i = 0; i < mTamanho; ++i) {
            if (mVetDados[i] == valor) {
                return i;
            }
        }
    }
}

// Ordena o vetor com o método QuickSort
void Vetor::OrdenaVetor(unsigned inicio, unsigned fim) {
    unsigned i, j;
    data pivo, aux;
    i = inicio;
    j = fim - 1;
    pivo = mVetDados[(inicio + fim) / 2];
    
    while (i <= j) {
        while (mVetDados[i] < pivo && i < fim) {
            i++;
        }
        
        while (mVetDados[j] > pivo && j > inicio) {
            j--;
        }
        
        if (i <= j) {
            aux = mVetDados[i];
            mVetDados[i] = mVetDados[j];
            mVetDados[j] = aux;
            i++;
            j--;
        }
        
        if (j > inicio) {
            OrdenaVetor(inicio, j + 1);
        }
        
        if (i < fim) {
            OrdenaVetor(i, fim);
        }
    }
}

// Sobrecarga do operador * para o produto interno entre dois vetores
data Vetor::operator*(const Vetor& outroVetor) {
    data resultado = 0;
    for (unsigned i = 0; i < mTamanho; ++i) {
        resultado = resultado + (mVetDados[i] * outroVetor.mVetDados[i]);
    }
    return resultado;
}
        
// Sobrecarga do operador * para a multiplicação do vetor por um número
Vetor& Vetor::operator*(const data& num) {
    for (unsigned i = 0; i < mTamanho; ++i) {
        mVetDados[i] = mVetDados[i] * num;
    }
    return *this;
}

// Remove os valores duplicados do vetor
void Vetor::RemoveDuplicados() {
    for (unsigned pos1 = 0; pos1 < mTamanho; pos1++) {
        for (unsigned pos2 = pos1 + 1; pos2 < mTamanho; pos2++) {
            if (mVetDados[pos1] == mVetDados[pos2]) {
                RemoveValor(pos2);
            }
        }
    }
}

// Remove o valor de uma posição dada
void Vetor::RemoveValor(unsigned pos) {
    MoveEsquerda(pos);
    mTamanho--;
    mCapacidade++;
}

// Sobrecarga do operador - para a implementação da diferença de vetores
Vetor& Vetor::operator-(const Vetor& outroVetor) {
    for (unsigned pos1 = 0; pos1 < mTamanho; pos1++) {
        for (unsigned pos2 = 0; pos2 < outroVetor.mTamanho; pos2++) {
            if (mVetDados[pos1] == outroVetor.mVetDados[pos2]) {
                RemoveValor(pos1);
            }
        }
    }
    return *this;
}

// Redimensionamento do vetor
void Vetor::Redimensionamento() {
    data* aux = new data[mTamanho * 2];
    for (unsigned i = 0; i < mTamanho; i++) {
        aux[i] = mVetDados[i];
    }
    delete[] mVetDados;
    mCapacidade = mTamanho * 2;
    mVetDados = aux;
}
        
// Verifica se o vetor está cheio
bool Vetor::Cheio() {
    if (mCapacidade == 0) {
        return true;
    } else {
        return false;
    }
}

// Insere no início do vetor
void Vetor::InsereInicio(data valor) {
    MoveDireita(0);
    mVetDados[0] = valor;
    ++mTamanho;
    mCapacidade--;
}

// Insere no final do vetor
void Vetor::InsereFinal(data valor) {
    mVetDados[mTamanho] = valor;
    ++mTamanho;
    mCapacidade--;
}

// Insere um valor em uma dada posição do vetor
void Vetor::InserePos(unsigned pos, data valor) {
    if (Cheio()) {
        Redimensionamento();
    }
    if (pos == 0) {
        InsereInicio(valor);
    } else if (pos == mTamanho) {
        InsereFinal(valor);
    } else {
        MoveDireita(pos);
        mVetDados[pos] = valor;
        mTamanho++;
        mCapacidade--;
    }
}

// Move os valores à direita de uma posição
void Vetor::MoveDireita(unsigned pos) {
    for (unsigned i = mTamanho; i > pos; --i) {
        mVetDados[i] = mVetDados[i-1];
    }
}

// Move os valores à esquerda de uma posição
void Vetor::MoveEsquerda(unsigned pos) {
    for (unsigned i = pos; i < (mTamanho - 1); ++i) {
        mVetDados[i] = mVetDados[i+1];
    }
}

// Retorna o tamanho do vetor
unsigned Vetor::Tamanho() {
    return mTamanho;
}

// Imprime o vetor
void Vetor::Imprime() {
    cout << "Vetor = [";
    for (unsigned i = 0; i < mTamanho; ++i) {
        cout << mVetDados[i];
        if (i != mTamanho - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}
