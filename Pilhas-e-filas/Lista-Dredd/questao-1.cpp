#include <iostream>

using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// pilha implementada em arranjo 
class PilhaV {
private:
    int mCapacidade;
    Dado *mDados;
    int mTamanho;
    int mPosTopo;
public:
    PilhaV(int cap = 100);
    ~PilhaV();
    void Empilhar(Dado valor);
    Dado Desempilhar();
    Dado Espiar(); // acessa elemento do topo, mas não retira
    void Depurar(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
    void Info();  // imprime informações da pilha (tamanho e  posição do topo)
};

PilhaV::PilhaV(int cap = 100) {
    mDados = new Dado[cap];
    mTamanho = 0;
    mCapacidade = cap;
    mPosTopo = 0;
}

PilhaV::~PilhaV() {
    while (mTamanho != 0) {
        --mPosTopo;
        --mTamanho;
        ++mCapacidade;
    }
    delete mDados[];
}

void PilhaV::Empilhar(Dado valor) {
    mDados[mPosTopo + 1] = valor
    ++mTamanho;
    --mCapacidade;
}

Dado PilhaV::Desempilhar() {
    --mPosTopo;
    return mDados[mPosTopo+1];
}

Dado PilhaV::Espiar() {
    return mDados[mPosTopo];
}

void PilhaV::Depurar() {
    for (int i = 0; i < mTamanho; ++i) {
        cout << mDados[i] << " ";
    }
    cout << endl;
}

void PilhaV::Info() {
    cout << mTamanho << " " << mPosTopo << endl;
}

int main() {
    PilhaV minhaPilha(20);
    Dado valor;
    
    for (int i = 0; i < 5; ++i) {
        cin >> valor;
        minhaPilha.Empilhar(valor);
    }
    
    for (int i = 0; i < 3; ++i) {
        cout << minhaPilha.Desempilhar(valor) << endl;
    }
    
    for (int i = 0; i < 4; ++i) {
        cin >> valor;
        minhaPilha.Empilhar(valor);
    }
    
    for (int i = 0; i < 3; ++i) {
        cout << minhaPilha.Desempilhar(valor) << endl;
    }
    
    cout << minhaPilha.Espiar() << endl;
    
    minhaPilha.Depurar();
    
    minhaPilha.Info();
    
    return 0;
}
