
#ifndef __ABSTRACT_VEICHLE__
#define __ABSTRACT_VEICHLE__

#include <windows.h>
#include "ode/ode.h"

class AbstractVeiclhe
{
   
 public:
      dJointID *joints;
      dBodyID *whells;
      dGeomID *geoms;
      
}


#endif
