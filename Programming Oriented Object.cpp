#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;
//Am supraincarcat in clasa Cladire operatorul<< si operatorul>>
class Cladire
{
private:
	string denumire;
	int nrEtaje;
	double suprafata;
	string tip;
	string zona;
public:
	Cladire(string denumire, int nrEtaje, double suprafata, string tip, string zona)
	{
		this->denumire = denumire;
		this->nrEtaje = nrEtaje;
		this->suprafata = suprafata;
		this->tip = tip;
		this->zona = zona;
	}

	Cladire()
	{
		this->denumire = "RANDOM";
		this->nrEtaje = 0;
		this->suprafata = 0;
		this->tip = "RANDOM";
		this->zona = "RANDOM";
	}

	Cladire(string denumire, int nrEtaje, double suprafata, string tip)
	{
		this->denumire = denumire;
		this->nrEtaje = nrEtaje;
		this->suprafata = suprafata;
		this->tip = tip;
		this->zona = "RANDOM";
	}

	Cladire(const Cladire& c)
	{
		this->denumire = c.denumire;
		this->nrEtaje = c.nrEtaje;
		this->suprafata = c.suprafata;
		this->zona = c.zona;
		this->tip = c.tip;
	}

	Cladire& operator=(const Cladire& c)
	{
		this->nrEtaje = c.nrEtaje;
		this->suprafata = c.suprafata;
		this->denumire = c.denumire;
		this->tip = c.tip;
		this->zona = c.zona;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Cladire c) {
		out << "Denumirea este " << c.denumire << endl;
		out << "are " << c.nrEtaje << "camere" << endl;
		out << "suprafata este:" << c.suprafata << endl;
		out << "este de tipul: " << c.tip << endl;
		out << "este in zona: " << c.zona << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Cladire& c) {
		in >> c.denumire;
		in >> c.nrEtaje;
		in >> c.suprafata;
		in >> c.zona;
		return in;
	}
	Cladire& operator/=(const Cladire& c)
	{
		this->nrEtaje /= c.nrEtaje;

		return *this;
	}

	Cladire& operator-=(const Cladire& c)
	{
		this->suprafata -= c.suprafata;
	}

	Cladire& operator+=(const Cladire& c)
	{
		this->suprafata += c.suprafata;
		return *this;
	}

	bool operator==(Cladire c)
	{
		return this->suprafata == c.suprafata;
	}

	bool operator>(const Cladire c)
	{
		if (this->suprafata > c.suprafata)
			return true;
		else return false;
	}

	bool operator<(const Cladire c)
	{
		if (this->suprafata < c.suprafata)
			return true;
		else return false;
	}

	~Cladire()
	{

	}

	double getSuprafata()
	{
		return suprafata;
	}
	void setSuprafata(double suprafata)
	{
		if (suprafata < 0)
			throw 101;
		else this->suprafata = suprafata;
	}

	string getDenumire()
	{
		return denumire;
	}

	void setDenumire(string denumire)
	{
		if (denumire.length() > 1) {
			this->denumire = denumire;
		}
	}

	int getnrEtaje()
	{
		return nrEtaje;
	}

	void setnrEtaje(int nrEtaje)
	{
		if (nrEtaje > 0) {
			this->nrEtaje = nrEtaje;
		}
	}

	string getTip()
	{
		return tip;
	}

	void setTip(string tip)
	{
		if (tip.length() > 0) {
			this->tip = tip;
		}
	}

	string getZona()
	{
		return zona;
	}

	void setZona(string zona)
	{
		if (zona.length() > 0) {
			this->zona = zona;
		}
	}
};

