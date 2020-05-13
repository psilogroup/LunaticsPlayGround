#ifndef __MATRIX__
# define __MATRIX__
#ifdef WIN32
#include <windows.h>
#endif
# include "vec3d.h"

class Matrix
{
 public:
   float m[16];
   Matrix();
   void setIdentity();
   void RotX(float a);
   void RotY(float a);
   void RotZ(float a);
   Matrix& operator*(const Matrix& mat);
   Matrix& operator=(const Matrix& mat);
   //Matrix operator+(Matrix& mat);
   //Matrix operator-(Matrix& mat);
};

vec3d vecbymat(vec3d vec, Matrix mat);

class MatrixRotX : public Matrix
{
 public:
   ///		 1		0		0
   ///	    RX = 0		cx		sx
   ///		 0		-sx		cx
   MatrixRotX(float a);
};

class MatrixRotY : public Matrix
{
 public:
   ///     cy		0		-sy
   ///	RY = 0		1		0
   ///	     sy		0		cy
   MatrixRotY(float a);
};

class MatrixRotZ : public Matrix
{
 public:
   //!		 cz		sz		0
   //!	RZ = -sz	cz		0
   //!		 0		0		1
   MatrixRotZ(float a);
};

#endif
