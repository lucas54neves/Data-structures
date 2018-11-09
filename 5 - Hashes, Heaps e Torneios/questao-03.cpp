// Tabela Hash com tratamento de colisão por endereçamento aberto
#include <iostream>
#include <string>
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
        // Insere um InfoHash na estrutura. Auxiliar para Inserir(chave/valor) e Redimensionar.
        void Inserir(InfoHash* ptPar);
        // Retorna a posicao em que uma chave deveria ficar na estrutura.
        unsigned Posicao(const std::string& chave) const;
        // Altera a capacidade da estrutura.
        void Redimensionar(unsigned novaCapacidade);
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
    // inicializar todas as posições de armazenamento com NULL indicando posição VAZIA
    for (unsigned i = 0; i < mCapacidade; ++i) {
        mVetPtDados[i] = NULL;
    }
}

Hash::~Hash() {
    // Implementado por Lucas Neves
    // desalocar memória de cada item (InfoHash) armazenado
    for (unsigned i = 0; i < mCapacidade; ++i) {
        if (mVetPtDados[i] != REMOVIDO) {
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
    unsigned h = Posicao(chave);
    
    if (mVetPtDados[h]->mChave == chave) {
        throw runtime_error ("Chave não encontrada.");
    } else {
        unsigned i = h + 1;
        bool inverteu = false;
        
        while (i != h || inverteu == false) {
            if (i >= mCapacidade) {
                i = 0;
                inverteu = true;
            }
            
            if (mVetPtDados[i]->mChave == chave) {
                return i;
            } else {
                ++i;
            }
        }
    }
    throw runtime_error ("Chave não encontrada.");
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
    if (mTamanho == mCapacidade) {
        Redimensionar(mCapacidade + 5);
    }
    
    if (mTamanho < mCapacidade) {
        unsigned pos = Posicao(chave);
        
        if (mVetPtDados[pos] == NULL || mVetPtDados[pos] == REMOVIDO) {
            mVetPtDados[pos] = new InfoHash(chave, valor);
        } else if (mVetPtDados[pos]->mChave == chave) {
            throw runtime_error ("Chave duplicada");
        } else {
            bool inserido = false;
            unsigned i = pos + 1;
            while (not inserido) {
                if (i >= mCapacidade) {
                    i = 0;
                }
                
                if (mVetPtDados[pos]->mChave == chave) {
                    throw runtime_error ("Chave duplicada");
                } else if (mVetPtDados[i] == NULL || mVetPtDados[i] == REMOVIDO) {
                    mVetPtDados[i] = new InfoHash(chave, valor);
                    inserido = true;
                }
                
                ++i;
            }
        }
        
        ++mTamanho;
    } else {
        throw runtime_error ("Inserção inválida");
    }
}

void Hash::Inserir(InfoHash* ptPar) {
    // Implementado por Lucas Neves
    // Insere um par (chave/valor) na estrutura. Supõe que a chave é válida e única.
    // Supõe que há espaço para inserção e que o ponteiro é válido. Não altera o tamanho.
    // Método protegido, auxiliar para Inserir(chave, valor) e Redimensionar(cap).
    unsigned h = Posicao(ptPar->mChave);
    
    if (mVetPtDados[h] == NULL) {
        mVetPtDados[h] = ptPar;
    } else {
        unsigned i = h;
        while (mVetPtDados[i] != NULL || mVetPtDados[i] != NULL) {
            if (i >= mCapacidade) {
                i = 0;
            } else {
                ++i;
            }
        }
        mVetPtDados[i] = ptPar;
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

void Hash::Redimensionar(unsigned novaCapacidade) {
    // Implementado por Lucas Neves
    // Altera a capacidade da estrutura. Pode ser chamado mesmo que a estrutura não esteja cheia.
    // Verifica se a novaCapacidade é válida. Método protegido.
    if (novaCapacidade > mCapacidade) {
        Hash* novaHash = new Hash(novaCapacidade);
        
        for (unsigned i = 0; i < mCapacidade; ++i) {
            novaHash->Inserir(mVetPtDados[i]);
        }
        
        delete[] mVetPtDados;
        
        mCapacidade = novaCapacidade;
        mVetPtDados = novaHash->mVetPtDados;
    } else {
        throw runtime_error ("A nova capacidade é menor que a capacidade anterior");
    }
}

void Hash::Remover(const std::string& chave) {
    // Implementado por Lucas Neves
    // Remove um item da hash associado com a chave dada.
    if (mTamanho == 0) {
        throw runtime_error ("Hash vazia");
    } else {
        unsigned h = Posicao(chave);
        
        if (mVetPtDados[h] == NULL) {
            throw runtime_error ("Posição vazia");
        } else if (mVetPtDados[h]->mChave == chave) {
            mVetPtDados[h] = REMOVIDO;
            --mTamanho;
        } else {
           bool removido = false;
            
            for (unsigned i = h + 1; i != h && removido == false; ++i) {
                if (i >= mCapacidade) {
                    i = 0;
                }
                if (mVetPtDados[i]->mChave == chave) {
                    mVetPtDados[i] = REMOVIDO;
                    --mTamanho;
                    removido = true;
                }
            }
            
            if (removido == false) {
                throw runtime_error ("Chave não encontrada");
            }
        }
    }
}

TValor Hash::Valor(const std::string& chave) const {
    // Implementado por Lucas Neves
    // Retorna o valor associado a uma chave.
    unsigned h = Posicao(chave);
    
    if (mVetPtDados[h]->mChave == chave) {
        return mVetPtDados[h]->mValor;
    } else {
        for (unsigned i = h + 1; i != h; ++i) {
            if (i >= mCapacidade) {
                i = 0;
            }
            
            if (mVetPtDados[i]->mChave == chave) {
                return mVetPtDados[h]->mValor;
            }
        }
    }
    
    throw runtime_error ("Chave não encontrada");
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
