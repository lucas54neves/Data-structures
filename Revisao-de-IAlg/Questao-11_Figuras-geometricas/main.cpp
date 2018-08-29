#include <iostream>
#include <cmath>

using namespace std;

struct Figura {
    char tipo;
    string nome;
    float area;
    float perimetro;
};

void Calculo (Figura dados[], int pos) {
    if (dados[pos].tipo == 'C') {
        dados[pos].nome = "Circulo";
        float raio;
        cin >> raio;
        dados[pos].perimetro = 2.0*(M_PI)*raio;
        dados[pos].area = (M_PI)*(pow(raio,2));
    } else if (dados[pos].tipo == 'R') {
        dados[pos].nome = "Retangulo";
        float base;
        float altura;
        cin >> base >> altura;
        dados[pos].area = base*altura;
        dados[pos].perimetro = 2.0*(base+altura);
    } else if (dados[pos].tipo == 'T') {
        dados[pos].nome = "Triangulo";
        float lado1;
        float lado2;
        float lado3;
        cin >> lado1 >> lado2 >> lado3;
        float p = ((lado1+lado2+lado3)/2.0);
        dados[pos].area = sqrt(p*(p-lado1)*(p-lado2)*(p-lado3));
        dados[pos].perimetro = lado1+lado2+lado3;
    }
}

int main() {
    Figura dados[5];
    
    for (int i = 0; i < 5; ++i) {
        cin >> dados[i].tipo;
        Calculo(dados, i);
    }
    
    for (int i = 0; i < 5; ++i) {
        cout << dados[i].nome << " " << dados[i].perimetro << " " << dados[i].area << endl;
    }
    
    return 0;
}
