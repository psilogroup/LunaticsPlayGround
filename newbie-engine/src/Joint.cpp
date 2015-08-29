/*
 * Joint.cpp
 *d
 *  Created on: 19/07/2009
 *      Author: newbie
 */

#include "Joint.h"
#include <ode/ode.h>
Joint::Joint()
{
  // TODO Auto-generated constructor stub

}

Joint::~Joint()
{
  // TODO Auto-generated destructor stub
}

Servo::Servo(Object *a, Object *b, vec3d anchor, vec3d aixs, dWorldID world)
{
  iJoint = dJointCreateHinge(world,0);
  dJointAttach(iJoint, a->iBody,b->iBody);

  dJointSetHingeAnchor(iJoint,anchor.x,anchor.y,anchor.z);
  dJointSetHingeAxis(iJoint,aixs.x,aixs.y,aixs.z);
}





  void Servo::setTorque(float torque)
  {
    dJointSetHingeParam (iJoint,dParamFMax,torque);
  }

  void Servo::turn(float angle)
  {
    dReal curturn = dJointGetHingeAngle(iJoint);

    dJointSetHingeParam(iJoint,dParamVel,((DEG2RAD(angle))-curturn)*1);
  }

  void Servo::setLowsStop(float angle)
  {
    dJointSetHingeParam (iJoint,dParamLoStop,DEG2RAD(angle));
  }

  void Servo::setHiStop(float angle)
  {
    dJointSetHingeParam (iJoint,dParamHiStop,DEG2RAD(angle));
  }

  float Servo::getAngle()
  {
    return RAD2DEG(dJointGetHingeAngle(iJoint));
  }


Servo::~Servo()
{
  dJointDestroy(iJoint);
}


Motor::Motor(Object *chassi,Object *roda,vec3d anchor,vec3d aixs,vec3d aixs2,vec3d aixs3, dWorldID world)
{
    jointConnection = dJointCreateBall(world,0);
    dJointAttach(jointConnection,chassi->iBody,roda->iBody);
    dJointSetBallAnchor (jointConnection,anchor.x,anchor.y,anchor.z);


    iJoint = dJointCreateAMotor(world,0);

    dJointAttach(iJoint, chassi->iBody,roda->iBody);

    dJointSetAMotorNumAxes(iJoint, 3);

    dJointSetAMotorAxis(iJoint,0,1,aixs.x,aixs.y,aixs.z);
    dJointSetAMotorAxis(iJoint,1,1,aixs2.x,aixs2.y,aixs2.z);
    dJointSetAMotorAxis(iJoint,2,1,aixs3.x,aixs3.y,aixs3.z);


}

void Motor::setTorque(float tx,float ty,float tz)
{
    dJointSetAMotorParam(iJoint,dParamFMax,tx);
    dJointSetAMotorParam(iJoint,dParamFMax2,ty);
    dJointSetAMotorParam(iJoint,dParamFMax3,tz);
}

void Motor::setVelocity(float vx,float vy,float vz)
{
    dJointSetAMotorParam(iJoint,dParamVel,vx);
    dJointSetAMotorParam(iJoint,dParamVel2,vy);
    dJointSetAMotorParam(iJoint,dParamVel3,vz);
}

Motor::~Motor()
{
    dJointDestroy(iJoint);
    dJointDestroy(jointConnection);
}

CarWheel::CarWheel (Object *chassi,Object *roda,vec3d anchor,vec3d aixs,vec3d aixs2,World *world)
{
    iJoint = dJointCreateHinge2(world->world,0);
    dJointAttach(iJoint,chassi->iBody,roda->iBody);

    dJointSetHinge2Anchor(iJoint,anchor.x,anchor.y,anchor.z);
    dJointSetHinge2Axis1(iJoint,aixs.x,aixs.y,aixs.z);
    dJointSetHinge2Axis2(iJoint,aixs2.x,aixs2.y,aixs2.z);

}

  void CarWheel::setSpeedy(float speedy,float force)
  {

  }

  void CarWheel::steer(float angle,float force)
  {


  }

  void CarWheel::setLowsStop(float angle)
  {

  }

  void CarWheel::setHiStop(float angle)
  {

  }

  CarWheel::~CarWheel()
  {
    dJointDestroy(iJoint);
  }
