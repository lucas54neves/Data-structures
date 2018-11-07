#ifndef VETOR_HPP
#define VETOR_HPP

typedef float data;

class Vetor {
    public:
        // Construtor padrão
        Vetor(unsigned capacidade);
        // Construtor de cópia
        Vetor(Vetor& vet);
        // Destrutor
        ~Vetor();
        // Retorna o valor de uma posição dada
        data Valor(unsigned pos);
        // Verifica se um valor existe no vetor
        bool Existe(data valor);
        // Altera um valor de uma posição dada
        void AlteraValor(unsigned pos, data valor);
        // Retorna uma posição de um valor dado
        unsigned Posicao(data valor);
        // Ordena o vetor com o método QuickSort
        void OrdenaVetor(unsigned inicio, unsigned fim);
        // Sobrecarga do operador * para o produto interno entre dois vetores
        data operator*(const Vetor& outroVetor);
        // Sobrecarga do operador * para a multiplicação do vetor por um número
        Vetor& operator*(const data& num);
        // Remove os valores duplicados do vetor
        void RemoveDuplicados();
        // Remove o valor de uma posição dada
        void RemoveValor(unsigned pos);
        // Sobrecarga do operador - para a implementação da diferença de vetores
        Vetor& operator-(const Vetor& outroVetor);
        // Redimensionamento do vetor
        void Redimensionamento();
        // Verifica se o vetor está cheio
        bool Cheio();
        // Insere no início do vetor
        void InsereInicio(data valor);
        // Insere no final do vetor
        void InsereFinal(data valor);
        // Insere um valor em uma dada posição do vetor
        void InserePos(unsigned pos, data valor);
        // Move os valores à direita de uma posição
        void MoveDireita(unsigned pos);
        // Move os valores à esquerda de uma posição
        void MoveEsquerda(unsigned pos);
        // Retorna o tamanho do vetor
        unsigned Tamanho();
        // Imprime o vetor
        void Imprime();
    private:
        data* mVetDados;
        unsigned mTamanho;
        unsigned mCapacidade;
};

#endif
