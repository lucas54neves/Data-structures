#include <iostream>

using namespace std;

typedef int Dado;

class Noh {
    friend class Pilha;
    public:
        Noh(Dado d) {
            mDado = d;
            mProximo = NULL;
        }
    private:
        Dado mDado;
        Noh* mProximo;
};

class Pilha {
    public:
        Pilha() {
            mTopo = NULL;
            mTamanho = 0;
        }
        
        ~Pilha() {
            LimparPilha();
        }
        
        void Empilhar(Dado d) {
            Noh* novo = new Noh(d);
            
            novo->mProximo = mTopo;
            mTopo = novo;
            
            ++mTamanho;
        }
        
        Dado Desempilhar() {
            Noh* deletado = mTopo;
            Dado removido = deletado->mDado;
            
            mTopo = mTopo->mProximo;
            
            delete deletado;
            --mTamanho;
            
            return removido;
        }
        
        bool Vazia() {
            return mTamanho == 0;
        }
        
        Dado Espiar() {
            if (not Vazia()) {
                return mTopo->mDado;
            } else {
                cout << "Pilha vazia" << endl;
                return -1;
            }
        }
    private:
        Noh* mTopo;
        unsigned int mTamanho;
        void LimparPilha() {
            while (mTopo != NULL) {
                Noh* removido = mTopo;
                mTopo = mTopo->mProximo;
                delete removido;
                --mTamanho;
            }
            mTopo = NULL;
        }
};

int main() {
    Pilha teste;
    for (Dado i = 0; i < 10; ++i) {
        teste.Empilhar(i);
    }
    
    for (Dado i = 0; i < 10; ++i) {
        cout << teste.Desempilhar() << " ";
    }
    cout << endl;
    
    return 0;
}
