#include <iostream>
#include <stdexcept>
#include <queue>

typedef std::string TValor;
typedef unsigned TChave;
enum Cor {PRETO, VERMELHO};

class Noh {
    friend class ArvoreRN;
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    public:
        Noh(unsigned chave, TValor valor);
    private:
        Noh* Tio();
        void DesalocarRecursivo();
        TValor mValor;
        TChave mChave;
        Cor mCor;
        Noh* mEsq;
        Noh* mDir;
        Noh* mPai;
};

class ArvoreRN {
    public:
        ArvoreRN();
        ~ArvoreRN();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(unsigned chave, TValor valor);
    private:
        void ArrumarInsercao(Noh* umNoh);
        void RotacionarDireita(Noh* umNoh);
        void RotacionarEsquerda(Noh* umNoh);
        Noh* mRaiz;
};

using namespace std;

// === classe Noh ==============================================================
Noh::Noh(TChave chave, TValor valor)
    : mValor(valor), mChave(chave), mCor(VERMELHO), mEsq(NULL), mDir(NULL), mPai(NULL) {
}

// Desaloca as subárvores e depois a si próprio.
void Noh::DesalocarRecursivo() {
	// Modificado
    delete mDir;
    delete mEsq;
    delete this; // Será mesmo?
}

// Retorna o tio do nó, ou NULL se não houver tio
Noh* Noh::Tio() {
	// Modificado
	if (mPai == NULL) {
		return NULL;
	} else if (mPai->mPai == NULL) {
		return NULL;
	} else if (mPai->mPai->mDir != NULL) {
		return mPai->mPai->mDir;
	} else if (mPai->mPai->mEsq != NULL) {
		return mPai->mPai->mEsq;
	} else {
		return NULL;
	}
}

// === classe ArvoreRN =========================================================
ArvoreRN::ArvoreRN() : mRaiz(NULL) {
}

ArvoreRN::~ArvoreRN() {
	// Modificado
	delete mRaiz;
}

// insere uma chave/valor na árvore,
// chama ArrumarInsercao para corrigir eventuais problemas
void ArvoreRN::Inserir(unsigned chave, TValor valor) {
    Noh* novoNoh = new Noh(chave, valor);
    
    if (mRaiz == NULL) {
		mRaiz = novoNoh;
		mRaiz->mCor = PRETO;
	} else {
		Noh* inter = mRaiz;
		Noh* aux;
		bool esq;
		
		while (inter != NULL) {
			aux = inter;
			if (novoNoh->mChave < inter->mChave) {
				inter = inter->mEsq;
				esq = true;
			} else {
				inter = inter->mDir;
				esq = false;
			}
		}
		
		inter = aux;
		
		if (esq) {
			inter->mEsq = novoNoh;
			novoNoh->mPai = inter;
		} else {
			inter->mDir = novoNoh;
			novoNoh->mPai = inter;
		}
		
		ArrumarInsercao(novoNoh);
	}
}

