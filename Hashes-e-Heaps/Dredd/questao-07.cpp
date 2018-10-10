#include <iostream>

using namespace std;

typedef int Data;

class HeapSort {
    public:
        HeapSort(Data vet[], int tam = 15, int cap = 20);
        ~HeapSort();
        void Inserir(Data d);
        void Imprimir();
        void Arrumar();
        void Ordenar();
    private:
        Data* mVetDados;
        int mCapacidade;
        int mTamanho;
        int Pai(int i);
        int Esquerdo(int i);
        int Direito(int i);
        void CorrigirDescendo(int i);
        void CorrigirSubindo(int i);
};

HeapSort::HeapSort(Data vet[], int tam, int cap) {
    mCapacidade = cap;
    mTamanho = tam;
    mVetDados = new Data[mCapacidade];
    
    for (int i = 0; i < mTamanho; ++i) {
        mVetDados[i] = vet[i];
    }
    
    Arrumar();
}

HeapSort::~HeapSort() {
    delete[] mVetDados;
}

void HeapSort::Inserir(Data d) {
    if (mTamanho == mCapacidade) {
        cout << "Erro ao inserir" << endl;
    } else {
        mVetDados[mTamanho] = d;
        CorrigirSubindo(mTamanho);
        ++mTamanho;
    }
}

void HeapSort::Imprimir() {
    for (int i = 0; i < mTamanho; ++i) {
        cout << mVetDados[i];
        if (i < mTamanho - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}

int HeapSort::Pai(int i) {
    return (i-1)/2;
}

int HeapSort::Esquerdo(int i) {
    return (2*i+1);
}

int HeapSort::Direito(int i) {
    return (2*i+2);
}

void HeapSort::Arrumar() {
    for (int i = (mTamanho/2-1); i >= 0; --i) {
        CorrigirDescendo(i);
    }
}

void HeapSort::CorrigirDescendo(int i) {
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior;
    
    if (esq < mTamanho && mVetDados[i] < mVetDados[esq]) {
        maior = esq;
    } else {
        maior = i;
    }
    
    if (dir < mTamanho && mVetDados[maior] < mVetDados[dir]) {
        maior = dir;
    }
    
    if (maior != i) {
        swap(mVetDados[maior], mVetDados[i]);
        CorrigirDescendo(maior);
    }
}

void HeapSort::CorrigirSubindo(int i) {
    int pai = this->Pai(i);
    
    if (mVetDados[pai] < mVetDados[i]) {
        swap(mVetDados[pai], mVetDados[i]);
        CorrigirSubindo(pai);
    }
}

void HeapSort::Ordenar(int n) {
    for (int i = n; i > 1; --i) 
    { 
        swap(mVetDados[0], mVetDados[i]); 
        DescerParaOrdenar(1, i-1); 
    } 
}

int main() {
    Data vet[15];
    
    for (int i = 0; i < 15; ++i) {
        cin >> vet[i];
    }
    
    HeapSort *h = new HeapSort(vet);
    h->Imprimir();
    
    Data d;
    for (int i = 0; i < 5; ++i) {
        cin >> d;
        h->Inserir(d);
    }
    h->Imprimir();
    
    h->Ordenar();
    h->Imprimir();
    
    return 0;
}
