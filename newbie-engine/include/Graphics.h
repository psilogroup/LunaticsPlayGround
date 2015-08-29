#ifndef __GRAPHICS__
#define __GRAPHICS__

#ifdef WIN32
#include <windows.h>
#endif

#include <math.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "vec3d.h"
#include <ode/ode.h>

class Graphics
{
 public:
   static void trigon(vec3d a,vec3d b,vec3d c)
     {

	vec3d normal = normalOfPlane(a,b,c);
	glBegin(GL_TRIANGLES);
	glNormal3f(normal.x,normal.y,normal.z);
	glVertex3f(a.x,a.y,b.z);
	glVertex3f(b.x,b.y,b.z);
	glVertex3f(c.x,c.y,c.z);

	glEnd();

     };

   static void plane(vec3d a,vec3d b,vec3d c,vec3d d)
     {
	trigon(a,b,c);
	trigon(a,c,d);
     };

   static void quad(vec3d a,vec3d b,vec3d c,vec3d d)
     {
	vec3d n=normalOfPlane(a,b,c);
	glNormal3f(n.x,n.y,n.z);
	glBegin(GL_QUADS);
	glVertex3f(a.x,a.y,a.z);
	glVertex3f(b.x,b.y,b.z);
	glVertex3f(c.x,c.y,c.z);
	glVertex3f(d.x,d.y,d.z);
	glEnd();
     };

   static void cube(float sizex,float sizey,float sizez)
     {
	float lx = sizex*0.5f;
	float ly = sizey*0.5f;
	float lz = sizez*0.5f;

	// sides
	glBegin (GL_TRIANGLE_STRIP);
	glNormal3f (-1,0,0);
	glVertex3f (-lx,-ly,-lz);
	glVertex3f (-lx,-ly,lz);
	glVertex3f (-lx,ly,-lz);
	glVertex3f (-lx,ly,lz);
	glNormal3f (0,1,0);
	glVertex3f (lx,ly,-lz);
	glVertex3f (lx,ly,lz);
	glNormal3f (1,0,0);
	glVertex3f (lx,-ly,-lz);
	glVertex3f (lx,-ly,lz);
	glNormal3f (0,-1,0);
	glVertex3f (-lx,-ly,-lz);
	glVertex3f (-lx,-ly,lz);
	glEnd();

	// top face
	glBegin (GL_TRIANGLE_FAN);
	glNormal3f (0,0,1);
	glVertex3f (-lx,-ly,lz);
	glVertex3f (lx,-ly,lz);
	glVertex3f (lx,ly,lz);
	glVertex3f (-lx,ly,lz);
	glEnd();

	// bottom face
	glBegin (GL_TRIANGLE_FAN);
	glNormal3f (0,0,-1);
	glVertex3f (-lx,-ly,-lz);
	glVertex3f (-lx,ly,-lz);
	glVertex3f (lx,ly,-lz);
	glVertex3f (lx,-ly,-lz);
	glEnd();

     };

   static vec3d crossProduct(vec3d a,vec3d b)
     {
	vec3d r;
	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return r;
     };

   static vec3d normalize(vec3d a)
     {
	float length = (float) sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	vec3d r;

	if (length == 0.0f)
	  length =  1.0f;

	r.x = r.x / length;
	r.y = r.y / length;
	r.z = r.z / length;
	return r;
     };

   static vec3d normalOfPlane(vec3d a,vec3d b, vec3d c)
     {
	vec3d v1;
	vec3d v2;
	vec3d n;
	vec3d r;
	v1.x = a.x - b.x;
	v1.y = a.y - b.y;
	v1.z = a.z - b.z;

	v2.x = b.x - c.x;
	v2.y = b.y - c.y;
	v2.z = b.z - c.z;
	n = normalize(crossProduct(v1,v2));
	return n;

     };

     static vec3d EulerFromQ(const dReal *q)
     {
        vec3d v;
        v.x = atan2f(2*(q[0]*q[1]+q[2]*q[3]),1-2*(q[1]*q[1]+q[2]*q[2]));
        v.y = asinf(2*(q[0]*q[2]-q[3]-q[1]));
        v.z = atan2f(2*(q[0]*q[3]+q[1]*q[2]),1-2*(q[2]*q[2]+q[3]*q[3]));

        return v;

     };

};

#endif
