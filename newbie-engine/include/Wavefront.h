#ifndef __WAVEFRONT__
#define __WAVEFRONT__

#include "vec3d.h"
#include "Object.h"
#include "Mesh.h"

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
