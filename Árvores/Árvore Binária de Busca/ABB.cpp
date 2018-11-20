#include <iostream>

using namespace std;

enum posInsercao {esq, dir};

typedef int Tipo;

class Noh {
    friend class ABB;
    public:
        Noh(Tipo chave = 0);
        ~Noh();
        bool FilhoDaDireita();
        bool FilhoDaEsquerda();
        bool Sucessor(Noh* ptResultado);
        Noh* Menor();
        int Nivel();
    private:
        Tipo mChave;
        Noh* mEsquerdo;
        Noh* mDireito;
        Noh* mPai;
};

Noh::Noh(Tipo chave) : mChave(chave), mEsquerdo(NULL). mDireito(NULL), mPai(NULL) {
}

Noh::~Noh() {
    delete mEsquerdo;
    delete mDireito;
}

bool Noh::FilhoDaDireita() {
    if (this->mPai == NULL) {
        return false
    } else {
        return mPai->mDireito == this;
    }
}

bool Noh::FilhoDaEsquerda() {
    if (this->mPai == NULL) {
        return false
    } else {
        return mPai->mEsquerdo == this;
    }
}

bool Noh::Sucessor(Noh* ptResultado) {
    if (this->mPai == NULL) {
        if (this->mDireito == NULL) {
            return false;
        } else {
            *ptResultado = this->mDireito->Menor();
        }
    } else if (this->mDireito != NULL) {
        *ptResultado = this->mDireito->Menor();
    } else if (this->FilhoDaDireita()) {
        Noh* atual = this;
        
        while (atual->FilhoDaDireita()) {
            atual = atual->mPai;
        }
        
        if (atual->mPai != NULL) {
            *ptResultado = atual->mPai;
            return true;
        } else {
            return false;
        }
    } else {
        *ptResultado = this->mPai;
        return true;
    }
}

Noh* Noh::Menor() {
    if (this->mEsquerdo != NULL) {
        return this->mEsquerdo->Minimo();
    } else {
        return this;
    }
}

class ABB {
    public:
        ABB();
        ~ABB();
        void Inserir(Tipo chave);
        void Remover(Tipo chave);
        Noh* Buscar(Tipo chave);
        void Transplanta(Noh* antigo, Noh* novo);
        bool Vazia();
        void EscreverOrdem();
        void EscreverPreOrdem();
        void EscreverPosOrdem();
        Noh* Minimo(Noh* raiz);
        Noh* Maximo(Noh* raiz);
        bool Sucessor(Tipo dado, Noh* ptResultado)
        int Altura();
    private:
        Noh* mRaiz;
        void EscreverOrdemAux(Noh* atual, int nivel);
        void EscreverPreOrdemAux(Noh* atual, int nivel);
        void EscreverPosOrdemAux(Noh* atual, int nivel);
};

ABB::ABB() {
    mRaiz = NULL;
}

ABB::~ABB() {
    delete mRaiz;
}

void ABB::Inserir(Tipo chave) {
    Noh* novo = new Noh(chave);
    if (mRaiz == NULL) {
        mRaiz = novo;
    } else {
        Noh* atual = mRaiz;
        posInsercao insercao;
        
        while (atual != NULL) {
            if (atual->mChave > chave) {
                atual = atual->mEsquerdo;
                insercao = esq;
            } else {
                atual = atual->mDireito;
                insercao = dir;
            }
        }
        
        novo->mPai = atual;
        if (insercao == esq) {
            atual->mEsquerdo = novo;
        } else {
            atual->mDireito = novo
        }
    }
}

void ABB::Remover(Tipo chave) {
    if (mRaiz == NULL) {
        cout << "Árvore vazia" << endl;
    } else {
        Noh* nohRemover = Busca(chave);
        
        if (nohRemover->mEsquerdo == NULL) {
            Transplanta(nohRemover, nohRemover->mDireito);
        } else if (nohRemover->mDireito == NULL) {
            Transplanta(nohRemover, nohRemover->mEsquerdo);
        } else {
            Noh* sucessor;
            nohRemover->Sucessor(sucessor);
            
            if (sucessor->mPai !=  nohRemover) {
                Transplanta(sucessor, sucessor->mDireito);
                sucessor->mDireito = nohRemover->mDireito;
                sucessor->mDireito->mPai = sucessor;
            }
            
            Transplanta(nohRemover, sucessor);
            sucessor->mEsquerdo = nohRemover->mEsquerdo;
            sucessor->mEsquedo->mPai = sucessor;
            
            nohRemover->mEsquerdo = NULL;
            nohRemover->mDireito = NULL;
            delete nohRemover;
        }
    }
}
