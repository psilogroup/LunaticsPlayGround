#include "Sphere.h"
#include <stdio.h>

const int vCount = 1296;
const int iCount = 1296;

float vData[vCount*3];

Sphere::Sphere(float r,int slice,int stack)
{
   iRadius = r;
   iSlices = slice;
   iStacks = stack;
   data = new BodyData();
   data->setName("Sphere");
}

void Sphere::MakeBody(dWorldID world)
{
   iBody = dBodyCreate(world);
   dMassSetSphereTotal(&iMass,iM,iRadius);
   dBodySetMass(iBody,&iMass);
   dBodySetPosition(iBody,iPosition.x,iPosition.y,iPosition.z);
   dBodySetLinearVel(iBody,iVel.x,iVel.y,iVel.z);
   disabledSteps = 0;

   dBodySetData(iBody,data);

}

void Sphere::MakeGeom(dSpaceID space)
{
   iGeom = dCreateSphere(space,iRadius);
}

void Sphere::Draw()
{
   glPushMatrix();
   if (Mat != NULL)
     Mat->Build();
   Transform();
   //glutSolidSphere(iRadius,32,32);
   glPopMatrix();
}

void Sphere::Update()
{
   const dReal *p,*r;

   UpdateDisableState();

   if(dBodyIsEnabled(iBody) == 0)
     return;

   p = dBodyGetPosition(iBody);
   iPosition.x = p[0];
   iPosition.y = p[1];
   iPosition.z = p[2];
   r = dGeomGetRotation(iGeom);
   iRotate.x = p[0];
   iRotate.y = p[1];
   iRotate.z = p[2];
//   v = dBodyGetLinearVel(iBody);
//   dBodyAddForce(iBody,v[0]*v[0]+v[1]*v[1]+v[2]*v[2],0,0);
//   printf("x: %f, y: %f z: %f\n",p[0],p[1],p[2]);
};
