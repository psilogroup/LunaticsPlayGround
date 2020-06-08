#include "baselib.h"
#include "Object.h"
#include "Graphics.h"
#include "vec4.h"


Object::Object()
{

	iSize.x = iSize.y = iSize.z = 1;
	iPosition.x = iPosition.y = iPosition.z = 0;
	iVel.x = iVel.y =iVel.z = 0;
	iM = 1;
	Mat = new Material();
	dQFromAxisAndAngle(q,1,0,0,0);

	data = new BodyData();
	data->setName("Object");
};

void Object::Draw(Shader *shader)
{

}

void Object::MakeBody(dWorldID world)
{


	iBody = dBodyCreate(world);
	dBodySetQuaternion(iBody,q);
	dBodySetPosition(iBody,iPosition.x,iPosition.y,iPosition.z);
	dBodySetLinearVel(iBody,iVel.x,iVel.y,iVel.z);
	dMassSetBox(&iMass,iM,iSize.x,iSize.y,iSize.z);
	dMassAdjust(&iMass,iM/2.0);
	dBodySetMass(iBody,&iMass);



	disabledSteps = 0;
	dBodySetAutoDisableFlag(iBody,1);
	
	dBodySetData(iBody,data);
	dBodySetAutoDisableSteps(iBody, 15);
	dBodyDisable(iBody);

};

void Object::MakeGeom(dSpaceID space)
{
	iGeom = dCreateBox(space,iSize.x,iSize.y,iSize.z);

	dMatrix3 R,R0,R1,R2,R3;

	dRFromAxisAndAngle(R1,1,0,0,DEG2RAD(iRotate.x));
	dRFromAxisAndAngle(R2,0,1,0,DEG2RAD(iRotate.y));
	dRFromAxisAndAngle(R3,0,0,1,DEG2RAD(iRotate.z));
	dMultiply0 (R0,R1,R2,3,3,3);
	dMultiply0 (R, R0,R3,3,3,3);

	dGeomSetRotation(iGeom,R);
	dGeomSetPosition(iGeom, iPosition.x, iPosition.y, iPosition.z);
};

void Object::LinkBodyWithGeom()
{
	dGeomSetBody(iGeom,iBody);
}

void Object::Update()
{

};

void Object::UpdateDisableState()
{
	bool disabled = true;
	if (iBody == 0)
		return;

	if (dBodyIsEnabled(iBody) == 0)
		return;

	const dReal *lv = dBodyGetLinearVel(iBody);
	const dReal *av = dBodyGetAngularVel(iBody);

	
		if ((lv[0]*lv[0]+lv[1]*lv[1]+lv[2]*lv[2]) > DISABLE_THRESHOLD)
			disabled = false;

	
		if ((av[0]*av[0]+av[1]*av[1]+av[2]*av[2]) > DISABLE_THRESHOLD)
			disabled = false;

	if (disabled = false)
		disabledSteps++;

	if (disabledSteps > AUTO_DISABLE_STEPS)
	{
		dBodyDisable(iBody);
	}


};


void Object::Transform()
{
	setTransform(dGeomGetPosition(iGeom),dGeomGetRotation(iGeom));
};

Object::~Object()
{
	delete Mat;
}

void Object::showAABB()
{
	
}

void Object::setRotation(float x,float y,float z)
{
	dMatrix3 R,R0,R1,R2,R3;

	dRFromAxisAndAngle(R1,1,0,0,DEG2RAD(x));
	dRFromAxisAndAngle(R2,0,1,0,DEG2RAD(y));
	dRFromAxisAndAngle(R3,0,0,1,DEG2RAD(z));
	dMultiply0 (R0,R1,R2,3,3,3);
	dMultiply0 (R, R0,R3,3,3,3);

	dGeomSetRotation(iGeom,R);
	dBodySetRotation(iBody,R);
}
void Object::setPosition(float x,float y,float z)
{
	dGeomSetPosition(iGeom,x ,y,z);
	dBodySetPosition(iBody,x,y,z);

}
