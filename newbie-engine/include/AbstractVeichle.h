#ifndef __ABSTRACT_VEICHLE__
#define __ABSTRACT_VEICHLE__

# ifdef WIN32
#  include <windows.h>
# endif
#include "ode/ode.h"

class AbstractVeiclhe
{
   
 public:
      dJointID *joints;
      dBodyID *whells;
      dGeomID *geoms;
      
}


#endif
