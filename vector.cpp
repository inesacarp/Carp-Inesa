#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class Exceptie:public exception {

};
class Vector {
	static int numarator;
	const int id;
protected:
	int capacitate;
	int dimensiune;
	float* elemente;
public:
	Vector() :id(0) {
		this->capacitate = 0;
		this->dimensiune = 0;
		this->elemente = NULL;
	}
	Vector(int capacitate, int dimensiune, float* elemente) :id(numarator++) {
		this->capacitate = capacitate;
		this->dimensiune = dimensiune;
		this->elemente = new float[this->dimensiune];
		for (int i = 0; i < this->dimensiune; i++) {
			this->elemente[i] = elemente[i];
		}
	}
	Vector(const Vector& v) :id(v.id) {
		this->capacitate = v.capacitate;
		this->dimensiune = v.dimensiune;
		this->elemente = new float[this->dimensiune];
		for (int i = 0; i < this->dimensiune; i++) {
			this->elemente[i] = v.elemente[i];
		}
	}

	Vector & operator=(const Vector& v) {
		if (this != &v) {
			if (this->elemente != NULL) {
				delete[]this->elemente;
			}
			this->capacitate = v.capacitate;
			this->dimensiune = v.dimensiune;
			this->elemente = new float[this->dimensiune];
			for (int i = 0; i < this->dimensiune; i++) {
				this->elemente[i] = v.elemente[i];
			}
		}
		return *this;
	}
	float operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->dimensiune) {
			return this->elemente[pozitie];
		}
		else throw exception();
	}


	friend ostream& operator<<(ostream& out, const  Vector &v) {
		out << v.id << endl;
		out << v.capacitate << endl;
		out << v.dimensiune << endl;
		for (int i = 0; i < v.dimensiune; i++) {
			out << v.elemente[i] << "  ";
		}
		return out;
	}
	~Vector() {
		if (this->elemente != NULL) {
			delete[]this->elemente;
		}
}
	explicit operator int() {
		return this->dimensiune;
	}
};
int Vector::numarator = 1;

class Matrice {
	int nrVectori;
	Vector* vector;
public:
	Matrice() {
		this->nrVectori = 0;
		this->vector = NULL;
	}
	Matrice(int nrVectori, Vector* vector) {
		this->nrVectori = nrVectori;
		this->vector = new Vector[this->nrVectori];
		for (int i = 0; i < this->nrVectori; i++) {
			this->vector[i] = vector[i];
		}
	}
	Matrice(const Matrice &m) {
		this->nrVectori = m.nrVectori;
		this->vector = new Vector[this->nrVectori];
		for (int i = 0; i < this->nrVectori; i++) {
			this->vector[i] = m.vector[i];
		}
	}
	Matrice& operator=(const Matrice &m) {
		if (this != &m) {
			if (this->vector != NULL) {
				delete[]this->vector;
			}
			this->nrVectori = m.nrVectori;
			this->vector = new Vector[this->nrVectori];
			for (int i = 0; i < this->nrVectori; i++) {
				this->vector[i] = m.vector[i];
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream&out, const Matrice& m) {
		out << m.nrVectori << endl;
		for (int i = 0; i < m.nrVectori; i++) {
			out << m.vector[i] << "e un vector" << endl;
		}
		return out;
	}
	~Matrice() {
		if (this->vector != NULL) {
			delete[]this->vector;
		}
	}
};

int main() {
	Vector v;
	Vector v1(12, 3, new float[3]{ 12,13,14 });
	Vector v2(45, 5, new float[5]{ 11,22,33,44,55 });
	Vector v3(99, 1, new float[1]{ 100});
	//Vector v4 = v2;
	//v1 = v3;
	cout << v1 << endl << endl <<v2 << endl << endl << v3 << endl << "  " << endl;
	/*cout << (int)v3 << endl;
	try {
		cout << v2[9] << endl;
	}
	catch (...) {
		cout << "pozitie introdusa gresit";
	}*/


	Matrice m1(2, new Vector[2]{ v3,v2 });
	//cout << m1;




	return 0;
}
