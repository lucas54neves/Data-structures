#include <iostream>

using namespace std;

class Corredor {
friend class Classificacao;
private:
	Corredor* mProximo;
	Corredor* mAnterior;
	int mNumero;
	int mPosicao;
public:
	Corredor() {
		mProximo = NULL;
		mAnterior = NULL;
	}
};

class Classificacao {
private:
	Corredor* mPrimeiro;
	Corretor* mUltimo;
	int QtdLinhaChegada;
	void RemoveTodos();
public:
	Classificacao() {
		QtdLinhaChegada = 0;
		mPrimeiro = NULL;
		mUltimo = NULL;
	}
	~Classificacao() {
		RemoveTodos();
	}
	RemoveTodos() {
		Corredor* aux = mPrimeiro;
		Corredor* temp;

		while (aux != NULL) {
			temp = aux;
			aux = aux->mProximo;
			delete temp;
		}

		QtdLinhaChegada = 0;
		mPrimeiro = NULL;
		mUltimo = NULL;
	}
};