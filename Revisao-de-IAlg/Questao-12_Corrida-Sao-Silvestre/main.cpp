#include <iostream>

using namespace std;

struct Corredor {
    int codigo;
    string nome;
    int idade;
    float peso;
    char sexo;
    float distanciaTotal = 0;
    float tempoTotal = 0;
    int totalDias = 0;
    float tempoMedio;
};

int CodigoPos(Corredor dados[], int codigo, int qtd) {
    for (int i = 0; i < qtd; ++i) {
        if (dados[i].codigo == codigo) {
            return i;
        }
    }
    return 0;
}

void Treinamento(Corredor dados[], int qtd) {
    int codigo, pos, dia;
    float distancia, tempo;
    cin >> dia;
    while (dia != -1) {
        cin >> codigo >> distancia >> tempo;
        pos = CodigoPos(dados, codigo, qtd);
        dados[pos].distanciaTotal = dados[pos].distanciaTotal + distancia;
        dados[pos].tempoTotal = dados[pos].tempoTotal + tempo;
        dados[pos].totalDias = dados[pos].totalDias + 1;
        cin >> dia;
    }
}

void Cadastro(Corredor dados[], int qtd) {
    for (int i = 0; i < qtd; ++i) {
        cin >> dados[i].codigo >> dados[i].nome >> dados[i].idade >> dados[i].peso >> dados[i].sexo;
    }
    Treinamento(dados, qtd);
}

void DistanciaTotal(Corredor dados[], int qtd) {
    int maiorIdade = dados[0].idade, pos = 0;
    for (int i = 1; i < qtd; ++i) {
        if (maiorIdade < dados[i].idade && dados[i].sexo == 'M') {
            maiorIdade = dados[i].idade;
            pos = i;
        }
    }
    cout << dados[pos].nome << " " << dados[pos].distanciaTotal << endl;
}

void MaiorFrequencia(Corredor dados[], int qtd) {
    int maiorFrequencia = dados[0].totalDias, pos = 0;
    for (int i = 1; i < qtd; ++i) {
        if (maiorFrequencia < dados[i].totalDias && dados[i].sexo == 'M') {
            maiorFrequencia = dados[i].totalDias;
            pos = i;
        }
    }
    cout << dados[pos].nome << " " << dados[pos].idade << endl;
}

void CalculaTempoMedio(Corredor dados[], int qtd) {
    for (int i = 0; i < qtd; ++i) {
        dados[i].tempoMedio = (dados[i].tempoTotal / dados[i].totalDias);
    }
}

void DadosCadaAtleta(Corredor dados[], int qtd) {
    CalculaTempoMedio(dados, qtd);
    for (int i = 0; i < qtd; ++i) {
        cout << dados[i].nome << " " << dados[i].tempoMedio << endl;
    }
}

int main() {
    int qtd;
    cin >> qtd;
    Corredor dados[qtd];
    
    Cadastro(dados, qtd);
    DistanciaTotal(dados, qtd);
    MaiorFrequencia(dados, qtd);
    DadosCadaAtleta(dados, qtd);
    
    return 0;
}
