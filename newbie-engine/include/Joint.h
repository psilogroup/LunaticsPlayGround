/*
 * Joint.h
 *
 *  Created on: 19/07/2009
 *      Author: newbie
 */

#ifndef __JOINT__

#define __JOINT__

#ifdef WIN32
#include <windows.h>
#endif
#include <ode/ode.h>
#include "vec4.h"
#include "Object.h"
#include "World.h"

class Joint
{
public:
  Object bodyA;
  Object bodyB;
  vec3d anchorA;
  vec3d aixsA;
  dJointID iJoint;
  Joint();
  virtual
  ~Joint();
};

class Servo : public Joint
{
public:
  Servo(Object *a, Object *b, vec3d anchor, vec3d aixs, dWorldID world);
  void setTorque(float torque);
  void turn(float angle);
  void setLowsStop(float angle);
  void setHiStop(float angle);
  float getAngle();

  virtual ~Servo();
};

class Motor : public Joint
{

  public:
        dJointID jointConnection;
        Motor(Object *chassi,Object *roda,vec3d anchor,vec3d aixs,vec3d aixs2,vec3d aixs3, dWorldID world);
        void setTorque(float tx,float ty,float tz);
        void setVelocity(float vx,float vy,float vz);
        virtual ~Motor();

};


class CarWheel : public Joint
{
  public:
  vec3d aixsB;
  CarWheel (Object *chassi,Object *roda,vec3d anchor,vec3d aixs,vec3d aixs2,World *world);

  void setSpeedy(float speedy,float force);
  void steer(float angle,float force);
  void setLowsStop(float angle);
  void setHiStop(float angle);

  virtual ~CarWheel();

};
#endif /* JOINT_H_ */

