#include <iostream>
#include <fstream>

using namespace std;

struct Tarefa {
    char descricao[40];
    int dia, mes, ano;
};

void Comparacao(int dia, int mes, int ano) {
    ifstream arquivo ("o-que-tem-para-hoje", ios::binary);
    if (arquivo) {
        cout << "Arquivo abriu" << endl;
        Tarefa atividade;
        while (!arquivo.eof()) {
            cout << "Arquivo está sendo lido" << endl;
            arquivo.read((char*) (&atividade), sizeof(Tarefa));
            if (atividade.dia == dia && atividade.mes == mes && atividade.ano == ano) {
                cout << "Datas iguais" << endl;
                for (int i = 0; i < 40; ++i) {
                    cout << atividade.descricao[i];
                }
                cout << endl;
            }
        }
    }
}

int main() {
    int  dia, mes, ano;
    cin >> dia >> mes >> ano;
    Comparacao(dia, mes, ano);
    return 0;
}