// procedimento para manter balanceamento após inserção
void ArvoreRN::ArrumarInsercao(Noh* umNoh) {
	// Modificado
	if (umNoh == mRaiz && umNoh->mCor == VERMELHO) {
		umNoh->mCor = PRETO;
	} else if (umNoh->Tio() != NULL) {
		if (umNoh->Tio()->mCor == PRETA) {
			// Rotação
		} else {
			// Mudança de cor
		}
	}
	
	/*if (umNoh->mPai->mCor == VERMELHO) {
		// Caso 1
		if (umNoh->mPai->mCor == VERMELHO
		 && umNoh->Tio()->mCor == VERMELHO
		 && umNoh->mPai->mPai->mCor == PRETO) {
			umNoh->mPai->mCor = PRETO;
			umNoh->Tio()->mCor = PRETO;
			umNoh->mPai->mPai->mCor = VERMELHO;
		} else {
			// Caso 2
			if (umNoh->mPai->mCor == VERMELHO
			 && umNoh->Tio()->mCor == PRETO
			 && umNoh->mPai->mPai->mCor == PRETO
			 && umNoh == umNoh->mPai->mDir
			 && umNoh->mPai == umNoh->mPai->mPai->mDir) {
				umNoh->mPai->mCor = PRETO;
				umNoh->mPai->mPai->mCor = VERMELHO;
				RotacionarEsquerda(umNoh);
			} else {
				// Caso 3
				if (umNoh->mPai->mCor == VERMELHO
				 && umNoh->Tio()->mCor == PRETO
				 && umNoh->mPai->mPai->mCor == PRETO
				 && umNoh == umNoh->mPai->mEsq
				 && umNoh->mPai == umNoh->mPai->mPai->mEsq) {
					 umNoh->mPai->mCor = PRETO;
					 umNoh->mPai->mPai->mCor = VERMELHO;
					 RotacionarEsquerda(umNoh);
				 } else {
					 // Caso 4
					 if (umNoh->mPai->mCor == VERMELHO
					  && umNoh->Tio()->mCor == PRETO
					  && umNoh->mPai->mPai->mCor == PRETO
					  && umNoh == umNoh->mPai->mEsq
					  && umNoh->mPai == umNoh->mPai->mPai->mDir) {
						 umNoh->mCor = PRETO;
						 umNoh->mPai->mPai->mCor = VERMELHO;
						 RotacionarDireita(umNoh);
						 RotacionarEsquerda(umNoh);
					 } else {
						 // Caso 5
						 if (umNoh->mPai->mCor == VERMELHO
						  && umNoh->Tio()->mCor == PRETO
						  && umNoh->mPai->mPai->mCor == PRETO
						  && umNoh == umNoh->mPai->mDir
						  && umNoh->mPai == umNoh->mPai->mPai->mEsq) {
							 umNoh->mCor = PRETO;
							 umNoh->mPai->mPai->mCor = VERMELHO;
							 RotacionarEsquerda(umNoh);
							 RotacionarDireita(umNoh);
						 }
					 }
				 }
			}
		}
		mRaiz->mCor = PRETO;
	}*/
}

// rotação à esquerda, muda a raiz se necessário
void ArvoreRN::RotacionarEsquerda(Noh* umNoh) {
	// Modificado
	Noh* nohAux = umNoh->mDir;
	umNoh->mDir = nohAux->mEsq;
	
	if (nohAux->mEsq != NULL) {
		nohAux->mEsq->mPai = umNoh;
	}
	
	nohAux->mPai = umNoh->mPai;
	
	if (umNoh == mRaiz) {
		mRaiz = nohAux;
	} else if (umNoh == umNoh->mPai->mEsq) {
		umNoh->mPai->mEsq = nohAux;
	} else {
		umNoh->mPai->mDir = nohAux;
	}
	
	nohAux->mEsq = umNoh;
	umNoh->mPai = nohAux;
	
}

// rotação à direita, muda a raiz se necessário
void ArvoreRN::RotacionarDireita(Noh* umNoh) {
	// Modificado
	Noh* nohAux = umNoh->mEsq;
	umNoh->mEsq = nohAux->mDir;
	
	if (nohAux->mDir != NULL) {
		nohAux->mDir->mPai = umNoh;
	}
	
	nohAux->mPai = umNoh->mPai;
	
	if (umNoh == mRaiz) {
		mRaiz = nohAux;
	} else if (umNoh == umNoh->mPai->mEsq) {
		umNoh->mPai->mEsq = nohAux;
	} else {
		umNoh->mPai->mDir = nohAux;
	}
	
	nohAux->mDir = umNoh;
	umNoh->mPai = nohAux;
}

// Escreve o conteúdo da árvore nível a nível
void ArvoreRN::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    filhos.push(mRaiz);
    while (not filhos.empty()) {
        unsigned nroNohsNesteNivel = unsigned(filhos.size());
        for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
            Noh* ptNoh = filhos.front();
            filhos.pop();
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mEsq);
                filhos.push(ptNoh->mDir);
            }
        }
        cout << "\n";
    }
}

// Escreve um nó (ou NIL).
ostream& operator<<(ostream& saida, Noh* ptNoh) {
    static char vetLetrasCores[] = "PV";
    if (ptNoh == NULL)
        saida << "NIL";
    else
        saida << '[' << vetLetrasCores[ptNoh->mCor] << ':' << ptNoh->mChave << '/'
              << ptNoh->mValor << ']';
    return saida;
}

int main() {
    ArvoreRN arvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                arvore.Inserir(chave, valor);
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
