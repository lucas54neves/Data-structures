// Tabela Hash com tratamento de colisão por endereçamento aberto
#include <iostream>
#include <exception>

typedef int TValor; // tipo do valor armazenado

class InfoHash {
    friend class Hash; // essa classe só deve ser usada na classe Hash
    InfoHash();
    InfoHash(const std::string& chave, const TValor& valor);
    std::string mChave;
    TValor mValor;
};

class Hash {
    public:
        Hash(unsigned capacidade = 50);
        ~Hash();
        // Mostra todos as posições de armazenamento da hash.
        void EscreverEstrutura(std::ostream& saida) const;
        // Insere uma cópia do valor. Não permite inserção de chave repetida.
        void Inserir(const std::string& chave, const TValor& valor);
        // Remove um item da hash associado com a chave dada.
        void Remover(const std::string& chave);
        // Retorna o valor associado a uma chave.
        TValor Valor(const std::string& chave) const;
    protected:
        // Retorna a posicao em que uma chave está armazenada na estrutura.
        unsigned Buscar(const std::string& chave) const;
        // Retorna a posicao em que uma chave deveria ficar na estrutura.
        unsigned Posicao(const std::string& chave) const;

        InfoHash** mVetPtDados;
        InfoHash* REMOVIDO; // ponteiro especial a ser usado para marcar posições de elemento removido
        unsigned mCapacidade;
        unsigned mTamanho;
};

using namespace std;

InfoHash::InfoHash()
    : mChave(), mValor() {
}

InfoHash::InfoHash(const std::string& chave, const TValor& valor)
    : mChave(chave), mValor(valor) {
}

Hash::Hash(unsigned capacidade) // capacidade tem valor default
    : mVetPtDados(new InfoHash*[capacidade]), REMOVIDO(new InfoHash()), mCapacidade(capacidade), mTamanho(0) {
    // Implementado por Lucas Neves
    // inicializa todas as posições de armazenamento com NULL indicando posição VAZIA
    for (unsigned i = 0; i < mCapacidade; ++i) {
        mVetPtDados[i] = NULL;
    }
}

Hash::~Hash() {
    // Implementado por Lucas Neves
    // desalocar memória de cada item (InfoHash) armazenado
    for (unsigned i = 0; i < mCapacidade; ++i) {
        if(mVetPtDados[i] != REMOVIDO) {
            delete mVetPtDados[i];
        }
    }
    // desalocar o ponteiro especial REMOVIDO
    delete REMOVIDO;
    // desalocar o vetor de ponteiros
    delete[] mVetPtDados;
}

unsigned Hash::Buscar(const std::string& chave) const {
    // Implementado por Lucas Neves
    // Retorna a posicao em que uma chave está armazenada na estrutura. Protegido.
    unsigned pos = Posicao(chave);
    
    if (mVetPtDados[pos] == NULL || mVetPtDados[pos] == REMOVIDO) {
        return 0;
    } else {
        unsigned i = pos + 1;
        while (i != pos) {
            if (i >= mCapacidade) {
                i = 0;
            }
            
            if (mVetPtDados[i]->mChave == chave) {
                return i;
            } else {
                ++i;
            }
        }
    }
    return 0;
}

void Hash::EscreverEstrutura(std::ostream& saida) const {
    // Mostra todos as posições de armazenamento da hash. Ajuda a debugar.
    for (unsigned i = 0; i < mCapacidade; ++i) {
        saida << '[' << i;
        if (mVetPtDados[i] != NULL) {
            if (mVetPtDados[i] == REMOVIDO)
                saida << "/removido";
            else
                saida << '/' << mVetPtDados[i]->mChave << '/' << mVetPtDados[i]->mValor;
        }
        saida << "] ";
    }
}

void Hash::Inserir(const string& chave, const TValor& valor) {
    // Implementado por Lucas Neves
    // Insere uma cópia do valor. Não permite inserção de chave repetida.
    if (mTamanho < mCapacidade) {
        unsigned pos = Posicao(chave);
        
        if (mVetPtDados[pos] == NULL || mVetPtDados[pos] == REMOVIDO) {
            mVetPtDados[pos] = new InfoHash(chave, valor);
        } else if (mVetPtDados[pos]->mChave == chave) {
            cerr << "ERRO" << endl;
        } else {
            bool inserido = false;
            unsigned i = pos + 1;
            while (not inserido) {
                if (i >= mCapacidade) {
                    i = 0;
                }
                
                if (mVetPtDados[pos]->mChave == chave) {
                    cerr << "ERRO" << endl;
                } else if (mVetPtDados[i] == NULL || mVetPtDados[i] == REMOVIDO) {
                    mVetPtDados[i] = new InfoHash(chave, valor);
                    inserido = true;
                }
                
                ++i;
            }
        }
        
        ++mTamanho;
    } else {
        cerr << "ERRO" << endl;
    }
}

unsigned Hash::Posicao(const string& chave) const {
    // Retorna a posição de armazenamento de uma chave, 0 <= posicao < mCapacidade. Protegido.
    unsigned pos = 1;
    unsigned tamanho = unsigned(chave.length());
    for (unsigned i = 0; i < tamanho; ++i)
        pos = 7 * pos + chave[i];
    return pos % mCapacidade;
}

void Hash::Remover(const std::string& chave) {
    // Implementado por Lucas Neves
    // Remove um item da hash associado com a chave dada.
    if (mTamanho == 0) {
        cerr << "ERRO" << endl;
    } else {
        unsigned pos = Posicao(chave);
        
        if (mVetPtDados[pos] == NULL) {
            cerr << "ERRO" << endl;
        } else {
            bool removido = false;
            
            if (mVetPtDados[pos] != REMOVIDO) {
                if (mVetPtDados[pos]->mChave == chave) {
                    mVetPtDados[pos] = REMOVIDO;
                    --mTamanho;
                    removido = true;
                } else {
                    for (unsigned i = pos + 1; i != pos && removido == false; ++i) {
                        if (mVetPtDados[i]->mChave == chave) {
                            mVetPtDados[i] = REMOVIDO;
                            --mTamanho;
                            removido = true;
                        }
                    }
                }
            }
            
            if (not removido) {
                cerr << "ERRO" << endl;
            }
        }
    }
}

TValor Hash::Valor(const std::string& chave) const {
    // Retorna o valor associado a uma chave.
    unsigned pos = Posicao(chave);
    
    if (mVetPtDados[pos]->mChave == chave) {
        return mVetPtDados[pos]->mValor;
    } else {
        for (unsigned i = pos + 1; i != pos; ++i) {
            if (i >= mCapacidade) {
                i = 0;
            }
            if (mVetPtDados[i]->mChave == chave) {
                return mVetPtDados[i]->mValor;
            }
        }
    }
    return 0;
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Hash tabela(capacidade);
    char operacao;
    string chave;
    TValor valor;
    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> chave >> valor;
                    tabela.Inserir(chave, valor);
                    break;
                case 'r': // remover
                    cin >> chave;
                    tabela.Remover(chave);
                    break;
                case 'c': // consultar
                    cin >> chave;
                    valor = tabela.Valor(chave);
                    cout << valor << endl;
                    break;
                case 'd': // debug (mostrar estrutura)
                    tabela.EscreverEstrutura(cout);
                    cout << endl;
                    break;
                case 'f': // finalizar
                    // vai testar depois
                    break;
                default:
                    cerr << "operação inválida\n";
            }
        }
        catch (exception& e) {
            // ignorar a mensagem que explica o erro e só escrever ERRO.
            cout << "ERRO" << endl;
        }
    } while (operacao != 'f');
    return 0;
}
