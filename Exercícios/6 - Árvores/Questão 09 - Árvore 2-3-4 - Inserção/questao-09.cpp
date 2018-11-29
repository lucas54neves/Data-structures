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
    // Códigos implementado
    Dado* minimoAux(Noh* raizSub);
    Dado* maximoAux(Noh* raizSub);
    Noh* insereAux(Noh* umNoh, Dado umItem, Dado& itemPromovido);
    Noh* divideNoh(Noh* umNoh, Dado umItem, Dado& itemPromovido);
    void insereEmNohFolhaNaoCheio(Noh* umNoh, Dado umItem);
    void insereEmNohIntermediarioNaoCheio(Noh* umNoh, Noh* novoNoh, Dado itemPromovido);   
public:
    Arvore234() { raiz = NULL; }
    ~Arvore234() { delete raiz; }
    // percorrimento (impressão)
    void percorreEmOrdem();
    // Código implementado
    void insere(Dado umItem);
};

void Arvore234::insere(Dado umItem) {
    // Implementado
    if (raiz == NULL) {
		raiz = new Noh;
		raiz->itens[0] = umItem;
		raiz->folha = true;
		raiz->num = 1;
	} else {
		
	}
}

Noh* Arvore234::insereAux(Noh* umNoh, Dado umItem, Dado& itemPromovido) {
	// Implementado
	
}

Noh* Arvore234::divideNoh(Noh* umNoh, Dado umItem, Dado& itemPromovido) {
	// Implementado
	
}

void Arvore234::insereEmNohFolhaNaoCheio(Noh* umNoh, Dado umItem) {
	// Implementado
	
}

void Arvore234::insereEmNohIntermediarioNaoCheio(Noh* umNoh, Noh* novoNoh, Dado itemPromovido) {
	// Implementado
	
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
        } else if(opcao == 'e') {
            B->percorreEmOrdem();
        }
    } while(opcao != 'q');
    
    
    delete B;    
    
    return 0;
}
