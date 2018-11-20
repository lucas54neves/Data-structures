#include <iostream>
#include <exception>
#include <limits>

typedef int TChave;

class Torneio {
    friend std::ostream& operator << (std::ostream& saida, const Torneio& h);
    public:
        // Construtor sem valores
        Torneio(int tam);
        // Construtor com valores
        Torneio(TChave vet[], int tam);
        ~Torneio();
        void Inserir(TChave chave);
        // Retorna o vencedor do torneio (maior) sem removÃª-lo.
        TChave Raiz();
        TChave Retirar();
        bool Vazio();
    protected:
        // Atualiza uma posiÃ§Ã£o, com base em seus dois filhos.
        void Atualizar(int i);
        // Atualiza um toneiro subindo a partir da posicao dada. Util para inserÃ§Ã£o.
        void ArrumarSubindo(int i);
        // Atualiza todos os nÃ³s intermediÃ¡rios do torneio.
        void ArrumarTudo();
        // Calcula o espaÃ§o necessÃ¡rio e inicializa atributos. Usado nos contrutores.
        void CalcularEspacoDeArmazenamento(int tam);
        // Calcula a posiÃ§Ã£o do filho direito de um nÃ³.
        inline int Direito(int i);
        // Calcula a posiÃ§Ã£o do filho esquerdo de um nÃ³.
        inline int Esquerdo(int i);
        // Calcula a posiÃ§Ã£o do pai de um nÃ³.
        inline int Pai(int i);

        TChave* mVetChaves; // espaÃ§o de armazenamento
        int mCapacidade; // quantidade mÃ¡xima de nÃ³s
        int mTamanho; // quantidade de nÃ³s utilizados
        int mNroTorneios; // quantidade de nÃ³s intermediÃ¡rios
        TChave mMenor; // valor especial que indica ausÃªncia de valor
};

using namespace std;

Torneio::Torneio(int tam) {
    CalcularEspacoDeArmazenamento(tam);
    mMenor = numeric_limits<TChave>::min();
    mTamanho = mNroTorneios;
    for (int i = 0; i < mCapacidade; ++i)
        mVetChaves[i] = mMenor;
}

Torneio::Torneio(TChave vet[], int tam) {
    CalcularEspacoDeArmazenamento(tam);
    mMenor = numeric_limits<TChave>::min();
    mTamanho = mNroTorneios + tam;
    int i = 0;
    // copiar dados do vetor para o torneio
    for (; i < tam; ++i) {
        mVetChaves[mNroTorneios+i] = vet[i];
    }
    // posicoes extras ganham a menor chave para completar nÃ³s intermediarios
    i += mNroTorneios;
    while (i < mCapacidade)
        mVetChaves[i++] = mMenor;
    ArrumarTudo();
}

Torneio::~Torneio() {
    delete[] mVetChaves;
}

void Torneio::Atualizar(int i) { // Implementado por Lucas Neves
    if (mVetChaves[Esquerdo(i)] > mVetChaves[Direito(i)]) {
        mVetChaves[i] = mVetChaves[Esquerdo(i)];
    } else {
        mVetChaves[i] = mVetChaves[Direito(i)];
    }
}

void Torneio::ArrumarSubindo(int i) { // Implementado por Lucas Neves
    if (mVetChaves[Pai(i)] < mVetChaves[i]) {
        swap(mVetChaves[Pai(i)], mVetChaves[i]);
        ArrumarSubindo(Pai(i));
    }
}

void Torneio::ArrumarTudo() {
    for (int i = (mTamanho-1)/2; i < mTamanho; ++i) {
        ArrumarSubindo(i);
    } 
}

void Torneio::CalcularEspacoDeArmazenamento(int tam) {
    mNroTorneios = 1;
    while (mNroTorneios < tam)
        mNroTorneios *= 2;
    mCapacidade = 2 * mNroTorneios - 1;
    mNroTorneios -= 1;
    mVetChaves = new TChave[mCapacidade];
}

int Torneio::Pai(int i) {
    return (i-1)/2;
}

int Torneio::Esquerdo(int i) {
    return 2*i+1;
}

int Torneio::Direito(int i) {
    return 2*i+2;
}

TChave Torneio::Raiz() { // Implementado por Lucas Neves
    if (mTamanho == mNroTorneios) {
        throw runtime_error("ImpossÃ­vel acessar raiz de torneio vazio.");
    } else {
        return mVetChaves[0];
    }
}

TChave Torneio::Retirar() { // Implementado por Lucas Neves
    if (mTamanho == mNroTorneios) {
        throw runtime_error("ImpossÃ­vel retirar de torneio vazio.");
    } else {
        TChave raiz = mVetChaves[0];
        
        if (mVetChaves[0] == mVetChaves[Direito(0)]) {
            mVetChaves[0] = mVetChaves[Esquerdo(0)];
        } else {
            mVetChaves[0] = mVetChaves[Direito(0)];
        }
        
        return raiz;
    }
}

bool Torneio::Vazio() {
    return mTamanho == mNroTorneios;
}

void Torneio::Inserir(TChave chave) {
    if (mTamanho == mCapacidade) {
        throw runtime_error("ImpossÃ­vel inserir em torneio cheio.");
    } else {
        bool inseriu = false;
        
        for (int i = mTamanho - 1; i >= (mTamanho-1)/2 && inseriu == false; --i) {
            if (mVetChaves[i] == mMenor) {
                mVetChaves[i] = chave;
                inseriu = true;
            }
        }
        ++mTamanho;
        
        ArrumarTudo();
    }
}

std::ostream& operator << (std::ostream& saida, const Torneio& t) {
    // Operador de escrita pode ser util para depurar o torneio.
    saida << '[';
    TChave chave;
    for (int i=0; i < t.mNroTorneios; ++i) {
        chave = t.mVetChaves[i];
        if (chave == t.mMenor)
            saida << "## ";
        else
            saida << chave << ' ';
    }
    saida << '|';
    int pos = t.mNroTorneios;
    int limite = t.mTamanho;
    while (pos < limite) {
        chave = t.mVetChaves[pos];
        if (chave == t.mMenor) {
            saida << " ##";
            ++limite;
        }
        else
            saida << ' ' << chave;
        ++pos;
    }
    saida << ']';
    return saida;
}

int main() {
    int capacidade; // nro de valores que quero guardar no torneio
    cin >> capacidade;
    Torneio torneio(capacidade);
    TChave chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                try {
                    cin >> chave;
                    torneio.Inserir(chave);
                }
                catch (runtime_error& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 'r': // Remover
                try {
                    cout << torneio.Retirar() << endl;
                }
                catch (runtime_error& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 'e': // Escrever
                cout << torneio << endl;
        }
    } while (operacao != 'f'); // Finalizar execuÃ§Ã£o
    return 0;
}
