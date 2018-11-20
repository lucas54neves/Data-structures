#include <iostream>

using namespace std;

class Pais {
private:
	char mNome[30];
	char mCapital[30];
	int mPopulacao;
	float mPIB;
	char mContinente[20];
public:
	Pais() {
		cout << "Entre com o nome do pais" << endl;
		cin.getline(mNome, 30);
		cout << "Entre com o nome da capital" << endl;
		cin.getline(mCapital, 30);
		cout << "Entre com a quantidade de população" << endl;
		cin >> mPopulacao;
		cin.ignore();
		cout << "Entre com o valor do PIB" << endl;
		cin >> mPIB;
		cin.ignore();
		cout << "Entre com o continente" << endl;
		cin.getline(mContinente, 20);
	}
	~Pais() {
		mNome[30] = ' ';
		mCapital[30] = ' ';
		mPopulacao = 0;
		mPIB = 0;
		mContinente[20] = ' ';
	}
	void Imprime() {
		cout << "Nome: " << mNome << endl;
		cout << "Capital: " << mCapital << endl;
		cout << "População: " << mPopulacao << endl;
		cout << "PIB: " << mPIB << endl;
		cout << "Continente: " << mContinente << endl;
	}
};

int main() {
	Pais *Brasil = new Pais;

	Brasil->Imprime();

	delete Brasil;
	return 0;
}