#include <iostream>
#include <string>

using namespace std;

typedef string Comando;

class Noh {
    friend class Deque;
    public:
        Noh(Comando d);
    private:
        Comando mComando;
        Noh* mProximo;
        Noh* mAnterior;
};

Noh::Noh(Comando d) : mComando(d) {
    mProximo = NULL;
    mAnterior = NULL;
}

class Deque {
    public:
        Deque(unsigned cap);
        ~Deque();
        void Inserir(Comando d);
        void Remover();
        bool Vazia();
    private:
        unsigned mCapacidade;
        unsigned mTamanho;
        void RemoverTodos();
        Noh* mPrimeiro;
        Noh* mUltimo;
};

Deque::Deque(unsigned cap) : mCapacidade(cap) {
    mPrimeiro = NULL;
    mUltimo = NULL;
    mTamanho = 0;
}

Deque::~Deque() {
    RemoverTodos();
}

void Deque::Inserir(Comando d) {
    Noh* novo = new Noh(d);

    if (mTamanho < mCapacidade) {
        if (Vazia()) {
            mPrimeiro = novo;
            mUltimo = novo;
        } else {
            mUltimo->mProximo = novo;
            novo->mAnterior = mUltimo;
            mUltimo = novo;
        }
        ++mTamanho;
    } else {
        Noh* esquecido = mPrimeiro;
        if (mTamanho == 1) {
            mPrimeiro = novo;
            mUltimo = novo;
        } else {
            mPrimeiro = mPrimeiro->mProximo;
            mPrimeiro->mAnterior = NULL;
            mUltimo->mProximo = novo;
            novo->mAnterior = mUltimo;
            mUltimo = novo;
        }
        cout << "esqueci: " << esquecido->mComando << endl;
        delete esquecido;
    }
}

void Deque::Remover() {
    if (Vazia()) {
        cout << "ERRO" << endl;
    } else {
        Noh* removido = mUltimo;
        
        if (mTamanho == 1) {
            mUltimo = NULL;
            mPrimeiro = NULL;
        } else {
            Noh* anterior = mUltimo->mAnterior;
            
            mUltimo = anterior;
            mUltimo->mProximo = NULL;
        }
        
        --mTamanho;
        cout << "desfazer: " << removido->mComando << endl;
        delete removido;
    }
}

bool Deque::Vazia() {
    return (mTamanho == 0);
}

void Deque::RemoverTodos() {
    Noh* inter = mPrimeiro;
    
    while (inter != NULL) {
        Noh* removido = inter;
        inter = inter->mProximo;
        delete removido;
    }
    
    mTamanho = 0;
    mPrimeiro = NULL;
    mUltimo = NULL;
}

int main() {
    unsigned cap;
    cin >> cap;
    
    Deque minhaDeque(cap);
    
    Comando ordem;
    cin.ignore();
    getline(cin, ordem);
    while (ordem != "sair") {
        if (ordem == "undo") {
        minhaDeque.Remover();
        } else {
        minhaDeque.Inserir(ordem);
        }
        getline(cin, ordem);
    }
    
    return 0;
}
