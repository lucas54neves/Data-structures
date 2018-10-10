#include <iostream>
#include <string>

using namespace std;

unsigned int FuncaoHash (string palavra) {
    return palavra.size() % 23;
}

class Noh {
    friend class Encadeamento;
    public:
        Noh(string palavra, string definicao);
    private:
        string mStringPalavra;
        string mStringDefinicao;
        Noh* mPtrProximo;
};

Noh::Noh(string palavra, string definicao) {
    mStringPalavra = palavra;
    mStringDefinicao = definicao;
    mPtrProximo = NULL;
}

class Encadeamento {
    public:
        Encadeamento();
        void Inserir(string palavra, string definicao);
        void RemoverElementos();
        void Buscar(string palavra);
    private:
        Noh* mPtrPrimeiro;
        Noh* mPtrUltimo;
        unsigned int mTamanho;
};

Encadeamento::Encadeamento() {
    mPtrPrimeiro = NULL;
    mPtrUltimo = NULL;
    mTamanho = 0;
}

void Encadeamento::Inserir(string palavra, string definicao) {
    Noh* novo = new Noh(palavra, definicao);
    
    if (mTamanho == 0) {
        mPtrPrimeiro = novo;
        mPtrUltimo = novo;
    } else {
        mPtrUltimo->mPtrProximo = novo;
        mPtrUltimo = novo;
    }
    
    ++mTamanho;
}

void Encadeamento::RemoverElementos() {
    Noh* inter = mPtrPrimeiro;
    Noh* removido = NULL;
    
    while (inter != NULL) {
        removido = inter;
        inter = inter->mPtrProximo;
        delete removido;
        --mTamanho;
    }
    
    delete inter;
}

void Encadeamento::Buscar(string palavra) {
    Noh* inter = mPtrPrimeiro;
    bool achou = false;
    
    while (inter != NULL) {
        if (inter->mStringPalavra == palavra) {
            achou = true;
            cout << "[" << inter->mStringPalavra << "] => " << inter->mStringDefinicao << endl;
            inter = NULL;
        } else {
            inter = inter->mPtrProximo;
        }
    }
    
    if (not achou) {
        cout << "NULL" << endl;
    }
}

class TabelaHash {
    public:
        TabelaHash(int cap = 23);
        ~TabelaHash();
        void Inserir(string palavra, string definicao);
        void Buscar(string palavra);
    private:
        Encadeamento* mElementos;
        unsigned int mCapacidade;
};

TabelaHash::TabelaHash(int cap) {
    mCapacidade = cap;
    mElementos = new Encadeamento[mCapacidade];
}

TabelaHash::~TabelaHash() {
    for (unsigned int i = 0; i < mCapacidade; ++i) {
        mElementos[i].RemoverElementos();
    }
    delete[] mElementos;
}

void TabelaHash::Inserir(string palavra, string definicao) {
    unsigned int h;
    h = FuncaoHash(palavra);
    
    mElementos[h].Inserir(palavra, definicao);
}

void TabelaHash::Buscar(string palavra) {
    unsigned int h;
    h = FuncaoHash(palavra);
    
    mElementos[h].Buscar(palavra);
}

int main() {
    TabelaHash dicionario;
    unsigned int qtdPalavras;
    
    cin >> qtdPalavras;
    
    string palavra, definicao;
    
    for (unsigned int i = 0; i < qtdPalavras; ++i){
        cin >> palavra;
        cin.ignore();
        getline(cin, definicao);
        dicionario.Inserir(palavra, definicao);
    }
    
    cin >> palavra;
    while (palavra != "-1") {
        dicionario.Buscar(palavra);
        cin >> palavra;
    }
    
    return 0;
}
