#include <iostream>
#include "Lab4Exmaple.h"

using namespace std;
enum STATE {
	OK, BAD_INIT, BAD_DIV,BAD_MULTIPLY
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
	friend class MatrixFloat;

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

	VectorFloat& operator/(const VectorFloat& b);
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


VectorFloat& VectorFloat::operator/(const  VectorFloat& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) v[i] /= b.v[i];
	return *this;
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
	VectorFloat vect4(4, 0);
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
	cout << "Expression 1" << endl;
	cout << "vect4= (vect2 * vect3) / 3 + vect3 * 10 + vect2 / a :" << endl;
	vect4 = (vect2 * vect3) / 3 + vect3 * 10 + vect2 / a;
	cout << vect4;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Expression 2" << endl;
	cout << "vect4= vect3 * a + vect2 * 2 - (vect3 / vect2) :" << endl;
	vect4 = vect3 * a + vect2 * 2 - (vect3 / vect2) ;
	cout << vect4;
	cout << "------------------------------------------------------------------" << endl;
	     if (vectcopy < vect2)  cout << "ObjectCopy less ObjectDef" << endl;
	else if (vectcopy > vect2)  cout << "ObjectCopy More ObjectDef" << endl;
	else if (vectcopy <= vect2) cout << "ObjectCopy less Exactly ObjectDef" << endl;
	else if (vectcopy >= vect2) cout << "ObjectCopy more Exactly ObjectDef" << endl;
	cout << "End testing." << endl;
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------2-----------------------------------------------------------------

class MatrixFloat {
private:
	VectorFloat* arr=nullptr;
	int n=1;
	int m=1;
	int state=0;				//state
public:
	MatrixFloat():arr(nullptr),n(0),m(0),state(0){}
	MatrixFloat(int n) :MatrixFloat(n, n) {};
	MatrixFloat(int n, int m) :MatrixFloat(n, m, 0) {};
	MatrixFloat(int n, int m, float);
	MatrixFloat(const MatrixFloat& s);
	MatrixFloat& operator=(const MatrixFloat& s);
	MatrixFloat& operator=(MatrixFloat&& s) noexcept;
	~MatrixFloat() {
		//	std::cout << " del mat";
		if (arr) delete[] arr;
	}
	friend istream& operator>>(istream& is, MatrixFloat& s);
	friend ostream& operator<<(ostream& os, MatrixFloat& s);
	VectorFloat& operator[](int index);
	//reload oparation
	MatrixFloat& operator++();
	MatrixFloat& operator--();

	MatrixFloat& operator+=(const MatrixFloat& s);
	MatrixFloat& operator+=(const float& b);
	MatrixFloat  operator+(const MatrixFloat& b);
	MatrixFloat  operator+(const int& b);
	MatrixFloat  operator+(const float& b);

	MatrixFloat& operator-=(const MatrixFloat& s);
	MatrixFloat& operator-=(const int& b);
	MatrixFloat& operator-=(const float& b);
	MatrixFloat  operator-(const MatrixFloat& b);
	MatrixFloat  operator-(const int& b);
	MatrixFloat  operator-(const float& b);


	MatrixFloat& operator*=(const int& b);
	MatrixFloat& operator*=(const float& b);
	MatrixFloat operator*(const MatrixFloat& b);
	VectorFloat operator*(const VectorFloat& b);   //matrix*vect
	MatrixFloat operator*(const float& b);


	MatrixFloat& operator/=(const int& b);
	MatrixFloat& operator/=(const float& b);
	MatrixFloat operator/(const int& b);
	MatrixFloat operator/(const float& b);

	bool operator>(const  MatrixFloat& s);
	bool operator>=(const MatrixFloat& s);
	bool operator<(const  MatrixFloat& s);
	bool operator<=(const MatrixFloat& s);

