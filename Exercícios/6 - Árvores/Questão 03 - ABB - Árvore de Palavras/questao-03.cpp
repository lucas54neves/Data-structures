#include <iostream>
#include <fstream>

using namespace std;
typedef string Dado;
enum Posicao {dir, esq};

class Noh {
    friend class ABB;
    private:
        Dado mValor;
        int mPosicao;
        Noh* mPtPai;
        Noh* mPtEsquerdo;
        Noh* mPtDireito;
        Noh* mPtProximo;
    public:
        Noh(Dado d = 0, int pos = 0)
        : mValor(d), mPosicao(pos), mPtPai(NULL), mPtEsquerdo(NULL), mPtDireito(NULL), mPtProximo(NULL){
        }
        ~Noh() {
            delete mPtEsquerdo;
            delete mPtDireito;
        }
};

class ABB {
    private:
        Noh* mPtRaiz;
    public:
        ABB()
        : mPtRaiz(NULL) {
        }
        
        ~ABB() {
            delete mPtRaiz;
        }
        
        void Inserir(Dado d, int pos) {
            Noh* novo = new Noh(d, pos);
            
            if (mPtRaiz == NULL) {
                mPtRaiz = novo;
            } else {
                Posicao posInsercao;
                Noh* atual = mPtRaiz;
                Noh* anterior = NULL;
                bool achou = false;
                
                while (atual != NULL && achou == false) {
                    anterior = atual;
                    
                    if (atual->mValor > d && atual->mValor != d) {
                        atual = atual->mPtEsquerdo;
                        posInsercao = esq;
                    } else if (atual->mValor < d && atual->mValor != d) {
                        atual = atual->mPtDireito;
                        posInsercao = dir;
                    } else {
                        achou = true;
                        
                        while (atual->mPtProximo != NULL) {
                            atual = atual->mPtProximo;
                        }
                        
                        atual->mPtProximo = novo;
                    }
                }
                
                if (achou == false) {
                    novo->mPtPai = anterior;
                    
                    if (posInsercao == esq) {
                        anterior->mPtEsquerdo = novo;
                    } else {
                        anterior->mPtDireito = novo;
                    }
                }
            }
        }
        
        void Buscar(Dado d) {
            Noh* atual = mPtRaiz;
            bool achou = false;
            
            while (atual != NULL && achou == false) {
                if (atual->mValor == d) {
                    achou = true;
                    
                    while (atual != NULL) {
                        cout << atual->mPosicao << " ";
                        atual = atual->mPtProximo;
                    }
                } else if (atual->mValor > d) {
                    atual = atual->mPtEsquerdo;
                } else {
                    atual = atual->mPtDireito;
                }
            }
            
            if (achou == false) {
                cout << "-1" << endl;
            }
        }
};

int main() {
    ABB arvorePalavras;
    int pos = 1;
    
    ifstream arquivo;
    arquivo.open("entrada.txt");
    
    if (arquivo) {
        Dado d;
        
        while (!arquivo.eof()) {
            arquivo >> d;
            arvorePalavras.Inserir(d, pos);
            ++pos;
        }
    }
    
    Dado palavra;
    cin >> palavra;
    
    arvorePalavras.Buscar(palavra);
    
    return 0;
}
