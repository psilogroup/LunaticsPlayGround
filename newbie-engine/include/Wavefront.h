#ifndef __WAVEFRONT__
#define __WAVEFRONT__
#ifdef WIN32
#include <windows.h>
#endif
#include "vec3d.h"
#include "Object.h"
#include "Mesh.h"
#include <ode/ode.h>
#include <string>
#include <iostream>

class Wavefront: public Mesh
{
 public:
   
   Wavefront(std::string filename);
   Wavefront();
   void load(std::string filename);
   
   ~Wavefront();

};

#endif
