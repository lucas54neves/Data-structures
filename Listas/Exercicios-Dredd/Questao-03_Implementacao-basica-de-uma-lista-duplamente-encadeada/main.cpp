#include <iostream>

using namespace std;

class Aluno {
    friend class Lista;
    public:
        Aluno(unsigned int matricula, string nome) {
            mMatricula = matricula;
            mNome = nome;
            mProximo = nullptr;
            mAnterior = nullptr;
        }
    private:
        unsigned int mMatricula;
        string mNome;
        Aluno* mProximo;
        Aluno* mAnterior;
};

class Lista {
    public:
        Lista() {
            mPrimeiro = nullptr;
            mUltimo = nullptr;
            mTamanho = 0;
        }
        
        ~Lista() {
            RemoverTodos();
        }
        
        bool Vazia() {
            return (mTamanho == 0);
        }
        
        bool Existe(unsigned int matricula) {
            Aluno* aux = mPrimeiro;
            
            while (aux != nullptr) {
                if (aux->mMatricula == matricula) {
                    return true;
                }
                aux = aux->mProximo;
            }
            
            return false;
        }
        
        void Inserir (unsigned int matricula, string nome) {
            Aluno* novo = new Aluno(matricula, nome);
            if (Vazia()) {
                mPrimeiro = novo;
                mUltimo = novo;
            } else {
                novo->mProximo = mPrimeiro;
                mPrimeiro->mAnterior = novo;
                mPrimeiro = novo;
            }
            ++mTamanho;
        }
        
        void Remover (unsigned int matricula) {
            if (Existe(matricula)) {
                Aluno* temp = mPrimeiro;
                
                while (temp->mMatricula != matricula) {
                    temp = temp->mProximo;
                }
                
                if (temp == mPrimeiro) {
                    mPrimeiro = temp->mProximo;
                    mPrimeiro->mAnterior = nullptr;
                } else if (temp == mUltimo) {
                    mUltimo = temp->mAnterior;
                    mUltimo->mProximo = nullptr;
                } else {
                    temp->mAnterior->mProximo = temp->mProximo;
                    temp->mProximo->mAnterior = temp->mAnterior;
                }
                
                delete temp;
                --mTamanho;
                } else {
                    cout << "ERRO" << endl;
                }
        }
        
        void EscreverDiretamente() {
            Aluno* aux = mPrimeiro;
            
            while (aux != nullptr) {
                cout << aux->mMatricula << " " << aux->mNome << " ";
                aux = aux->mProximo;
            }
            
            cout << endl;
        }
        
        void EscreverInversamente() {
            Aluno* aux = mUltimo;
            
            while (aux != nullptr) {
                cout << aux->mMatricula << " " << aux->mNome << " ";
                aux = aux->mAnterior;
            }
            cout << endl;
        }
    private:
        Aluno* mPrimeiro;
        Aluno* mUltimo;
        unsigned int mTamanho;
        
        void RemoverTodos() {
            Aluno* aux = mPrimeiro;
            Aluno* temp;
            
            while (aux != mUltimo) {
                aux = aux->mProximo;
                temp = aux;
                delete temp;
            }
            delete aux;
            
            mPrimeiro = nullptr;
            mUltimo = nullptr;
        }
};

int main() {
    Lista minhaLista;
    string opcao, nome;
    unsigned int matricula;
    
    cin >> opcao;
    
    while (opcao != "t") {
        if (opcao == "i") {
            cin >> matricula >> nome;
            minhaLista.Inserir(matricula, nome);
        } else if (opcao == "r") {
            cin >> matricula;
            minhaLista.Remover(matricula);
        } else if (opcao == "ed") {
            minhaLista.EscreverDiretamente();
        } else if (opcao == "er") {
            minhaLista.EscreverInversamente();
        }
        cin >> opcao;
    }

    return 0;
}
