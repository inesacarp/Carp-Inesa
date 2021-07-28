#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
class Joc
{
	const int id;
	string titluJoc;
	string consolaCompatibila;
	int varstaMinima;
	bool stareaJocului;//0-disponibil,1- inchiriat
	int nrExemplare;
	float* pretPerConsola;
public:
	Joc() :id(0)
	{
		this->titluJoc = " ";
		this->consolaCompatibila = " ";
		this->varstaMinima = 0;
		this->stareaJocului = 0;
		this->nrExemplare = 0;
		this->pretPerConsola = NULL;
	}
	Joc(int id, string titluJoc, string consolaCompatibila, int varstaMinima, bool stareaJocului, int nrExemplare, float* pretPerConsola) :id(id)
	{
		this->titluJoc = titluJoc;
		this->consolaCompatibila = consolaCompatibila;
		this->varstaMinima = varstaMinima;
		this->stareaJocului = stareaJocului;
		this->nrExemplare = nrExemplare;
		this->pretPerConsola = new float[this->nrExemplare];
		for (int i = 0; i < this->nrExemplare; i++)
		{
			this->pretPerConsola[i] = pretPerConsola[i];
		}
	}
	Joc(const Joc& j) :id(j.id)
	{
		this->titluJoc = j.titluJoc;
		this->consolaCompatibila = j.consolaCompatibila;
		this->varstaMinima = j.varstaMinima;
		this->stareaJocului = j.stareaJocului;
		this->nrExemplare = j.nrExemplare;
		this->pretPerConsola = new float[this->nrExemplare];
		for (int i = 0; i < this->nrExemplare; i++)
		{
			this->pretPerConsola[i] = j.pretPerConsola[i];
		}
	}
	~Joc()
	{
		if (this->pretPerConsola != NULL)
		{
			delete[]this->pretPerConsola;
		}
	}
	Joc& operator=(const Joc& j)
	{
		if (this != &j)
		{
			if (this->pretPerConsola != NULL)
			{
				delete[]this->pretPerConsola;
			}
			this->titluJoc = j.titluJoc;
			this->consolaCompatibila = j.consolaCompatibila;
			this->varstaMinima = j.varstaMinima;
			this->stareaJocului = j.stareaJocului;
			this->nrExemplare = j.nrExemplare;
			this->pretPerConsola = new float[this->nrExemplare];
			for (int i = 0; i < this->nrExemplare; i++)
			{
				this->pretPerConsola[i] = j.pretPerConsola[i];
			}
		}
		return*this;
	}

	friend ostream& operator<<(ostream& out, const Joc& j)
	{
		out << "Id: " << j.id << endl;
		out << "Nume: " << j.titluJoc << endl;
		out << "Consola disponibila: " << j.consolaCompatibila << endl;
		out << "Varsta minima: " << j.varstaMinima<< " ani" << endl;
		out << "Starea Jocului: (0-disponibil,1 inchiriat) " << j.stareaJocului << endl;
		out << "Numar exemplare: " << j.nrExemplare<< endl;
		out << "Pret exemplar: ";
		for (int i = 0; i < j.nrExemplare; i++)
		{
			out << j.pretPerConsola[i] << " | ";
		}
		return out;
	}

	string getTitlu()
	{
		return this->titluJoc;
	}
	int getVarsta()
	{
		return this->varstaMinima;
	}
	void setTitlu(string titluJoc)
	{
		this->titluJoc = titluJoc;
	}

	bool getStare()
	{
		return this->stareaJocului;	
	}
	void setStare(bool stareaJocului)
	{
		this->stareaJocului = stareaJocului;
	}

	float* getPreturi()
	{
		return this->pretPerConsola;
	}
	float totalPreturi()
	{
		float suma = 0;
		for (int i = 0; i < this->nrExemplare; i++)
		{
			suma += pretPerConsola[i];
		}
		return suma;
	}
};

