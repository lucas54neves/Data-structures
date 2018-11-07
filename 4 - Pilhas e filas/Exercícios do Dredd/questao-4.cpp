#include <iostream>

typedef int Dado;

class Fila {
    public:
        Fila(unsigned cap = 80);
        ~Fila();
        // Remove e retorna o próximo elemento da fila.
        Dado Desenfileira();
        // Insere um valor na fila. Retorna um booleano que informa se a inserção foi realmente
        // realizada.
        bool Enfileirar(const Dado& valor);
        // Escreve todo o conteúdo do armazenamento da fila na saída de dados.
        void EscreverConteudo(std::ostream& saida) const;
        // Retorna tamanho, capacidade, inicio e fim da fila.
        void Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const;
        // Retorna o primeiro elemento da fila, sem removê-lo.
        Dado Proximo() const;
        // Retorna a quantidade de elementos na fila.
        unsigned Tamanho() const { return mTamanho; }
        // Consulta se a fila está vazia.
        bool Vazia() const;
    protected:
        unsigned mCapacidade;
        Dado* mDados;
        unsigned mPosInicio; // indica a posicao do primeiro
        unsigned mPosFim;    // indica a posicao do ultimo
        unsigned mTamanho;
};

using namespace std;

Fila::Fila(unsigned cap) : mCapacidade(cap) { // cap tem valor default
    mDados = new Dado[cap];
    mTamanho = 0;
    mPosInicio = 0;
    mPosFim = 0;
}

Fila::~Fila() {
    delete[] mDados;
}

// Remove e retorna o próximo elemento da fila.
Dado Fila::Desenfileira() {
    if (Vazia()) {
        cout << "Fila vazia" << endl;
        return -1;
    } else if (mPosInicio == mCapacidade - 1) {
        mPosInicio = 0;
        --mTamanho;
        return mDados[mCapacidade - 1];
    } else if (mTamanho == 1) {
        unsigned pos = mPosInicio;
        mPosInicio = 0;
        mPosFim = 0;
        mTamanho = 0;
        return mDados[pos];
    } else {
        ++mPosInicio;
        --mTamanho;
        return mDados[mPosInicio - 1];
    }
}

// Insere um valor na fila. Retorna um booleano que informa se a inserção foi realmente realizada.
bool Fila::Enfileirar(const Dado& valor) {
    if (mTamanho == mCapacidade) {
        return false;
    } else if (Vazia()) {
        mDados[0] = valor;
        mPosInicio = 0;
        mPosFim = 0;
    } else if ((mPosFim + 1) == mCapacidade){
        mDados[0] = valor;
        mPosFim = 0;
    } else {
        ++mPosFim;
        mDados[mPosFim] = valor;
    }
    ++mTamanho;
    return true;
}

// Escreve todo o conteúdo do armazenamento (começando da posição zero) da fila na saída de dados.
void Fila::EscreverConteudo(ostream& saida) const {
    for (unsigned i = 0; i < mCapacidade; i++) {
        saida << mDados[i] << " ";
    }
    saida << endl;
}

// Retorna tamanho, capacidade, inicio e fim da fila.
void Fila::Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const {
    *ptTam = mTamanho;
    *ptCap = mCapacidade;
    *ptIni = mPosInicio;
    *ptFim = mPosFim;
}

// Retorna o primeiro elemento da fila, sem removê-lo.
Dado Fila::Proximo() const {
    return (mDados[mPosInicio]);
}

// Consulta se a fila está vazia.
bool Fila::Vazia() const {
    return (mTamanho == 0);
}

int main() {
    unsigned tamanho, capacidade, inicio, fim;
    cin >> capacidade;
    Fila fila(capacidade);
    Dado valor;
    char comando;
    cin >> comando;
    while (comando != 't') {
        switch (comando) {
        case 'e': // enfileirar
            cin >> valor;
            if (not fila.Enfileirar(valor))
                cout << "FILA CHEIA!\n";
            break;
        case 'd': // desenfileirar
            if (fila.Vazia())
                cout << "ERRO\n";
            else {
                valor = fila.Desenfileira();
                cout << valor << endl;
            }
            break;
        case 'p': // proximo
            if (fila.Vazia())
                cout << "ERRO\n";
            else
                cout << fila.Proximo() << endl;
            break;
        case 'i': // informações sobre a fila
            fila.Info(&tamanho, &capacidade, &inicio, &fim);
            cout << "tamanho=" << tamanho << " capacidade=" << capacidade << " inicio=" << inicio
                 << " fim=" << fim << endl;
            fila.EscreverConteudo(cout);
            break;
        case 't':
            // vai testar novamente no while
            break;
        default:
            cout << "comando inválido\n";
        }
        cin >> comando;
    }
    return 0;
}
