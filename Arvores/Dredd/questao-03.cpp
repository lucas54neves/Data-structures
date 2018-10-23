#include <iostream>
#include <fstream>

using namespace std;

enum PosicaoInsercao {esquerda, direita};

class Posicao {
    friend class ListaPos;
    public:
        Posicao(int pos) {
            mPosicao = pos;
            mProxima = NULL;
        };
    private:
        int mPosicao;
        Posicao* mProxima;
};

class ListaPos {
    public:
        ListaPos() {
            mPrimeira = NULL;
            mUltima = NULL;
        };
        void Inserir(int pos) {
            Posicao* novo = new Posicao(pos);
            if (mPrimeira == NULL) {
                mPrimeira = novo;
                mUltima = novo;
            } else {
                mUltima->mProxima = novo;
                mUltima = novo;
            }
        };
        void Imprimir() {
            Posicao* inter = mPrimeira;
            
            while (inter != NULL) {
                cout << inter->mPosicao;
                if (inter != mUltima) {
                    cout << " ";
                } else {
                    cout << endl;
                }
                
                inter = inter->mProxima;
            }
        };
    private:
        Posicao* mPrimeira;
        Posicao* mUltima;
};

class Noh {
    friend class Arvore;
    public:
        Noh(string nome) {
            mNome = nome;
            mEsquerdo = NULL;
            mDireito = NULL;
        };
    private:
        string mNome;
        Noh* mEsquerdo;
        Noh* mDireito;
        Noh* mPai;
        ListaPos mPosicoes;
};

class Arvore {
    public:
        Arvore() {
            mRaiz = NULL;
        };
        ~Arvore() {
            delete mRaiz;
        };
        void Inserir(string nome, int pos) {
            Noh* novo = new Noh(nome);
            PosicaoInsercao posInsercao;
            
            if (mRaiz == NULL) {
                mRaiz = novo;
            } else {
                Noh* atual = mRaiz;
                Noh* pai = NULL;
                
                while (atual != NULL) {
                    pai = atual;
                    
                    if (atual->mNome > nome) {
                        atual = atual->mEsquerdo;
                        posInsercao = esquerda;
                    } else {
                        atual = atual->mDireito;
                        posInsercao = direita;
                    }
                }
                
                novo->mPai = pai;
                
                if (posInsercao == esquerda) {
                    pai->mEsquerdo = novo;
                } else {
                    pai->mDireito = novo;
                }
            }
        };
        bool Buscar(string nome) {
            Noh* atual = mRaiz;
            
            while (atual != NULL) {
                if (atual->mNome == nome) {
                    atual->mPosicoes->Imprimir;
                    return true;
                } else if (atual->mNome > nome) {
                    atual = atual->mEsquerdo;
                } else {
                    atual = atual->mDireito;
                }
            }
            
            cout << "-1" << endl;
            return false;
        };
    private:
        Noh* mRaiz;
};

int main() {
    ifstream arquivo("entrada.txt");
            
            if (arquivo) {
                while (arquivo.eof()) {
                    
                }
            };
}
