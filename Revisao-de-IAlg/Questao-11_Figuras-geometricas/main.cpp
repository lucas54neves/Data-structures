#include <iostream>
#include <cmath>

using namespace std;

struct Figura {
    string nome;
    float area;
    float perimetro;
    char tipo;
} fig1, fig2, fig3, fig4, fig5;

void Calculo (Figura& fig) {
    if (fig.tipo == 'C') {
        fig.nome = "Circulo";
        float raio;
        cin >> raio;
        fig.perimetro = 2.0*(M_PI)*raio;
        fig.area = (M_PI)*(pow(raio,2));
    } else if (fig.tipo == 'R') {
        fig.nome = "Retangulo";
        float base;
        float altura;
        cin >> base >> altura;
        fig.area = base*altura;
        fig.perimetro = 2.0*(base+altura);
    } else if (fig.tipo == 'T') {
        fig.nome = "Triangulo";
        float lado1;
        float lado2;
        float lado3;
        cin >> lado1 >> lado2 >> lado3;
        int p = ((lado1+lado2+lado3)/2.0);
        fig.area = sqrt(p*(p-lado1)*(p-lado2)*(p-lado3));
        fig.perimetro = lado1+lado2+lado3;
    }
}

int main() {
    cin >> fig1.tipo;
    Calculo(fig1);
    cin >> fig2.tipo;
    Calculo(fig2);
    cin >> fig3.tipo;
    Calculo(fig3);
    cin >> fig4.tipo;
    Calculo(fig4);
    cin >> fig5.tipo;
    Calculo(fig5);
    cout << fig1.nome << " " << fig1.perimetro << " " <<fig1.area << endl;
    cout << fig2.nome << " " << fig2.perimetro << " " <<fig2.area << endl;
    cout << fig3.nome << " " << fig3.perimetro << " " <<fig3.area << endl;
    cout << fig4.nome << " " << fig4.perimetro << " " <<fig4.area << endl;
    cout << fig5.nome << " " << fig5.perimetro << " " <<fig5.area << endl;
    return 0;
}
