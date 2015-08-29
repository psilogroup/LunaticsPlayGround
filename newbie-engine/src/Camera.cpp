#include "Camera.h"
#include "definitions.h"
#include <math.h>

Camera::Camera() {
    follower = NULL;
}

Camera::Camera(vec3d p, vec3d r) {
   position.x = p.x;
   position.y = p.y;
   position.z = p.z;

   rotation.x = r.x;
   rotation.y = r.y;
   rotation.z = r.z;
}

void Camera::setPosition(vec3d p)
{
  position.x = p.x;
  position.y = p.y;
  position.z = p.z;


}

void Camera::setRotation(vec3d r)
{
  rotation.x = r.x;
  rotation.y = r.y;
  rotation.z = r.z;
}


void Camera::Turn(int deltaX, int deltaY)
{
   rotation.x += float(deltaX) * 0.5f;
   rotation.y += float(deltaY) * 0.5f;
}

void Camera::UpDown(int deltaX,int deltaY)
{
   //float side = 0.01f * float(deltaX);
   //float fwd = 0.01f * float(deltaY);
   //float s = sinf(DEG2RAD(position.x));
   //float c = cosf(DEG2RAD(position.y));

   //position.x += -s*side + c*fwd;
   //position.y += c*side + s*fwd;
}

void Camera::setFollower(vec3d *follow)
{
    follower = follow;
}
