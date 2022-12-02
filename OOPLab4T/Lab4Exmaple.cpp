#include <iostream>
#include "Lab4Exmaple.h"

using namespace std;
enum STATE {
	OK, BAD_INIT, BAD_DIV
};
void MenuTask()
{
	cout << "     Menu Task   \n";
	cout << "    1.  Class VectorFloat  \n";
	cout << "    2.  Class Vector \n";
	cout << "    3.  Class Vector and Matrix \n";
	cout << "    4.  Exit \n";
}
//------------------------------------------------------1-------------------------------------------------------------------
class VectorFloat
{
	float* v;
	int num = 2;
	int state = 0;
	static float badIndexRef;
	static int numVec;

public:
	VectorFloat():VectorFloat(1){}
	VectorFloat(int n);
	VectorFloat(int n, float);
	VectorFloat(const VectorFloat& s);  // crot copy
	VectorFloat& operator=(const VectorFloat& s);
	VectorFloat& operator=(VectorFloat&& s) noexcept;
	void Init(int n);   //
	void Init(int n, float);   //
	~VectorFloat() {
		//	std::cout << " del vec";
		if (v) delete[] v;
	}
	friend istream& operator>>(istream& is, VectorFloat& s);
	friend ostream& operator<<(ostream& os, VectorFloat& s);


	float& operator[](int index);
	VectorFloat& operator++();
	VectorFloat& operator--();

	VectorFloat& operator+=(const VectorFloat& s);
	VectorFloat& operator+=(const int& b);
	VectorFloat& operator+=(const float& b);
	VectorFloat  operator+(const VectorFloat& b);
	VectorFloat  operator+(const int& b);
	VectorFloat  operator+(const float& b);

	VectorFloat& operator-=(const VectorFloat& s);
	VectorFloat& operator-=(const int& b);
	VectorFloat& operator-=(const float& b);
	VectorFloat  operator-(const VectorFloat& b);
	VectorFloat  operator-(const int& b);
	VectorFloat  operator-(const float& b);

	VectorFloat& operator*=(const VectorFloat& b);
	VectorFloat& operator*=(const int& b);
	VectorFloat& operator*=(const float& b);

	VectorFloat operator*(const VectorFloat& b);
	VectorFloat operator*(const int& b);
	VectorFloat operator*(const float& b);
	
	VectorFloat& operator/=(const VectorFloat& b);
	VectorFloat& operator/=(const int& b);
	VectorFloat& operator/=(const float& b);

	VectorFloat operator/(const int& b);
	VectorFloat operator/(const float& b);

	bool operator>(const VectorFloat& s);
	bool operator>=(const VectorFloat& s);
    bool operator<(const VectorFloat& s);
    bool operator<=(const VectorFloat& s);

};

float VectorFloat::badIndexRef = 0;
VectorFloat::VectorFloat(int n) {
	if (n <= 0)    n = 1;  // default num =2;
	num = n;
	v = new float[n];
	for (int i = 0; i < n; i++) {
		v[i] = 0.0;
	}
}
VectorFloat::VectorFloat(int n, float b) : VectorFloat(n) {
	for (int i = 0; i < num; i++) {
		v[i] = b;
	}
}
VectorFloat::VectorFloat(const VectorFloat& s) {
	num = s.num;
	v = new float[num];
	state = 1;
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
}
VectorFloat& VectorFloat::operator=(const VectorFloat& s) {
	if (this == &s) return *this;
	if (num != s.num)
	{
		if (v) delete[] v;
		num = s.num;
		v = new float[num];
		state = 1;
	}
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
	return *this;
}
VectorFloat& VectorFloat::operator=(VectorFloat&& s) noexcept
{
	if (this == &s) return *this;
	num = s.num; state = s.state;
	if (this->v != nullptr) delete[] v;
	v = s.v;
	s.num = 0; s.v = nullptr; s.state = -1;
	return *this;
}
void VectorFloat::Init(int n) {
	if (num != n) {
		if (v != nullptr) delete[] v;
		num = n;
		v = new float[n];
	}
	for (int i = 0; i < num; i++) 	v[i] = 0;
}
void VectorFloat::Init(int n, float b) {
	if (num != n) {
		if (v != nullptr) delete[] v;
		num = n;
		v = new float[n];
	}
	for (int i = 0; i < num; i++) 	v[i] = b;
}

istream& operator>>(istream& is, VectorFloat& s) {
	for (int i = 0; i < s.num; i++)
	{
		is >> s.v[i];
	}
	return is;
};
ostream& operator<<(ostream& os, VectorFloat& s) {
	for (int i = 0; i < s.num; i++)
		os << s.v[i] << '\t';
	os << endl;
	return os;
}
float& VectorFloat::operator[](int index)
{
	if (index >= 0 && index < num) return v[index];
	cout << " Error : operator[] - index out of range \n";
	return badIndexRef;
}

