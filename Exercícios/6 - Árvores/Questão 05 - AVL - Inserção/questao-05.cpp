#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

class NohAVL; // declaração avançada

typedef std::string TChave; // chave da árvore
typedef float TValor; // valor da árvore

// Declarações das classes ===================================================

class NohAVL {
    friend class AVL;
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
    private:
        NohAVL (TChave c, const TValor& v);
        ~NohAVL();
        NohAVL* ArrumarBalanceamento();
        void AtualizarAltura();
        void DesalocarFilhosRecursivo();
        int FatorBalanceamento();
        NohAVL* InserirRecursivo(NohAVL* ptNoh);
        NohAVL* RotacionarEsquerda();
        NohAVL* RotacionarDireita();
        void TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo);
        TChave mChave;
        TValor mValor;
        NohAVL* mPtEsq;
        NohAVL* mPtDir;
        NohAVL* mPtPai;
        unsigned int mAltura; // folhas têm altura 1
};

class AVL {
    public:
        AVL();
        ~AVL();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, const TValor& valor);
    private:
        NohAVL* mPtRaiz;
};

// === Classe NohAVL ==============================================================================

using namespace std;

NohAVL::NohAVL(TChave c, const TValor& v) {
    // Modificado
    mChave = c;
    mValor = v;
    mPtEsq = NULL;
    mPtDir = NULL;
    mPtPai = NULL;
    mAltura = 1;
}

NohAVL::~NohAVL() {
	// Modificado
	DesalocarFilhosRecursivo();
}

// Faz as rotações e ajustes necessários inclusive do nó pai. Atualiza a altura.
// Retorna o nó que ficar na posição dele após os ajustes.
NohAVL* NohAVL::ArrumarBalanceamento() {
	// Modificado
	AtualizarAltura();
	
	if (FatorBalanceamento() >= -1 && FatorBalanceamento() <= 1) {
		return this;
	} else if (FatorBalanceamento() > 1 && mPtEsq->FatorBalanceamento() >= 0) {
		return RotacionarDireita();
	} else if (FatorBalanceamento() > 1 && mPtEsq->FatorBalanceamento() < 0) {
		mPtEsq = mPtEsq->RotacionarEsquerda();
		return RotacionarDireita();
	} else if (FatorBalanceamento() < -1 && mPtDir->FatorBalanceamento() >= 0) {
		return RotacionarEsquerda();
	} else { // if (this->FatorBalanceamento() < -1 && this->mPtDir->FatorBalanceamento < 0)
		mPtDir = mPtDir->RotacionarDireita();
		return RotacionarEsquerda();
	}
}

// Calcula e atualiza a altura de um nó.
void NohAVL::AtualizarAltura() {
	// Modificado
	int altEsq = mPtEsq->mAltura;
	int altDir = mPtDir->mAltura;
	mAltura = 1 + max(altEsq, altDir);
}

// Desaloca todos os descendentes.
void NohAVL::DesalocarFilhosRecursivo() {
    // Modificado
    delete mPtEsq;
    delete mPtDir;
}

// Calcula e retorna o fator de balanceamento do nó.
int NohAVL::FatorBalanceamento() {
	// Modificado
	int altEsq = mPtEsq->mAltura;
	int altDir = mPtDir->mAltura;
	return altEsq - altDir;
}

// Insere um nó numa subárvore.
NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh) {
	// Modificado
	if (this->mChave > ptNoh->mChave) {
		this->mPtEsq = this->mPtEsq->InserirRecursivo(ptNoh);	
	} else {
		this->mPtDir = this->mPtDir->InserirRecursivo(ptNoh);
	}
	
	return ArrumarBalanceamento();
}

// Rotaciona a subárvore à direita. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarDireita() {
	// Modificado
	NohAVL* aux = this->mPtEsq;
	
	this->mPtEsq = aux->mPtDir;
	
	if (aux->mPtDir != NULL) {
		aux->mPtDir->mPtPai = this;
	}
	
	aux->mPtPai = this->mPtPai;
	
	if (this->mPtPai == NULL) {
		if (this == this->mPtPai->mPtEsq) {
			this->mPtPai->mPtEsq = aux;
		} else {
			this->mPtPai->mPtDir = aux;
		}
	}
	
	aux->mPtDir = this;
	this->mPtPai = aux;
	
	aux->AtualizarAltura();
	this->AtualizarAltura();
	
	return aux;
}

// Rotaciona a subárvore à esquerda. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarEsquerda() {
	// Modificado
	NohAVL* aux = this->mPtDir;
	this->mPtDir = mPtEsq;
	
	if (aux->mPtEsq != NULL) {
		aux->mPtEsq = this;
	}
	
	if (aux->mPtEsq != NULL) {
		aux->mPtEsq->mPtPai = this;
	}
	
	aux->mPtPai = this->mPtPai;
	
	if (this->mPtPai != NULL) {
		if (this == this->mPtPai->mPtEsq) {
			this->mPtPai->mPtEsq = aux;
		} else {
			this->mPtPai->mPtDir = aux;
		}
	}
	
	aux->mPtEsq = this;
	this->mPtPai = aux;
	
	this->AtualizarAltura();
	aux->AtualizarAltura();
	
	return aux;
}

// Substitui um dos filhos por um novo nó.
void NohAVL::TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo) {
    // Modificado
    
}

// Escreve o conteúdo de um nó no formato [altura:chave/valor].
// Escreve "[]" se o ponteiro recebido for NULL.
std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    return saida;
}

// === Classe AVL =================================================================================
AVL::AVL() {
    // Modificado
    mPtRaiz = NULL;
}

AVL::~AVL() {
	// Modificado
	delete mPtRaiz;
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
// Usado para conferir se a estrutra da árvore está correta.
void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        NohAVL* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

// Insere um par chave/valor na árvore.
void AVL::Inserir(TChave chave, const TValor& valor) {
    // Modificado
    NohAVL* novoNoh = new NohAVL(chave, valor);
    if (mPtRaiz == NULL) {
		mPtRaiz = novoNoh;
	} else {
		mPtRaiz = mPtRaiz->InserirRecursivo(novoNoh);
	}
}

// === Programa ===================================================================================
int main() {
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave, valor);
                break;
            case 'e': // Escrever nós nível a nível
                minhaArvore.EscreverNivelANivel(cout);
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
