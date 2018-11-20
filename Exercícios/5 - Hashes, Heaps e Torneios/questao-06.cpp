#include <iostream>

using namespace std;

typedef int Data;

class MinHeap {
    public:
        MinHeap(Data vet[], int tam);
        ~MinHeap();
        void Imprimir(int pos);
    private:
        Data* mVetDados;
        int mTamanho;
        int mCapacidade;
        int Pai(int i);
        int Esquerdo(int i);
        int Direito(int i);
        void CorrigirDescendo(int i);
        void Arrumar();
};

MinHeap::MinHeap(Data vet[], int tam) {
    mTamanho = tam;
    mVetDados = new Data[tam];
    
    for (int i = 0; i < mTamanho; ++i) {
        mVetDados[i] = vet[i];
    }
    
    Arrumar();
}

MinHeap::~MinHeap() {
    delete[] mVetDados;
}

int MinHeap::Pai(int i) {
    return (i-1)/2;
}

int MinHeap::Esquerdo(int i) {
    return (2*i+1);
}

int MinHeap::Direito(int i) {
    return (2*i+2);
}

void MinHeap::Arrumar() {
    for (int i = (mTamanho/2-1); i >= 0; --i) {
        CorrigirDescendo(i);
        Imprimir(i);
    }
}

void MinHeap::CorrigirDescendo(int i) {
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int menor;
    
    if (esq < mTamanho && mVetDados[esq] < mVetDados[i]) {
        menor = esq;
    } else {
        menor = i;
    }
    
    if (dir < mTamanho && mVetDados[dir] < mVetDados[menor]) {
        menor = dir;
    }
    
    if (menor != i) {
        swap(mVetDados[menor], mVetDados[i]);
        CorrigirDescendo(menor);
    }
}

void MinHeap::Imprimir(int pos) {
    cout << pos << ": ";
    for (int i = 0; i < mTamanho; ++i) {
        cout << mVetDados[i];
        
        if (i < mTamanho - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}

int main() {
    int tam;
    cin >> tam;
    
    int vet[tam];
    for (int i = 0; i < tam; ++i) {
        cin >> vet[i];
    }
    
    MinHeap(vet, tam);
}
