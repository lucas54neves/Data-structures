/*
-> Obtenção de um valor em uma dada posição do vetor;
-> Alteração de um valor em uma dada posição do vetor;
-> Busca de um valor no vetor;
-> Ordenação do vetor utilizando um método clássico (ex: bubblesort, mergesort, etc.);
-> Cálculo do produto interno;
-> Multiplicação dos valores do vetor por um número inteiro qualquer;
-> Remoção de elementos duplicados do vetor;
-> Remoção de um valor em uma dada posição do vetor;
-> Diferença de vetores: recebe um vetor como parâmetro e remove do vetor atual todos os elementos que estejam no vetor recebido;
-> Redimensionamento do vetor;
-> Inserção de um valor em uma dada posição do vetor - nesse caso a inserção deverá verificar se o vetor não precisa ser redimensionado antes de fazer a tarefa;
-> Suporte ao conceito de capacidade e tamanho - por exemplo, o vetor terá capacidade para 1000 elementos, mas possui apenas 100 armazenados, assim ele suportará a inserção de 900 novos elementos,
sem precisar de redimensionamento. 
 */
 
 // Função retorna um valor
 // Procedimento altera o estado, não retorna um valor
 // Funções: o nome descreve o resultado
 // Procedimentos: o nome é um verbo no infinitivo (ou imperativo) que descreve a ação

#include <iostream>

typedef float data;

using namespace std;

class Vetor {
    public:
        // Construtor padrão
        Vetor(unsigned capacidade)
        : mVetDados(new data[capacidade]),
          mTamanho(capacidade),
          mCapacidade(capacidade) { // inicializacao
        }
        
        // Construtor de cópia
        Vetor(Vetor& vet) {
            mTamanho = vet.mTamanho;
            mCapacidade = 0;
            mVetDados = new data[mTamanho];
            for (unsigned i = 0; i < mTamanho; ++i) {
                mVetDados[i] = vet.mVetDados[i];
            }
        }

        // Destrutor
        ~Vetor() {
            delete[] mVetDados;
            mTamanho = 0;
            mCapacidade = 0;
        }
        // Metodo para copiar vetor (vetor1 = vetor2)
        // Metodo para verificar equivalencia (vetor1 == vetor2)

        // Retorna o valor de uma posição dada
        data Valor(unsigned pos) {
            data valor = mVetDados[pos];
            return valor;
        }
        
        // Verifica se um valor existe no vetor
        bool Existe(data valor) {
            for (unsigned i = 0; i < mTamanho; ++i) {
                if (mVetDados[i] == valor) {
                    return true;
                }
            }
            return false;
        }

        // Altera um valor de uma posição dada
        void AlteraValor(unsigned pos, data valor) {
            mVetDados[pos] = valor;
        }

        // Retorna uma posição de um valor dado
        unsigned Posicao(data valor) {
            if (Existe(valor)) {
                for (unsigned i = 0; i < mTamanho; ++i) {
                    if (mVetDados[i] == valor) {
                        return i;
                    }
                }
            }
        }

        // Ordena o vetor com o método QuickSort
        void OrdenaVetor(unsigned inicio, unsigned fim) {
            unsigned i, j;
            data pivo, aux;
            i = inicio;
            j = fim - 1;
            pivo = mVetDados[(inicio + fim) / 2];
            
            while (i <= j) {
                while (mVetDados[i] < pivo && i < fim) {
                    i++;
                }
                
                while (mVetDados[j] > pivo && j > inicio) {
                    j--;
                }
                
                if (i <= j) {
                    aux = mVetDados[i];
                    mVetDados[i] = mVetDados[j];
                    mVetDados[j] = aux;
                    i++;
                    j--;
                }
                
                if (j > inicio) {
                    OrdenaVetor(inicio, j + 1);
                }
                
                if (i < fim) {
                    OrdenaVetor(i, fim);
                }
            }
        }

        // Retorna o produto interno entre dois vetores
        data ProdutoInterno(Vetor& outroVetor) {
            data valor = 0;
            for (unsigned i = 0; i < this->mTamanho; ++i) {
                valor = valor + (this->mVetDados[i] * outroVetor.mVetDados[i]);
            }
            return valor;
        }