VectorFloat& VectorFloat::operator-=(const VectorFloat& b)
{
	int i;
	if (num == b.num) for (i = 0; i < num; i++) v[i] -= b.v[i];
	else {
		cout << " Warning: vectors of different sizes are used in operation -= \n";
		if (num < b.num) {
			float* tmp;
			tmp = new float[b.num];
			for (i = 0; i < num; i++) tmp[i] = v[i] - b.v[i];
			for (; i < b.num; i++) tmp[i] = -b.v[i];
			num = b.num;
			if (v != nullptr) delete[] v;
			v = tmp;
		}
		else 	for (i = 0; i < b.num; i++) v[i] -= b.v[i];
	}
	return *this;
}
VectorFloat& VectorFloat::operator-=(const int& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) v[i] -= b;
	}
	return *this;
}
VectorFloat& VectorFloat::operator-=(const float& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) v[i] -= b;
	}
	return *this;
}

VectorFloat& VectorFloat::operator--()
{
	for (int i = 0; i < num; i++) v[i] -= 1;
	return *this;
}
VectorFloat VectorFloat::operator-(const VectorFloat& b)
{
	VectorFloat tmp(*this);
	tmp -= b;
	return tmp;
}
VectorFloat VectorFloat::operator-(const int& b)
{
	VectorFloat tmp(*this);
	tmp -= b;
	return tmp;
}
VectorFloat VectorFloat::operator-(const float& b)
{
	VectorFloat tmp(*this);
	tmp -= b;
	return tmp;
}
VectorFloat& VectorFloat::operator++()
{
	for (int i = 0; i < num; i++) v[i] += 1;
	return *this;
}
VectorFloat& VectorFloat::operator+=(const VectorFloat& b)
{
	int i;
	if (num == b.num) for (i = 0; i < num; i++) v[i] += b.v[i];
	else
	{
		cout << " Warning: vectors of different sizes are used in operation += \n";
		if (num < b.num) {
			float* tmp;
			tmp = new float[b.num];
			for (i = 0; i < num; i++) tmp[i] = v[i] + b.v[i];
			for (; i < b.num; i++) tmp[i] = b.v[i];
			num = b.num;
			if (v != nullptr) delete[] v;
			v = tmp;
		}
		else for (i = 0; i < b.num; i++) v[i] += b.v[i];
	}
	return *this;
}
VectorFloat& VectorFloat::operator+=(const int& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) v[i] += b;
	}
	return *this;
}
VectorFloat& VectorFloat::operator+=(const float& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) v[i] += b;
	}
	return *this;
}
VectorFloat VectorFloat::operator+(const VectorFloat& b)
{
	VectorFloat tmp(*this);
	tmp += b;
	return tmp;
}
VectorFloat VectorFloat::operator+(const int& b)
{
	VectorFloat tmp(*this);
	tmp += b;
	return tmp;
}
VectorFloat VectorFloat::operator+(const float& b)
{
	VectorFloat tmp(*this);
	tmp += b;
	return tmp;
}
VectorFloat& VectorFloat::operator*=(const  VectorFloat& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) v[i] *= b.v[i];
	return *this;
}

VectorFloat& VectorFloat::operator*=(const int& b) {
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	for (int i = 0; i < num; i++) v[i] *= b;
	return *this;
	return tmp;
}
VectorFloat& VectorFloat::operator*=(const float& b) {
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	for (int i = 0; i < num; i++) v[i] *= b;
	return *this;
	return tmp;
}

VectorFloat VectorFloat::operator*(const  VectorFloat& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) v[i] *= b.v[i];
	return *this;
}
VectorFloat VectorFloat::operator*(const int& b) {
	VectorFloat rez(*this);
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez *= b;
	return rez;
	return tmp;
}
VectorFloat VectorFloat::operator*(const float& b) {
	VectorFloat rez(*this);
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez *= b;
	return rez;
	return tmp;
}
VectorFloat& VectorFloat::operator/=(const  VectorFloat& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) v[i] /= b.v[i];
	return *this;
}
VectorFloat& VectorFloat::operator/=(const int& b) {
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	else for (int i = 0; i < num; i++) v[i] /= b;
	return *this;
	return tmp;
}
VectorFloat& VectorFloat::operator/=(const float& b) {
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	else for (int i = 0; i < num; i++) v[i] /= b;
	return *this;
	return tmp;
}
VectorFloat VectorFloat::operator/(const int& b) {
	VectorFloat rez(*this);
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez /= b;
	return rez;
	return tmp;
}
VectorFloat VectorFloat::operator/(const float& b) {
	VectorFloat rez(*this);
	VectorFloat tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez /= b;
	return rez;
	return tmp;
}