class Magazin
{
	string nume;
	int nrJocuri;
	Joc* jocuri;
public:
	Magazin()
	{
		this->nume = "Necunoscut";
		this->nrJocuri = 0;
		this->jocuri = NULL;
	}
	Magazin(string nume, int nrJocuri, Joc* jocuri)
	{
		this->nume = nume;
		this->nrJocuri = nrJocuri;
		this->jocuri = new Joc[this->nrJocuri];
		for (int i = 0; i < this->nrJocuri; i++)
		{
			this->jocuri[i] = jocuri[i];
		}
	}
	Magazin(const Magazin& m)
	{
		this->nume = m.nume;
		this->nrJocuri = m.nrJocuri;
		this->jocuri = new Joc[this->nrJocuri];
		for (int i = 0; i < this->nrJocuri; i++)
		{
			this->jocuri[i] = m.jocuri[i];
		}
	}
	~Magazin()
	{
		if (this->jocuri != NULL)
		{
			delete[]this->jocuri;
		}
	}
	Magazin& operator=(const Magazin& m)
	{
		if (this != &m)
		{
			if (this->jocuri != NULL)
			{
				delete[]this->jocuri;
			}
			this->nume = m.nume;
			this->nrJocuri = m.nrJocuri;
			this->jocuri = new Joc[this->nrJocuri];
			for (int i = 0; i < this->nrJocuri; i++)
			{
				this->jocuri[i] = m.jocuri[i];
			}
			
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Magazin& m)
	{
		out << "Nume: " << m.nume << endl;
		out << "Numar Jocuri: " << m.nrJocuri << endl;
		out << "Jocuri: " << endl;
		for (int i = 0; i < m.nrJocuri; i++)
		{
			out << m.jocuri[i] << endl<<endl;
		}
		return out;
	}

	int operator()()
	{
		int nr = 0;
		for (int i = 0; i < this->nrJocuri; i++)
		{
			if (this->jocuri[i].getVarsta() >= 16)
			{
				nr++;
			}
		}
		return nr;
	}

	Magazin& operator+=(Joc j)
	{
		for (int i = 0; i < this->nrJocuri; i++)
		{
			if (this->jocuri[i].getTitlu() == j.getTitlu() && this->jocuri[i].getStare()==1)
			{
				this->jocuri[i].setStare(0);
			}
		}
		return *this;
	}
	Magazin& operator-=(Joc j)
	{
		for (int i = 0; i < this->nrJocuri; i++)
		{
			if (this->jocuri[i].getTitlu() == j.getTitlu() && this->jocuri[i].getStare() == 0)
			{
				this->jocuri[i].setStare(1);
			}
		}
		return *this;
	}

	Joc operator[](int pozitie)
	{
		if (pozitie >= 0 && pozitie < this->nrJocuri)
		{
			return this->jocuri[pozitie];
		}
	}

	float venitInchirieri()
	{
		float valoare = 0;
		for (int i = 0; i < this->nrJocuri; i++)
		{
			if (this->jocuri[i].getStare() == 1)
			{
				valoare += this->jocuri[i].totalPreturi();
			}
		}
		return valoare;
	}
};

void main()
{
	Joc j;
	cout << j.getTitlu() << endl;
	j.setTitlu("NBA");
	cout << j.getTitlu() << endl;

	float preturiConsole[] = { 33.4,11.3,22.5 };
	Joc j1(33, "Fifa", "PC/XBOX/PS4", 12, 0, 3, preturiConsole);
	Joc joc1(12, "Minecraft", "PC/XBOX", 10, 0, 2, preturiConsole);
	Joc joc2(44, "Mortal KOMBAT", "PC/XBOX/PS4", 17, 1, 3, preturiConsole);
	Joc joc3(23, "CS:GO", "PC", 16, 0, 1, preturiConsole);
	cout << j1 << endl << endl;

	Joc j2 = j1;
	cout << j2 << endl<<endl;

	j = j1;
	cout << j << endl << endl;

	cout << "-------------------------------" << endl;
	Joc* vectJocuri = new Joc[4];
	vectJocuri[0] = j1;
	vectJocuri[1] = joc1;
	vectJocuri[2] = joc2;
	vectJocuri[3] = joc3;
	Magazin m("Altex", 4, vectJocuri);
	cout << m << endl;
	cout << "Numarul de jocuri care au varsta mai mare sau egala cu 16 ani este: " << m() << endl;

	m -= j1;
	m += joc2;
	m -= joc3;
	cout << endl << m << endl << endl;
	cout << m[2] << endl;

	cout << "Valorile venite din inchirieri: " << m.venitInchirieri() << endl;
	cout << "-------------------------------" << endl;
	
}