class InstitutiePublica : public Cladire
{
	const  string limba; //limba in care se intocmesc de regula actele
	static int nrZile; // numarul de zile lucratoare pe an, recunosc ca nu prea are sens dar nu am mai avut inspiratie pentru altceva
	char* denumireI = new char[50];
	int nrAngajati;
	float* varste;
	int nrsc; // numar sali de conferinta
	string director;
public:
	InstitutiePublica() :Cladire(), limba("romana") {
		this->denumireI = new char[strlen("primarie") + 1];
		strcpy(this->denumireI, "primarie");
		this->nrAngajati = 3;
		this->varste = new float[3]{ 25,27,26 };
		this->nrsc = 4;
		this->director = "Gavrila";
	}
	InstitutiePublica(string denumire, int nrEtaje, double suprafata, string tip, string zona, const char* denumireI, string limba, int nrAngajati,
		float* varste, int nrsc, string director)
		:Cladire(denumire, nrEtaje, suprafata, tip), limba(limba) {
		if (denumireI) {
			this->denumireI = new char[strlen(denumireI) + 1];
			strcpy(this->denumireI, denumireI);
		}
		else denumireI = nullptr;
		this->nrAngajati = nrAngajati;
		this->varste = new float[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->varste[i] = varste[i];
		}
		this->nrsc = nrsc;
		this->director = director;
	}
	string getLimba() {
		return this->limba;
	}
	void setDenI(const char* denumireI) {
		if (denumireI != NULL) {
			if (strlen(denumireI) > 3) {
				if (this->denumireI != NULL) {
					delete[] this->denumireI;
				}

				this->denumireI = new char[strlen(denumireI) + 1];
				strcpy(this->denumireI, denumireI);
			}
		}

	}
	const char* getDenumireI() {
		return this->denumireI;
	}
	void setNrAng(int nrAngajati) {
		this->nrAngajati = nrAngajati;
	}
	int getNrAngajati() {
		return nrAngajati;
	}
	void setVarste(int nrAngajati, float* varste) {
		if (nrAngajati > 0 && varste != NULL) {
			if (this->varste != NULL) {
				delete[]this->varste;
			}
			this->varste = new float[nrAngajati];
			for (int i = 0; i < nrAngajati; i++) {
				this->varste[i] = varste[i];
			}
			this->nrAngajati = nrAngajati;
		}
	}
	const float* getvarste() {
		return this->varste;
	}
	void setNrsali(int nrsc) {
		this->nrsc = nrsc;
	}
	int getNrsali() {
		return this->nrsc;
	}
	void setDirector(string director)
	{
		if (director.length() > 1) {
			this->director = director
				;
		}
	}
	string getDirector() {
		return this->director;
	}
	InstitutiePublica(const InstitutiePublica& p1) :Cladire(p1), limba(p1.limba) {
		if (p1.denumireI) {
			this->denumireI = new char[strlen(p1.denumireI) + 1];
			strcpy(this->denumireI, p1.denumireI);
		}
		else denumireI = nullptr;
		this->nrAngajati = p1.nrAngajati;

		if (p1.varste) {
			this->varste = new float[this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++) {
				this->varste[i] = p1.varste[i];
			}
		}
		else throw "Parametri incorecti";
		this->nrsc = p1.nrsc;
		this->director = p1.director;
	}
	InstitutiePublica operator=(const InstitutiePublica& p1) {
		if (p1.denumireI) {
			this->denumireI = new char[strlen(p1.denumireI) + 1];
			strcpy(this->denumireI, p1.denumireI);
		}
		else denumireI = nullptr;
		this->nrAngajati = p1.nrAngajati;

		if (p1.varste) {
			this->varste = new float[this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++) {
				this->varste[i] = p1.varste[i];
			}
		}
		else throw "Parametri incorecti";
		this->nrsc = p1.nrsc;
		this->director = p1.director;
		Cladire::operator=(p1);
		return *this;
	}
	friend ostream& operator<<(ostream& out1, InstitutiePublica p1) {
		out1 << (Cladire)p1;
		out1 << "Denumirea institutiei este: " << p1.denumireI << endl;
		out1 << "Limba este: " << p1.limba << endl;
		out1 << "Numarul de zile lucratoare este: " << p1.nrZile << endl;
		out1 << "Numarul de angajati este: " << p1.nrAngajati << endl;
		for (int i = 0; i < p1.nrAngajati; i++) {
			out1 << "varsta este:" << p1.varste[i] << endl;
		}
		out1 << "Numarul salilor de conferinta este: " << p1.nrsc << endl;
		out1 << "Numele directorului: " << p1.director;
		return out1;
	}
	friend istream& operator>>(istream& in1, InstitutiePublica& p1) { //n am facut pt char*
		in1 >> p1.nrAngajati;
		if (p1.varste)
			delete[] p1.varste;
		p1.varste = new float[p1.nrAngajati];
		for (int i = 0; i < p1.nrAngajati; i++)
			in1 >> p1.varste[i];
		if (p1.denumireI)
			delete[] p1.denumireI;
		scanf(p1.denumireI);
		in1 >> p1.denumireI;
		in1 >> p1.nrsc;
		in1 >> p1.director;

		return in1;
	}
	float& operator[](int index) {
		if (index >= 0 && index < nrAngajati) {
			return varste[index];
		}
		else {
			throw "Index in afara limitelor";
		}
	}
	int varstaMedie()
	{
		float s = 0;
		if (nrAngajati == 0)
			return -1;
		for (int i = 0; i < nrAngajati; i++)
			s += varste[i];
		return s / nrAngajati;
	}
	float maxVarsta()
	{
		float max;
		max = varste[0];
		for (int i = 1; i < nrAngajati; i++)
			if (varste[i] > max)
				max = varste[i];
		return max;
	}

	~InstitutiePublica() {
		if (this->varste) {
			delete[]this->varste;
		}
		if (this->denumireI) {
			delete[]this->denumireI;
		}
	}
};
int InstitutiePublica::nrZile = 251;