	int getState() {
		return state;
	}
};
MatrixFloat::MatrixFloat(int ni, int mi, float b)
{
	if (ni <= 0) n = 1; else n = ni;
	if (mi <= 0) m = 1; else m = mi;
	arr = new VectorFloat[n];
	for (int i = 0; i < n; i++) arr[i].Init(m, b);
}

MatrixFloat::MatrixFloat(const MatrixFloat& s)
{
	n = s.n;
	m = s.m;
	int i;
	arr = new VectorFloat[n];
	for (i = 0; i < n; i++) arr[i].Init(m, 0);
	for (i = 0; i < n; i++)
		for (int j = 0; j < m; j++)  arr[i][j] = s.arr[i][j];

}

MatrixFloat& MatrixFloat::operator=(const MatrixFloat& s)
{
	if (this != &s) {
		int i;
		if (n != s.n || m != s.m) {
			n = s.n; m = s.m;
			if (arr != nullptr) {
				delete[] arr;
			}
			arr = new VectorFloat[n];
			for (i = 0; i < n; i++) arr[i].Init(m, 0);
		}
		for (i = 0; i < n; i++)
			for (int j = 0; j < m; j++)  arr[i][j] = s.arr[i][j];

	}
	return *this;
}
VectorFloat& MatrixFloat::operator[](int index)
{
	if (index >= 0 && index < n) return arr[index];
	cout << " Error : operator[] - index index out of range \n";
	return arr[0];
}

MatrixFloat& MatrixFloat::operator=(MatrixFloat&& s) noexcept
{
	n = s.n; m = s.m;
	arr = s.arr;
	s.arr = nullptr;
	s.n = 0; s.m = 0;
	return *this;
}
istream& operator>>(istream& is, MatrixFloat& s)
{
	for (int i = 0; i < s.n; i++) is >> s.arr[i];
	return is;
}

ostream& operator<<(ostream& os, MatrixFloat& s)
{
	for (int i = 0; i < s.n; i++) os << s.arr[i];  // << endl;
	return os;
}
MatrixFloat& MatrixFloat::operator++() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] += 1;
		}
	}
	return *this;
}
MatrixFloat& MatrixFloat::operator--() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] -= 1;
		}
	}
	return *this;
}
MatrixFloat& MatrixFloat::operator+=(const MatrixFloat& s) {
	if (s.n == n) for (int i = 0; i < n; i++) arr[i] += s.arr[i];
	else {
		cout << "Error: matrices of different dimensions \n";
		cout << "The += operation was not performed. \n";
	}
	return *this;
}