        // Multiplica todos os valores do vetor por um número dado
        void MultiplicaNumero(data num) {
            for (unsigned i = 0; i < mTamanho; ++i) {
                mVetDados[i] = mVetDados[i] * num;
            }
        }

        // Remove os valores duplicados do vetor
        void RemoveDuplicados() {
            for (unsigned pos1 = 0; pos1 < mTamanho; pos1++) {
                for (unsigned pos2 = pos1 + 1; pos2 < mTamanho; pos2++) {
                    if (mVetDados[pos1] == mVetDados[pos2]) {
                        RemoveValor(pos2);
                    }
                }
            }
        }

        // Remove o valor de uma posição dada
        void RemoveValor(unsigned pos) {
            MoveEsquerda(pos);
            mTamanho--;
            mCapacidade++;
        }

        // Sobrecarga do operador - para a implementação da diferença de vetores
        Vetor& operator-(const Vetor& outroVetor) {
            for (unsigned pos1 = 0; pos1 < mTamanho; pos1++) {
                for (unsigned pos2 = 0; pos2 < outroVetor.mTamanho; pos2++) {
                    if (mVetDados[pos1] == outroVetor.mVetDados[pos2]) {
                        RemoveValor(pos1);
                    }
                }
            }
            return *this;
        }

        void Redimensionamento() {
            data* aux = new data[mTamanho * 2];
            for (unsigned i = 0; i < mTamanho; i++) {
                aux[i] = mVetDados[i];
            }
            delete[] mVetDados;
            mCapacidade = mTamanho * 2;
            mVetDados = aux;
        }
        
        bool Cheio() {
            if (mCapacidade == 0) {
                return true;
            } else {
                return false;
            }
        }

        void InsereInicio(data valor) {
            MoveDireita(0);
            mVetDados[0] = valor;
            ++mTamanho;
            mCapacidade--;
        }

        void InsereFinal(data valor) {
            mVetDados[mTamanho] = valor;
            ++mTamanho;
            mCapacidade--;
        }

        void InserePos(unsigned pos, data valor) {
            if (Cheio()) {
                Redimensionamento();
            }
            if (pos == 0) {
                InsereInicio(valor);
            } else if (pos == mTamanho) {
                InsereFinal(valor);
            } else {
                MoveDireita(pos);
                mVetDados[pos] = valor;
                mTamanho++;
                mCapacidade--;
            }
        }

        void MoveDireita(unsigned pos) {
            for (unsigned i = mTamanho; i > pos; --i) {
                mVetDados[i] = mVetDados[i-1];
            }
        }

        void MoveEsquerda(unsigned pos) {
            for (unsigned i = pos; i < (mTamanho - 1); ++i) {
                mVetDados[i] = mVetDados[i+1];
            }
        }

        unsigned Tamanho() {
            return mTamanho;
        }
        
        void Imprime() {
            cout << "Vetor = [";
            for (unsigned i = 0; i < mTamanho; ++i) {
                cout << mVetDados[i];
                if (i != mTamanho - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        }
    private:
        data* mVetDados;
        unsigned mTamanho;
        unsigned mCapacidade;
};

int main () {
    unsigned capacidade;
    cout << "Entre com a capacidade do primeiro vetor" << endl;
    cin >> capacidade;
    Vetor vetor1(capacidade);
    data valor;

    for (unsigned i = 0; i < capacidade; ++i) {
        cout << "Entre com o valor para o vetor" << endl;
        cin >> valor;
        vetor1.AlteraValor(i, valor);
    }
    
    cout << "Entre com a capacidade do segundo vetor" << endl;
    cin >> capacidade;
    Vetor vetor2(capacidade);
    
    for (unsigned i = 0; i < capacidade; ++i) {
        cout << "Entre com o valor para o vetor" << endl;
        cin >> valor;
        vetor2.AlteraValor(i, valor);
    }
    
    cout << "Diferença dos vetores" << endl;
    vetor1 = vetor1 - vetor2;
    vetor1.Imprime();

    return 0;
}
