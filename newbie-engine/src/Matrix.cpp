#include "Matrix.h"
#include "definitions.h"
#include "string.h"
#include <math.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#define M(x,y) (y*4+x)

/**
 * Classe para Manipulação de matrizes
 */

Matrix::Matrix()
{
 setIdentity();
}

/**
 * seta a matrix como identidade
 * |1 0 0 0|
 * |0 1 0 0|
 * |0 0 1 0|
 * |0 0 0 1|
 */

void Matrix::setIdentity()
{

 m[0]  = 1.0f;  m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = 0.0f;
 m[4]  = 0.0f;  m[5]  = 1.0f; m[6]  = 0.0f; m[7]  = 0.0f;
 m[8]  = 0.0f;  m[9]  = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
 m[12] = 0.0f; m[13]  = 0.0f; m[14] = 0.0f; m[15] = 1.0f;

}

/**
 * Multiplica a Matrix por um vetor 3x1
 */
vec3d vecbymat(vec3d vec, Matrix mat)
{
   vec3d r;
   r.x = mat.m[0] * vec.x + mat.m[1]  * vec.y + mat.m[2]    * vec.z + mat.m[3];
   r.y = mat.m[4] * vec.x + mat.m[5]  * vec.y + mat.m[6]    * vec.z + mat.m[7];
   r.z = mat.m[8] * vec.x + mat.m[9]  * vec.y + mat.m[10]   * vec.z + mat.m[11];
   return r;
}


Matrix& Matrix::operator*(const Matrix& mat)
{
	float _m[16];
	for(int i = 0; i <4;i++)
		for(int j = 0; j<4; j++)
		{
			float sum = 0.0f;
			for(int k=0;k<4;k++)
				sum += this->m[i*4+k] * mat.m[k*4+j];
			_m[i*4+j] = sum;
		}
   memcpy(this->m,_m,sizeof(float)*16);

	return *this;
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	memcpy(this->m,mat.m,sizeof(float)*16);
	return *this;
}

void Matrix::RotX(float a)
{
	float c = cosf(DEG2RAD(a));
	float s = sinf(DEG2RAD(a));
	m[0]  = 1.0f;  m[1]  =  0.0f; m[2]  = 0.0f; m[3]  = 0.0f;
	m[4]  = 0.0f;  m[5]  =  c;    m[6]  = s;    m[7]  = 0.0f;
	m[8]  = 0.0f;  m[9]  =  -s;   m[10] = c;    m[11] = 0.0f;
	m[12] = 0.0f; m[13]  =  0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

void Matrix::RotY(float a)
{
	 float c = cosf(DEG2RAD(a));
	 float s = sinf(DEG2RAD(a));

	 m[0]  = c;     m[1]   = 0.0f; m[2]  =  -s; m[3]  = 0.0f;
	 m[4]  = 0.0f;  m[5]   = 1.0f; m[6]  =  0.0f; m[7]  = 0.0f;
	 m[8]  = s;     m[9]   = 0.0f; m[10] =  c; m[11] = 0.0f;
	 m[12] = 0.0f;  m[13]  = 0.0f; m[14] =  0.0f; m[15] = 1.0f;
}

void Matrix::RotZ(float a)
{
	 float c = cosf(DEG2RAD(a));
	  float s = sinf(DEG2RAD(a));

	  m[0]  = c;     m[1]   = s;    m[2]  = 0.0f; m[3]  = 0.0f;
	  m[4]  = -s;    m[5]   = c;    m[6]  = 0.0f; m[7]  = 0.0f;
	  m[8]  = 0.0f;  m[9]   = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
	  m[12] = 0.0f;  m[13]  = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

/**
 * Matriz de Rotação no Eixo X
 * |1  0  0  0|
 * |0  cx sx 0|
 * |0 -sx cx 0|
 * |0  0  0  1|
 */
MatrixRotX::MatrixRotX(float a)
{
 float c = cosf(a);
 float s = sinf(a);
  m[0]  = 1.0f;  m[1]  =  0.0f; m[2]  = 0.0f; m[3]  = 0.0f;
  m[4]  = 0.0f;  m[5]  =  c;    m[6]  = s;    m[7]  = 0.0f;
  m[8]  = 0.0f;  m[9]  =  -s;   m[10] = c;    m[11] = 0.0f;
  m[12] = 0.0f; m[13]  =  0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

/**
 * Matriz de Rotação no eixo Y
 * |c 0 -s 0|
 * |0 1  0 0|
 * |s 0  c 0|
 * |0 0  0 1|
 */
MatrixRotY::MatrixRotY(float a)
{
 float c = cosf(DEG2RAD(a));
 float s = sinf(DEG2RAD(a));

 m[0]  = c;     m[1]   = 0.0f; m[2]  =  -s; m[3]  = 0.0f;
 m[4]  = 0.0f;  m[5]   = 1.0f; m[6]  =  0.0f; m[7]  = 0.0f;
 m[8]  = s;     m[9]   = 0.0f; m[10] =  c; m[11] = 0.0f;
 m[12] = 0.0f;  m[13]  = 0.0f; m[14] =  0.0f; m[15] = 1.0f;
}

/**
 * Matriz de Rotação no eixo Z
 * | c  s 0 0|
 * |-s  c 0 0|
 * | 0  0 1 0|
 * | 0  0 0 1|
 */
MatrixRotZ::MatrixRotZ(float a)
{
  float c = cosf(DEG2RAD(a));
  float s = sinf(DEG2RAD(a));

  m[0]  = c;     m[1]   = s;    m[2]  = 0.0f; m[3]  = 0.0f;
  m[4]  = -s;    m[5]   = c;    m[6]  = 0.0f; m[7]  = 0.0f;
  m[8]  = 0.0f;  m[9]   = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
  m[12] = 0.0f;  m[13]  = 0.0f; m[14] = 0.0f; m[15] = 1.0f;

}
