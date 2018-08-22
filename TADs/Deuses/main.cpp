#include <iostream>

using namespace std;

class Deus {
	private:
		string mNome;
		int mForca;
		int mSabedoria;
		int mSaude;
		int mExperiencia;
	public:
		Deus(string nome, int forca, int sabedoria, int saude, int experiencia) {
			mNome = nome;
			mForca = forca;
			mSabedoria = sabedoria;
			mSaude = saude;
			mExperiencia = experiencia;
		}
		~Deus() {
			mNome = "";
			mForca = 0;
			mSabedoria = 0;
			mSaude = 0;
			mExperiencia = 0;
		}
		string Nome() {
			return mNome;
		}
		int Forca() {
			return mForca;
		}
		int Sabedoria() {
			return mSabedoria;
		}
		int Saude() {
			return mSaude;
		}
		int Experiencia() {
			return mExperiencia;
		}
		void Imprime() {
			cout << "Nome:" << Nome() << endl;
			cout << "Força: " << Forca() << endl;
			cout << "Sabedoria: " << Sabedoria() << endl;
			cout << "Saúde: " << Saude() << endl;
			cout << "Experiência: " << Experiencia() << endl;
		}
};

int main () {
	Deus *Thor = new Deus("Thor", 5, 2, 6, 1);

	Thor->Imprime();
	
	delete Thor;

	return 0;
}