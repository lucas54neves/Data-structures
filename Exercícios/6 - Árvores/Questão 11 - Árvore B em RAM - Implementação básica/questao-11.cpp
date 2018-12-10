#include <iostream>
#include <queue>

typedef int TChave;

class Noh {
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    friend class ArvoreB;
    public:
        // colocar aqui métodos públicos
    private:
        bool mFolha;
        unsigned mNroChaves;
        TChave* mVetChaves; // até 2M-1 chaves
        Noh** mVetPtFilhos; // até 2M filhos
};

class ArvoreB {
    public:
        // colocar aqui métodos públicos
        void EscreverNivelANivel(std::ostream& saida);
    private:
        // colocar aqui métodos privados/auxiliares
        int mGrau;
        Noh* mPtRaiz;
};

using namespace std;

ostream& operator<<(ostream& saida, Noh* ptNoh) {
    saida << '[';
    if (ptNoh != NULL) {
        saida << ptNoh->mVetChaves[0];
        for (unsigned i = 1; i < ptNoh->mNroChaves; ++i)
            saida << ',' << ptNoh->mVetChaves[i];
    }
    saida << ']';
    return saida;
}

// Escreve a árvore nível a nível para facilitar a depuração.
void ArvoreB::EscreverNivelANivel(ostream& saida) {
    if (mPtRaiz == NULL)
        saida << "[]\n";
    else {
        queue<Noh*> filhos;
        filhos.push(mPtRaiz);
        while (not filhos.empty()) {
            unsigned nroNohsNesteNivel = unsigned(filhos.size());
            for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
                Noh* ptNoh = filhos.front();
                filhos.pop();
                saida << ptNoh << ' ';
                if (not ptNoh->mFolha)
                    for (unsigned i = 0; i <= ptNoh->mNroChaves; ++i)
                        filhos.push(ptNoh->mVetPtFilhos[i]);
            }
            saida << "\n";
        }
    }
}

int main() {
    int grau;
    cin >> grau;
    ArvoreB arvore(grau);
    char opcao;
    TChave chave;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.Inserir(chave);
                break;
            case 'e': // Escrever nós nível a nível
                arvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}
