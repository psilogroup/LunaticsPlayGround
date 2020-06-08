#ifndef __CAMERA__
# define __CAMERA__

#include "baselib.h"
#include "vec3d.h"

class Camera
{
 public:
   vec3d position;
   vec3d rotation;
   glm::mat4 projection;
   glm::mat4 view;
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
   void setCamera();
   void setProjectionMatrix(float fov,float zNear, float zFar);
   void recalculateViewMatrix();
};

#endif
