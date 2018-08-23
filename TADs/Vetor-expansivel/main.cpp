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

#include <iostream>

typedef float data;

using namespace std;

class Vetor {
    public:
        Vetor(unsigned capacidade)
        : mVetDados(new data[capacidade]), mTamanho(capacidade),
          mCapacidade(capacidade){ // inicializacao
        }

        ~Vetor() {
            delete[] mVetDados;
            mTamanho = 0;
            mCapacidade = 0;
        }
        // Metodo para copiar vetor (vetor1 = vetor2)
        // Metodo para verificar equivalencia (vetor1 == vetor2)

        data ObtemValor(unsigned pos) {
            data valor = mVetDados[pos];
            return valor;
        }

        void AlteraValor(unsigned pos, data valor) {
            mVetDados[pos] = valor;
        }

        unsigned BuscaValor(int valor) {
            for (unsigned i = 0; i < mTamanho; ++i) {
                if (mVetDados[i] == valor) {
                    return i;
                }
            }
            return -1;
        }

        void OrdenaVetor(unsigned inicio, unsigned fim) {
            unsigned i, j, pivo, aux;
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

        data ProdutoInterno(Vetor outroVetor) {
            data valor = 0;
            for (unsigned i = 0; i < mTamanho; ++i) {
                valor = valor + (mVetDados[i] * outroVetor.mVetDados[i]);
            }
            return valor;
        }

        void MultiplicaNumero(int num) {
            for (unsigned i = 0; i < mTamanho; ++i) {
                mVetDados[i] = mVetDados[i] * num;
            }
        }

        void RemoveDuplicados() {
            for (unsigned pos1 = 0; pos1 < mTamanho; pos1++) {
                for (unsigned pos2 = pos1 + 1; pos2 < mTamanho; pos2++) {
                    if (mVetDados[pos1] == mVetDados[pos2]) {
                        RemoveValor(pos2);
                    }
                }
            }
        }

        void RemoveValor(unsigned pos) {
            for (unsigned i = pos; i < (mTamanho - 1); ++i) {
                mVetDados[i] = mVetDados[i+1];
            }
            mTamanho--;
        }

        void DiferencaVetores(Vetor outroVetor) {
            for (unsigned pos1 = 0; pos1 < mTamanho; pos1++) {
                for (unsigned pos2 = 0; pos2 < outroVetor.mTamanho; pos2++) {
                    if (mVetDados[pos1] == outroVetor.mVetDados[pos2]) {
                        RemoveValor(pos1);
                    }
                }
            }
        }

        //void Redimensionamento() {}

        void InsereValor(unsigned pos, data valor) {
            for (unsigned i = mTamanho; i > pos; --i) {
                mVetDados[i+1] = mVetDados[i];
            }
            mVetDados[pos] = valor;
            mTamanho++;
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
    Vetor vetor(capacidade);
    data valor;

    for (unsigned i = 0; i < capacidade; ++i) {
        cout << "Entre com o valor" << endl;
        cin >> valor;
        vetor.AlteraValor(i, valor);
    }
    vetor.Imprime();
    vetor.OrdenaVetor(0, vetor.Tamanho());
    vetor.Imprime();

    return 0;
}
