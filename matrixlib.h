#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

struct Matrix
{
float e[16];              
};

struct Vector
{
float e[4];              

float& operator[](int index)
{
return e[index];      
}

};

ostream& operator<<(ostream& out, const Matrix &m);
ostream& operator<<(ostream& out, const Vector &v);

Matrix buildidentitymatrix(void);
Matrix buildrotationmatrix(float theta, float x, float y, float z);
Matrix buildscalematrix(float x, float y, float z);
Matrix buildtranslationmatrix(float x, float y, float z);

Vector buildvector(float x, float y, float z);

Matrix operator*(const Matrix &a, const Matrix &b);
void operator*=(Matrix &a, const Matrix &b);
Vector operator*(const Matrix &a, const Vector &v);

ostream& operator<<(ostream& out, const Matrix &m)
{
out << m.e[0] << " " << m.e[4] << " " <<  m.e[8] << " " <<  m.e[12] << endl;
out << m.e[1] << " " <<  m.e[5] << " " <<  m.e[9] << " " <<  m.e[13] << endl;
out << m.e[2] << " " <<  m.e[6] << " " <<  m.e[10] << " " <<  m.e[14] << endl;
out << m.e[3] << " " <<  m.e[7] << " " <<  m.e[11] << " " <<  m.e[15];
return out;         
}

ostream& operator<<(ostream& out, const Vector &v)
{
out << "(" << v.e[0] << ", " << v.e[1] << ", " <<  v.e[2] << ")";
return out;         
}

Matrix buildidentitymatrix(void)
{
Matrix m;       
m.e[0] = 1;
m.e[1] = 0;
m.e[2] = 0;
m.e[3] = 0;

m.e[4] = 0;
m.e[5] = 1;
m.e[6] = 0;
m.e[7] = 0;

m.e[8] = 0;
m.e[9] = 0;
m.e[10] = 1;
m.e[11] = 0;

m.e[12] = 0;
m.e[13] = 0;
m.e[14] = 0;
m.e[15] = 1;     

return m;
}

Matrix buildrotationmatrix(float theta, float x, float y, float z)
{
Matrix m;       
float c = cos(theta);
float s = sin(theta);
float t = 1 - cos(theta);     
m.e[0] = t*x*x + c;
m.e[1] = t*x*y + s*z;
m.e[2] = t*x*z - s*y;
m.e[3] = 0;
     
m.e[4] = t*x*y - s*z;
m.e[5] = t*y*y + c;
m.e[6] = t*y*z + s*x;
m.e[7] = 0;

m.e[8] = t*x*z + s*y;
m.e[9] = t*y*z - s*x;
m.e[10] = t*z*z + c;
m.e[11] = 0;

m.e[12] = 0;
m.e[13] = 0;
m.e[14] = 0;
m.e[15] = 1;          

return m;
}

Matrix buildscalematrix(float x, float y, float z)
{
Matrix m;     
     
m.e[0] = x;
m.e[1] = 0;
m.e[2] = 0;
m.e[3] = 0;

m.e[4] = 0;
m.e[5] = y;
m.e[6] = 0;
m.e[7] = 0;

m.e[8] = 0;
m.e[9] = 0;
m.e[10] = z;
m.e[11] = 0;

m.e[12] = 0;
m.e[13] = 0;
m.e[14] = 0;
m.e[15] = 1;     

return m;
}

Matrix buildtranslationmatrix(float x, float y, float z)
{
Matrix m;
m.e[0] = 1;
m.e[1] = 0;
m.e[2] = 0;
m.e[3] = 0;

m.e[4] = 0;
m.e[5] = 1;
m.e[6] = 0;
m.e[7] = 0;

m.e[8] = 0;
m.e[9] = 0;
m.e[10] = 1;
m.e[11] = 0;

m.e[12] = x;
m.e[13] = y;
m.e[14] = z;
m.e[15] = 1;     
return m;
}

Matrix operator*(const Matrix &a, const Matrix &b)
{    
Matrix m;     

m.e[0] = b.e[0]*a.e[0] + b.e[1]*a.e[4] + b.e[2]*a.e[8] + b.e[3]*a.e[12];
m.e[1] = b.e[0]*a.e[1] + b.e[1]*a.e[5] + b.e[2]*a.e[9] + b.e[3]*a.e[13];
m.e[2] = b.e[0]*a.e[2] + b.e[1]*a.e[6] + b.e[2]*a.e[10] + b.e[3]*a.e[14];
m.e[3] = b.e[0]*a.e[3] + b.e[1]*a.e[7] + b.e[2]*a.e[11] + b.e[3]*a.e[15];

m.e[4] = b.e[4]*a.e[0] + b.e[5]*a.e[4] + b.e[6]*a.e[8] + b.e[7]*a.e[12];
m.e[5] = b.e[4]*a.e[1] + b.e[5]*a.e[5] + b.e[6]*a.e[9] + b.e[7]*a.e[13];
m.e[6] = b.e[4]*a.e[2] + b.e[5]*a.e[6] + b.e[6]*a.e[10] + b.e[7]*a.e[14];
m.e[7] = b.e[4]*a.e[3] + b.e[5]*a.e[7] + b.e[6]*a.e[11] + b.e[7]*a.e[15];

m.e[8] = b.e[8]*a.e[0] + b.e[9]*a.e[4] + b.e[10]*a.e[8] + b.e[11]*a.e[12];
m.e[9] = b.e[8]*a.e[1] + b.e[9]*a.e[5] + b.e[10]*a.e[9] + b.e[11]*a.e[13];
m.e[10] = b.e[8]*a.e[2] + b.e[9]*a.e[6] + b.e[10]*a.e[10] + b.e[11]*a.e[14];
m.e[11] = b.e[8]*a.e[3] + b.e[9]*a.e[7] + b.e[10]*a.e[11] + b.e[11]*a.e[15];

m.e[12] = b.e[12]*a.e[0] + b.e[13]*a.e[4] + b.e[14]*a.e[8] + b.e[15]*a.e[12];
m.e[13] = b.e[12]*a.e[1] + b.e[13]*a.e[5] + b.e[14]*a.e[9] + b.e[15]*a.e[13];
m.e[14] = b.e[12]*a.e[2] + b.e[13]*a.e[6] + b.e[14]*a.e[10] + b.e[15]*a.e[14];
m.e[15] = b.e[12]*a.e[3] + b.e[13]*a.e[7] + b.e[14]*a.e[11] + b.e[15]*a.e[15];     

return m;
}


void operator*=(Matrix &a, const Matrix &b)
{
a = a*b;
}


Vector buildvector(float x, float y, float z)
{
Vector v;
v.e[0] = x;
v.e[1] = y;
v.e[2] = z;
v.e[3] = 1;
return v;              
}

Vector operator*(const Matrix &a, const Vector &v)
{
Vector vnew;

vnew.e[0] = v.e[0]*a.e[0] + v.e[1]*a.e[4] + v.e[2]*a.e[8] + v.e[3]*a.e[12];
vnew.e[1] = v.e[0]*a.e[1] + v.e[1]*a.e[5] + v.e[2]*a.e[9] + v.e[3]*a.e[13];
vnew.e[2] = v.e[0]*a.e[2] + v.e[1]*a.e[6] + v.e[2]*a.e[10] + v.e[3]*a.e[14];
vnew.e[3] = v.e[0]*a.e[3] + v.e[1]*a.e[7] + v.e[2]*a.e[11] + v.e[3]*a.e[15];

return vnew;
}
