// Árvore 2-3-4  
// (Árvore B em memória, com nós com capacidade para 2, 3 ou 4 filhos)
// Estruturas de Dados - 2018/2
// Código by Joukim

#include <iostream>

using namespace std;

// constantes para verificação
const int MAXITENS = 3;
const int MINITENS = 1;
const int MAXFILHOS = 4;

// posição do elemento do meio (o que sobe para página pai em caso de estouro
const int MEIO = 1; 

typedef float Dado;

class Noh {
friend class Arvore234;
private:
    bool folha;
    int num; // número de itens armazenadas no nó
    Dado itens[MAXITENS];
    Noh* filhos[MAXFILHOS];
    Noh* pai;
public:
    Noh();
    ~Noh();
};

Noh::Noh() {
    num = 0;
    folha = false;
    for (int i = 0; i < MAXFILHOS; i++) {
        filhos[i] = NULL;
    }
}

Noh::~Noh() {
    for (int i = 0; i < num+1; i++) {
        delete filhos[i];
    }
}

class Arvore234 {
private:
    Noh* raiz;
    void percorreEmOrdemAux(Noh* atual, int nivel);
    // Códigos Implementado
    Dado* minimoAux(Noh* raizSub);
    Dado* maximoAux(Noh* raizSub);
    Noh* insereAux(Noh* umNoh, Dado umItem, Dado& itemPromovido);
    Noh* divideNoh(Noh* umNoh, Dado umItem, Dado& itemPromovido);
    void insereEmNohFolhaNaoCheio(Noh* umNoh, Dado umItem);
    void insereEmNohIntermediarioNaoCheio(Noh* umNoh, Noh* novoNoh, Dado itemPromovido);
public:
    Arvore234() { raiz = NULL; }
    ~Arvore234() { delete raiz; }
    void percorreEmOrdem();
    // Códigos Implementado
    void insere(Dado umItem);
    Dado* minimo();
    Dado* maximo();
};

void Arvore234::insere(Dado umItem) {
    // Implementado
    if (raiz == NULL) {
		raiz = new Noh;
		raiz->folha = true;
		raiz->itens[0] = umItem;
		raiz->num = 1;
	} else {
		Dado itemPromovido;
		Noh* novoNoh = insereAux(raiz, umItem, itemPromovido);
		
		if (novoNoh) {
			Noh* antigaRaiz = raiz;
			raiz = new Noh;
			
			raiz->itens[0] = itemPromovido;
			raiz->num = 1;
			raiz->filhos[0] = antigaRaiz;
			raiz->filhos[1] = novoNoh;
		}
	}
}

Noh* Arvore234::insereAux(Noh* umNoh, Dado umItem, Dado& itemPromovido) {
	if (umNoh->folha) {
		if (umNoh->num < MAXITENS) {
			insereEmNohFolhaNaoCheio(umNoh, umItem);
			return NULL;
		} else {
			Noh* novoNoh = divideNoh(umNoh, umItem, itemPromovido);
			
			if (umItem <= umNoh->itens[MEIO]) {
				insereEmNohFolhaNaoCheio(umNoh, umItem);
			} else {
				insereEmNohFolhaNaoCheio(novoNoh, umItem);
			}
			return novoNoh;
		}
	} else {
		int i = umNoh->num - 1;
		while (i >= 0 && umNoh->itens[i] > umItem) {
			i--;
		}
		
		Noh* nohAux = insereAux(umNoh->filhos[i+1], umItem, itemPromovido);
		
		if (nohAux) {
			Dado itemAux = itemPromovido;
			
			if (umNoh->num < MAXITENS) {
				insereEmNohIntermediarioNaoCheio(umNoh, nohAux, itemAux);
				return NULL;
			} else {
				Noh* novoNoh = divideNoh(umNoh, umItem, itemPromovido);
				
				if (itemAux <= umNoh->itens[MEIO]) {
					insereEmNohIntermediarioNaoCheio(umNoh, nohAux, itemAux);
				} else {
					insereEmNohIntermediarioNaoCheio(novoNoh, nohAux, itemAux);
				}
				
				return novoNoh;
			}
		}
	}
	return NULL;
}

