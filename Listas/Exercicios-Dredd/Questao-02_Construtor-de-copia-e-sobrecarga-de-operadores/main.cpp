#include <iostream>

using namespace std;

typedef string Texto;

class noh {
        friend class lista;
    private:
        const Texto palavra;
        noh* proximo;
    public:
        noh(Texto p);
};

noh::noh(Texto p) : palavra(p) {
    proximo = NULL;
}


class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        lista(const lista& umaLista);
        lista& operator=(const lista& umaLista);
        lista operator+(const lista& umaLista) const;
        ~lista();
        void removerTodos();
        void insere(Texto palavra);
        bool vazia();
        void insereNoFim(Texto palavra);
        void imprime() const;
};

// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

void lista::removerTodos() {
    noh* inter = primeiro;
    noh* removido;
    
    while (inter != NULL) {
        removido = inter;
        inter = inter->proximo;
        delete removido;
    }
    delete inter;
    
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// insere no inicio da lista
void lista::insere(Texto palavra) {
    noh* novo = new noh(palavra);
    novo->proximo = primeiro;
    primeiro = novo;
    if (tamanho == 0)
        ultimo = novo;
    ++tamanho;
}

bool lista::vazia() {
    return (tamanho == 0);
}

void lista::insereNoFim(Texto palavra) {
    noh* novo = new noh(palavra);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    ++tamanho;
}

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() const {
    noh* iter = primeiro;
    while (iter != NULL) {
        cout << iter->palavra << " ";
        iter = iter->proximo;
    }
    cout << endl;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
    // IMPLEMENTAR
    removerTodos();
    noh* inter = umaLista.primeiro;
    while (inter != NULL) {
        insereNoFim(inter->palavra);
        inter = inter->proximo;
    }
}

// sobrecarga do operador de atribuição - retorna a própria lista
lista& lista::operator=(const lista& umaLista) {
    // IMPLEMENTAR
    removerTodos();
    noh* inter = umaLista.primeiro;
    while (inter!= NULL) {
        insereNoFim(inter->palavra);
        inter = inter->proximo;
    }
    return *this;
}

// concatenacao de listas
lista lista::operator+(const lista& umaLista) const {
    // IMPLEMENTAR
    lista novaLista;
    
    noh* inter = primeiro;
    while (inter != NULL) {
        novaLista.insereNoFim(inter->palavra);
        inter = inter->proximo;
    }
    
    inter = umaLista.primeiro;
    while (inter != NULL) {
        novaLista.insereNoFim(inter->palavra);
        inter = inter->proximo;
    }
        
    return novaLista;
}

int main() { // NÃO MODIFIQUE!
    lista listaA;
    lista listaB;
    string opcao;
    string palavra;
    char idLista;
    do {
        cin >> opcao;
        if (opcao == "i") {
            cin >> idLista >> palavra;
            if (idLista == 'a')
                listaA.insere(palavra);
            else
                listaB.insere(palavra);
        }
        else if (opcao == "a=b") {
            listaA = listaB;
        }
        else if (opcao == "b=a") {
            listaB = listaA;
        }
        else if (opcao == "s") {
            lista soma = listaA + listaB;
            soma.imprime();
        }
        else if (opcao == "e") {
            cin >> idLista;
            if (idLista == 'a')
                listaA.imprime();
            else
                listaB.imprime();
        }
    } while (opcao != "t");
    return 0;
}