bool VectorFloat::operator>(const VectorFloat& s) {
	for (int i = 0; i < num; i++) {
		if (v[i] > s.v[i])
			return true;
	}
	return false;
}
bool VectorFloat::operator>=(const VectorFloat& s) {
	for (int i = 0; i < num; i++) {
		if (v[i] >= s.v[i])
			return true;
	}
	return false;
}
bool VectorFloat::operator<(const VectorFloat& s) {
	for (int i = 0; i < num; i++) {
		if (v[i] < s.v[i])
			return true;
	}
	return false;
}
bool VectorFloat::operator<=(const VectorFloat& s) {
	for (int i = 0; i < num; i++) {
		if (v[i] <= s.v[i])
			return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------------------------
void task1() {
	VectorFloat vect1(5);
	VectorFloat vect2(4, 5);
	VectorFloat vect3(4, 12.1);
	VectorFloat vectcopy(vect2);
	float a = 2.5;
	cout << "Test class VectorFloat : " << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << vect1;
	cout << "------------------------------------------------------------------" << endl;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << vect3;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Test reload operation:" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload ++ :"<<endl;
	cout << (++vect2);
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload -- :" << endl;
	cout << (--vect2);
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect + vect :" << endl;
	vect2 += vect2;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect + int :" << endl;
	vect2 += 2;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect + float :" << endl;
	vect2 += a;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect - float :" << endl;
	vect2 -= a;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect - int :" << endl;
	vect2 -= 2;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect - vect :" << endl;
	vect2 -=vect3;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect * vect :" << endl;
	vect2 *= vect3;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect * 0 :" << endl;
	vect2 *= 0;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect / vect :" << endl;
	vect2 /= vect3;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload vect / 0 :" << endl;
	vect2 /= 0;
	cout << vect2;
	cout << "------------------------------------------------------------------" << endl;
	     if (vectcopy < vect2)  cout << "ObjectCopy less ObjectDef" << endl;
	else if (vectcopy > vect2)  cout << "ObjectCopy More ObjectDef" << endl;
	else if (vectcopy <= vect2) cout << "ObjectCopy less Exactly ObjectDef" << endl;
	else if (vectcopy >= vect2) cout << "ObjectCopy more Exactly ObjectDef" << endl;
}

void task2(){
}

void task3(){}
/*
/// <summary>
	/// Задано : A,B,C,D,F  -  Матриці комплесних чисел
	///          a,b,c  -  Вектори комплесних чисел 
	///          _a,_b,_c - комплексні числа.
	/// Обчислити вираз : F = A+B*_a-B*_c+C/_b; 
	///                   c = F*a + D*b         
	/// </summary>
	/// <returns></returns>

int mainExample2() {
	ComplexMatrix A(5),  B(5), C(5), D(5), F(5);
	ComplexVector a(5), b(5), c(5);
	ComplexDouble _a(3.2, 5), _b(1, 2), _c = RandComplexDouble();
	
		A.RandComplexMatrix();
		B.RandComplexMatrix();
		C.RandComplexMatrix();
		D.RandComplexMatrix();
		a.RandComplexVector();
		b.RandComplexVector();
		c.RandComplexVector();

		cout << endl;
		cout << "Matrix A \n" << A;
		cout << "Matrix B \n" << B;
		cout << "Matrix C \n" << C;
		cout << "Matrix D \n" << D;
		cout << endl;
		cout << "Vector a \n" << a;
		cout << "Vector b \n" << b;
		cout << "Vector c \n" << c;
	
	/// Обчислити вираз : F = A+B*_a-B*_c+C/_b; 
	///                   c = F*a + D*b     
	F = A + B * _a - B * _c + C / _b;
	cout << "Matrix F \n" << F;
	c = F * a + D * b;
	cout << "Vector c \n" << c;

	
	return 3;
}
int mainExample3() {
	cout << " End begin \n";
	uint Flight[5] = { 12,32,23,43,43 };
	MyTime MTime[5] = { {9,10}, {10,30}, {10,30}, {10,30} , {15,35} };
	MyAssoc dbase(5, Flight, MTime);
	dbase.TableFlight();
	MyTime r = { 10,30 }, ro;
	uint fli = 32;
	ro = dbase[fli];
	cout << " Test : MyTime operator[](uint&s  )  " << "Flight " << fli << " time   " <<
		ro << endl;
	cout << " Test : uint	operator[](MyTime&s)  " << " time  " << r << " light  " <<
		dbase[r] << endl;
	cout << " Flight with time :   9   to  11 \n";
	dbase(9, 11);
	cout << " End test \n";
	return 4;
}
*/
