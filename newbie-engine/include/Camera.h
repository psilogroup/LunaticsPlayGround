#ifndef __CAMERA__
# define __CAMERA__



# include "Matrix.h"
class Camera
{
 public:
   vec3d position;
   vec3d rotation;
   Matrix *matrix;
   vec3d *follower;
   unsigned int width;
   unsigned int height;
   Camera();
   Camera(vec3d p,vec3d r);
   void setPosition (vec3d p);
   void setRotation (vec3d r);
   void Turn(int deltaX, int deltaY);
   void UpDown(int deltaX,int deltaY);
   void setFollower(vec3d *follow);
};

#endif
