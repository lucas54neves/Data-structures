#include <iostream>

using namespace std;

typedef int Data;

class MinHeap {
    public:
        MinHeap();
        ~MinHeap();
        void Inserir(Data d);
        void Imprimir();
        Data EspiarRaiz();
        Data RetirarRaiz();
    private:
        Data* mVetDados;
        unsigned int mTamanho;
        unsigned int mCapacidade;
        unsigned int Pai(unsigned int i);
        unsigned int Esquerdo(unsigned int i);
        unsigned int Direito(unsigned int i);
        void CorrigirSubindo(unsigned int i);
        void CorrigirDescendo(unsigned int i);
        void Arrumar();
};

MinHeap::MinHeap() {
    
}

MinHeap::~MinHeap() {
    
}
