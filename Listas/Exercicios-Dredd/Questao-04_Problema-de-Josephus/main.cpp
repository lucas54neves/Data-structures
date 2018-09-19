#include <iostream>

using namespace std;

typedef unsigned int dado;

class Pessoa {
    friend class Circulo;
    public:
        Pessoa(dado d = 0);
    private:
        const dado mDado;
        Pessoa* mProxima;
};

Pessoa::Pessoa(dado d) : mDado(d) {
    mProxima = NULL;
}

class Circulo {
    public:
        Circulo();
        ~Circulo();
        void AlgoritmoJosephus(unsigned int qtdPessoas, unsigned int qtdAvancos);
        void Inserir(unsigned int d);
        bool Vazio();
    private:
        Pessoa* mPrimeira;
        Pessoa* mUltima;
        unsigned int mTamanho;
        void RemoverTodos();
};

Circulo::Circulo() {
    mPrimeira = NULL;
    mUltima = NULL;
    mTamanho = 0;
}

Circulo::~Circulo() {
    RemoverTodos();
}

void Circulo::RemoverTodos() {
    mPrimeira = NULL;
    mUltima = NULL;
    mTamanho = 0;
}

bool Circulo::Vazio() {
    return (mTamanho == 0);
}

void Circulo::Inserir(dado d) {
    Pessoa* nova = new Pessoa(d);
    if (Vazio()) {
        mPrimeira = nova;
        mUltima = nova;
    } else {
        mUltima->mProxima = nova;
        mUltima = nova;
    }
    ++mTamanho;
}

void Circulo::AlgoritmoJosephus(unsigned int qtdPessoas, unsigned int qtdAvancos) {
    for (unsigned int i = 1; i <= qtdPessoas; ++i) {
        Inserir(i);
    }
    mUltima->mProxima = mPrimeira;
    
    if (not Vazio()) {
        Pessoa* inter = mPrimeira;
        Pessoa* antInter = mPrimeira;
        Pessoa* removida = NULL;
        
        while (mTamanho > 1) {
            for (unsigned int i = 0; i < qtdAvancos; ++i) {
                antInter = inter;
                inter = inter->mProxima;
            }
            
            removida = inter;
            antInter->mProxima = inter->mProxima;
            inter = inter->mProxima;
            
            delete removida;
            --mTamanho;
        }
        
        cout << inter->mDado << endl;
    }
}

int main() {
    Circulo circuloSoldados;
    unsigned int qtdPessoas, qtdAvancos;
    cin >> qtdPessoas >> qtdAvancos;
    circuloSoldados.AlgoritmoJosephus(qtdPessoas, qtdAvancos);
    
    return 0;
}