class Corporatie :public Cladire //doar de tip S.A.
{
	string fondator;
	int nrSedii;
	string* sedii;
	int anInfiintare;
	float cifraAfaceri;
	const int impozit; // in %, presupunem ca toate corporatiile platesc acelasi  % de impozit 
	static string formaJuridica;
public:
	Corporatie() :Cladire(), impozit(12) {
		this->fondator = "John W";
		this->nrSedii = 4;
		this->sedii = new string[4]{ "S1","S2","S3","S4" };
		this->anInfiintare = 1998;
		this->cifraAfaceri = 1987964;
	}
	Corporatie(string denumire, int nrEtaje, double suprafata, string tip, string fondator, int nrSedii, string* sedii,
		int anInfiintare, float cifraAfaceri) :Cladire(denumire, nrEtaje, suprafata, tip), impozit(19) {
		this->fondator = fondator;
		this->nrSedii = nrSedii;
		this->sedii = new string[nrSedii];
		for (int i = 0; i < nrSedii; i++) {
			this->sedii[i] = sedii[i];
		}
		this->anInfiintare = anInfiintare;
		this->cifraAfaceri = cifraAfaceri;
	}
	Corporatie(const Corporatie& co) :impozit(co.impozit), Cladire(co) {
		this->fondator = co.fondator;
		this->nrSedii = co.nrSedii;
		this->sedii = new string[nrSedii];
		for (int i = 0; i < nrSedii; i++) {
			this->sedii[i] = co.sedii[i];
		}
		this->anInfiintare = co.anInfiintare;
		this->cifraAfaceri = co.cifraAfaceri;
	}
	Corporatie operator=(const Corporatie& co) {
		this->fondator = co.fondator;
		this->nrSedii = co.nrSedii;
		if (this->nrSedii != co.nrSedii) {
			if (this->sedii != NULL) {
				delete[]this->sedii;
			}
			this->sedii = new string[nrSedii];
			for (int i = 0; i < nrSedii; i++) {
				this->sedii[i] = co.sedii[i];
			}
		}
		this->anInfiintare = co.anInfiintare;
		this->cifraAfaceri = co.cifraAfaceri;
		Cladire::operator=(co);
		return *this;
	}
	friend istream& operator>>(istream& in2, Corporatie& co) {
		in2 >> (Cladire&)co;
		in2 >> co.fondator;
		in2 >> co.nrSedii;
		if (co.nrSedii) {
			delete[] co.sedii;
		}
		co.sedii = new string[co.nrSedii];
		for (int i = 0; i < co.nrSedii; i++) {
			in2 >> co.sedii[i];
		}
		in2 >> co.anInfiintare;
		in2 >> co.cifraAfaceri;
		return in2;
	}

	friend ostream& operator<<(ostream& out2, Corporatie& co) {
		out2 << (Cladire)co;
		out2 << co.formaJuridica << endl;
		out2 << "Fondatorul companiei este: " << co.fondator << endl;
		out2 << "Numarul de sedii este de: " << co.nrSedii << endl;
		for (int i = 0; i < co.nrSedii; i++) {
			out2 << "Acestea sunt: " << co.sedii[i] << endl;
		}
		out2 << "Anul infiintarii este: " << co.anInfiintare << endl;
		out2 << "Cifra de afaceri: " << co.cifraAfaceri << endl;
		out2 << "Impozitul este: " << co.impozit << endl;

		return out2;
	}
	void setFondator(string fondator) {
		if (fondator.length() > 1) {
			this->fondator = fondator;
		}
	}
	string getFondator() {
		return this->fondator;
	}
	void setNrSedii(int nrSedii) {
		this->nrSedii = nrSedii;
	}
	int getNrSedii() {
		return this->nrSedii;
	}
	void setSedii(int nrSedii, string* sedii) {
		if (nrSedii > 0 && sedii != NULL) {
			if (this->sedii != NULL) {
				delete[]this->sedii;
			}
			this->sedii = new string[nrSedii];
			for (int i = 0; i < nrSedii; i++) {
				this->sedii[i] = sedii[i];
			}
			this->nrSedii = nrSedii;
		}
	}
	const string* getSedii() {
		return this->sedii;
	}
	void setAnInfiintare(int anInfiintare) {
		this->anInfiintare = anInfiintare;

	}
	int getAnInfiintare() {
		return this->anInfiintare;
	}
	void setcifraAf(float cifraAfaceri) {
		this->cifraAfaceri = cifraAfaceri;
	}
	float getCifraAfaceri() {
		return this->cifraAfaceri = cifraAfaceri;
	}
	int getImpozit() {
		return this->impozit;

	}
	string& operator[](int ind) {
		if (ind >= 0 && ind < nrSedii) {
			return sedii[ind];
		}
		else {
			throw "Indexul depaseste limitele";
		}
	}
};
string Corporatie::formaJuridica = "SOCIETATE PE ACTIUNI";


int  main() {

	InstitutiePublica p1;
	Cladire c("Clad", 2, 20, "casa", "tineretului");
	InstitutiePublica p2("Cladire", 2, 20, "dup", "tineretului", "JJJJ", "romana", 2, new float[2]{ 25,35 }, 17, "I");
	Corporatie e("Building Emp", 2, 68, "Birouri", "J.K.", 3, new string[3]{ "S1","S2","S3" }, 1999, 258473);
	//cout << p2;
	//cout << endl << endl;
	p1 = p2;
	cout << p1;
	return 0;
}

