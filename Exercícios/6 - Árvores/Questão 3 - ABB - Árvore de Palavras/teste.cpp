#include <iostream>
#include <fstream>

using namespace std;

typedef string Dado;

enum Posicao {DIR, ESQ};

class Noh {
	friend class ABB;
	private:
		Dado mValor;
		int mPosicao;
		Noh* mPtPai;
		Noh* mPtEsq;
		Noh* mPtDir;
		Noh* mPtProximo;
	public:
		Noh(Dado d = 0, int pos = 0);
		~Noh();
};

class ABB {
	private:
		Noh* mPtRaiz;
	public:
		ABB();
		~ABB();
		void Inserir(Dado d, int pos);
		void Buscar(Dado d);
};

Noh::Noh(Dado d, int pos)
	: mValor(d), mPosicao(pos), mPtPai(NULL), mPtEsq(NULL), mPtDir(NULL), mPtProximo(NULL) {
}

Noh::~Noh() {
	delete mPtEsq;
	delete mPtDir;
}

ABB::ABB() 
	: mPtRaiz(NULL) {
}

ABB::~ABB() {
	delete mPtRaiz;
}

void ABB::Inserir(Dado d, int pos) {
	Noh* novo = new Noh(d, pos);
    if (mPtRaiz == NULL) {
        mPtRaiz = novo;
    } else {
        Posicao posInsercao;
        Noh* atual = mPtRaiz;
        Noh* anterior;
        bool achou = false;
        while (atual != NULL && achou == false) {
            anterior = atual;
            if (atual->mValor > d && atual->mValor != d) {
                atual = atual->mPtEsq;
                posInsercao = ESQ;
            } else if (atual->mValor < d && atual->mValor != d) {
                atual = atual->mPtDir;
                posInsercao = DIR;
            } else {
				achou = true;
				// Encadeamento
				while (atual->mPtProximo != NULL) {
					atual = atual->mPtProximo;
				}
				atual->mPtProximo = novo;
			}
        }
        if (achou == false) {
			novo->mPtPai = anterior;
			if (posInsercao == DIR) {
				anterior->mPtDir = novo;
			} else {
				anterior->mPtEsq = novo;
			}
		}
    }
}

void ABB::Buscar(Dado d) {
	Noh* atual = mPtRaiz;
	bool achou = false;
    while (atual != NULL) {
        if (atual->mValor == d) {
			// retorna posicoes
			achou = true;
			while (atual != NULL) {
				cout << atual->mPosicao << " ";
				atual = atual->mPtProximo;
			}
        } else if (atual->mValor > d) {
            atual = atual->mPtEsq;
        } else {
            atual = atual->mPtDir;
        }
    }
	// retorna -1 caso nao encontrar a palavra
	if (achou == false) {
		cout << "-1" << endl;
	}
}

int main() {
	ABB minhaArvore;
	int pos = 1;
	Dado palavra;
	cin >> palavra;
	// enquanto der pra ler palavras fazer:
	// ler no arquivo
	// inserir a palavra passando d e pos
	// incrementar a pos
	ifstream arquivo;
	arquivo.open("entrada.txt");
	string d;
	if (arquivo) {
		while (arquivo >> d) {
			minhaArvore.Inserir(d, pos);
			pos++;
		}
	}
	minhaArvore.Buscar(palavra);
}