MatrixFloat& MatrixFloat::operator+=(const float& b) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] += b;
		}
	}
	return *this;
}
MatrixFloat  MatrixFloat::operator+(const MatrixFloat& b) {
	MatrixFloat mat(*this);
	if (b.n == n) {
		mat += b;
	}
	else
	{
		cout << "Error: matrices of different dimensions \n";
		cout << "The += operation was not performed. \n";
	}
	return mat;
}
MatrixFloat  MatrixFloat::operator+(const int& b) {
	MatrixFloat mat(*this);
	mat += b;
	return mat;
}
MatrixFloat  MatrixFloat::operator+(const float& b) {
	MatrixFloat mat(*this);
	mat += b;
	return mat;
}
MatrixFloat& MatrixFloat::operator-=(const MatrixFloat& s) {
	if (s.n == n) for (int i = 0; i < n; i++) arr[i] -= s.arr[i];
	else {
		cout << "Error: matrices of different dimensions \n";
		cout << "The += operation was not performed. \n";
	}
	return *this;
}
MatrixFloat& MatrixFloat::operator-=(const int& b) {
	for (int i = 0; i < n; i++) arr[i] -= b;
	return *this;
}
MatrixFloat& MatrixFloat::operator-=(const float& b) {
	for (int i = 0; i < n; i++) arr[i] -= b;
	return *this;
}
MatrixFloat  MatrixFloat::operator-(const MatrixFloat& b) {
	MatrixFloat mat(*this);
	mat -= b;
	return mat;
}
MatrixFloat  MatrixFloat::operator-(const int& b) {
	MatrixFloat mat(*this);
	mat -= b;
	return mat;
}
MatrixFloat  MatrixFloat::operator-(const float& b) {
	MatrixFloat mat(*this);
	mat -= b;
	return mat;
}
MatrixFloat& MatrixFloat::operator*=(const int& b) {
	MatrixFloat tmp;
	if (b == 0) {
		tmp.state = BAD_MULTIPLY;
		cout << "Error Multiply" << endl;
		return *this;
	}
	else for (int i = 0; i < n; i++) arr[i] *= b;
	return *this;
	return tmp;
}
MatrixFloat& MatrixFloat::operator*=(const float& b) {
	MatrixFloat tmp;
	if (b == 0) {
		tmp.state = BAD_MULTIPLY;
		cout << "Error Multiply" << endl;
		return *this;
	}
	else for (int i = 0; i < n; i++) arr[i] *= b;
	return *this;
	return tmp;
}
MatrixFloat  MatrixFloat::operator*(const MatrixFloat& b) {
	if (n == b.m && m == b.m) {
		MatrixFloat ret(m, n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				ret[i][j] = 0;
				for (int l = 0; l < m; l++) ret[i][j] += arr[i][l] * b.arr[l][j];
			}
		return ret;
	}
	else {
		cout << "Error: matrices of different dimensions \n";
		cout << "The *  operation was not performed. \n";
		return *this;
	}
}
VectorFloat  MatrixFloat::operator*(const VectorFloat& b) {   //matrix*vect
	VectorFloat ret(n);
	if (n == b.num) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				ret[i] += arr[i][j] * b.v[j];
			}
	}
	else {
		cout << "Error: matrix and vector different dimensions \n";
		cout << "The *  operation was not performed. \n";
	}
	return ret;
}
MatrixFloat  MatrixFloat::operator*(const float& b) {
	MatrixFloat mat(*this);
	MatrixFloat tmp;
	if (b == 0) {
		tmp.state = BAD_MULTIPLY;
		cout << "Error Multiply" << endl;
		return mat;
	}
	else mat *= b;
	return mat;
	return tmp;
}
MatrixFloat& MatrixFloat::operator/=(const int& b) {
	MatrixFloat tmp;
	if (b==0)
	{
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	else for (int i = 0; i < n; i++) arr[i] /= b;
	return *this;
	return tmp;
}
MatrixFloat& MatrixFloat::operator/=(const float& b) {
	MatrixFloat tmp;
	if (b == 0)
	{
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	else for (int i = 0; i < n; i++) arr[i] /= b;
	return *this;
	return tmp;
}
MatrixFloat  MatrixFloat::operator/(const int& b) {
	MatrixFloat mat(*this);
	MatrixFloat tmp;
	if (b == 0)
	{
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return mat;
	}
	else for (int i = 0; i < n; i++) arr[i] /= b;
	return mat;
	return tmp;
}
MatrixFloat  MatrixFloat::operator/(const float& b) {
	MatrixFloat mat(*this);
	MatrixFloat tmp;
	if (b == 0)
	{
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return mat;
	}
	else for (int i = 0; i < n; i++) arr[i] /= b;
	return mat;
	return tmp;
}
bool MatrixFloat::operator>(const  MatrixFloat& s) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] > s.arr[i][j])
				return true;
		}
	}
	return false;
}
bool MatrixFloat::operator>=(const MatrixFloat& s) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] >= s.arr[i][j])
				return true;
		}
	}
	return false;
}
bool MatrixFloat::operator<(const  MatrixFloat& s) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] < s.arr[i][j])
				return true;
		}
	}
	return false;
}
bool MatrixFloat::operator<=(const MatrixFloat& s) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] >= s.arr[i][j])
				return true;
		}
	}
	return false;
}
void task2(){
	MatrixFloat A(3);
	MatrixFloat B(3, 3);
	MatrixFloat C(3, 3, 10);
	MatrixFloat D(3, 3, 5.2);
	MatrixFloat E(3, 3, 12);
	MatrixFloat matcopy(C);
	VectorFloat vector1(3,5);
	VectorFloat vector2(3);
	float value = 2.4;
	cout << "Test class MatrixFloat : " << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << A;
	cout << "------------------------------------------------------------------" << endl;
	cout << B;
	cout << "------------------------------------------------------------------" << endl;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << D;
	cout << "------------------------------------------------------------------" << endl;
	cout << vector1;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Test reload operation:" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload ++ :" << endl;
	cout << (++C);
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload -- :" << endl;
	cout << (--C);
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix + matrix :" << endl;
	C += D;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix + float :" << endl;
	C += value;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix - float :" << endl;
	C -= value;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix - matrix :" << endl;
	C -= D;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matix * matrix :" << endl;
	C = C * D;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix * value :" << endl;
	C *= value;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix * 0 :" << endl;
	C *= 0;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix / float :" << endl;
	C /= value;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Reload matrix / 0 :" << endl;
	C /= 0;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Expression 1" << endl;
	cout << "C = C + D * value - B * 2 + C / 10 : " << endl;
	C = (C + D * value - B * 2 + C) / 10;
	cout << C;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Expression 2" << endl;
	cout << "vector2 = (C * vector1 + D * vector1) : " << endl;
	vector2 = ((C * vector1 + D * vector1)+100)/value;
	cout << vector2;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Object state " << matcopy.getState() << endl;
	if (matcopy < C)  cout << "ObjectCopy less ObjectDef" << endl;
	else if (matcopy > C)  cout << "ObjectCopy More ObjectDef" << endl;
	else if (matcopy <= C) cout << "ObjectCopy less Exactly ObjectDef" << endl;
	else if (matcopy >= C) cout << "ObjectCopy more Exactly ObjectDef" << endl;
	cout << "End testing." << endl;
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------3-----------------------------------------------------------------

void task3(){}
/*
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