Noh* Arvore234::divideNoh(Noh* umNoh, Dado umItem, Dado& itemPromovido) {
	itemPromovido = umNoh->itens[MEIO];
	Noh* novoNoh = new Noh;
	
	novoNoh->folha = umNoh->folha;
	novoNoh->itens[0] = umNoh->itens[MEIO+1];
	
	umNoh->num = 1;
	novoNoh->num = 1;
	
	if (!umNoh->folha) {
		for (int i = 0; i < MEIO + 1; i++) {
			novoNoh->filhos[i] = umNoh->filhos[MEIO+1+i];
		}
	}
	
	return novoNoh;
}

void Arvore234::insereEmNohFolhaNaoCheio(Noh* umNoh, Dado umItem) {
	int i = umNoh->num - 1;
	
	while (i >= 0 && umNoh->itens[i] > umItem) {
		umNoh->itens[i+1] = umNoh->itens[i];
		i--;
	}
	
	umNoh->itens[i+1] = umItem;
	umNoh->num++;
}

void Arvore234::insereEmNohIntermediarioNaoCheio(Noh* umNoh, Noh* novoNoh, Dado itemPromovido) {
	int i = umNoh->num - 1;
	
	while (i >= 0 && umNoh->itens[i] > itemPromovido) {
		umNoh->itens[i+1] = umNoh->itens[i];
		umNoh->filhos[i+2] = umNoh->filhos[i+1];
		i--;
	}
	
	umNoh->itens[i+1] = itemPromovido;
	umNoh->filhos[i+2] = novoNoh;
	umNoh->num++;
}

Dado* Arvore234::minimo() {
    // Implementado
    if (raiz == NULL) {
		return NULL;
	} else {
		return minimoAux(raiz);
	}
}

Dado* Arvore234::minimoAux(Noh* raizSub) {
	// Implementado
	if (raizSub->folha) {
		return &(raizSub->itens[0]);
	} else {
		return minimoAux(raizSub->filhos[0]);
	}
}

Dado* Arvore234::maximo() {
	// Implementado
    if (raiz == NULL) {
		return NULL;
	} else {
		return maximoAux(raiz);
	}
}

Dado* Arvore234::maximoAux(Noh* raizSub) {
	// Implementado
	int pos = raizSub->num - 1;
	if (raizSub->folha) {
		return &(raizSub->itens[pos]);
	} else {
		return maximoAux(raizSub->filhos[pos+1]);
	}
}

void Arvore234::percorreEmOrdem() {
    percorreEmOrdemAux(raiz,0);        
    cout<< endl;
}

void Arvore234::percorreEmOrdemAux(Noh* umNoh, int nivel) {
    int i;
    for (i = 0; i < umNoh->num; i++) {
        // se nó não é folha, imprima os dados do filho i
        // antes de imprimir o item i
        if (not umNoh->folha) {
            percorreEmOrdemAux(umNoh->filhos[i], nivel+1); 
        }
        cout << umNoh->itens[i] << '/' << nivel << ' ';
    }
 
    // Imprima os dados do último filho
    if (not umNoh->folha) {
        percorreEmOrdemAux(umNoh->filhos[i], nivel+1);   
    }
}


// =========================== Programa ================================
int main() {
    Arvore234* B = new Arvore234;
    
    char opcao;
    float valor;
    
    do {
        cin >> opcao;
        if (opcao == 'i') {
            cin >> valor;
            B->insere(valor);
        } if (opcao == 'l') {
            cin >> valor;
            cout << *B->minimo() << endl;
        } if (opcao == 'h') {
            cin >> valor;
            cout << *B->maximo() << endl;
        } else if(opcao == 'e') {
            B->percorreEmOrdem();
        }
    } while(opcao != 'q');
    
    
    delete B;    
    
    return 0;
}
