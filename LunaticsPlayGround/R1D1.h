#ifndef __R1D1__
#define __R1D1__
#include <ode/ode.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Graphics.h"
#include "definitions.h"


class Robot1
{
public:

	Cube *chassi;
	Cube *radar;
	Sphere *canonBody;
	Cylinder *canonGun;
	Sphere** canonBals;

	Cylinder *rodaFrontalEsquerda;
	Cylinder *rodaFrontalDireita;

	Cylinder *rodaTraseiraEsquerda;
	Cylinder *rodaTraseiraDireita;

	CarWheel *jointRodaFL;
	CarWheel *jointRodaFR;
	CarWheel *jointRodaBL;
	CarWheel *jointRodaBR;

	Servo *servoBody;
	Servo *servoGun;
	bool rightPressed;
	bool leftPressed;
	bool accellPressed;
	bool reversePressed;
	bool breaking;
	bool rotingLeft;
	bool rotingRight;
	bool rotingUp;
	bool rotingDown;

	float Cd;
	float S;
	float rho;
	float aceleador;
	float speed;
	float torque;
	float Fdrag;
	float Frr;
	float force;

	float getFrr(){return Frr;};
	float getSpeed(){return speed;};
	float getTorque(){return torque;};
	float getFdrag(){return Fdrag;};
	float getForce(){return force;};
	float bodyRot;
	float gunRot;
	int shots;
	bool allShotsAlocated;


	Robot1(vec3d pos,World *world)
	{

		rightPressed =  leftPressed = accellPressed =  reversePressed =
			breaking =  rotingRight =  rotingLeft =
			rotingUp = rotingDown = allShotsAlocated =false;
		gunRot = bodyRot = 0.1;
		Cd = 0.50;
		S = 4.0;
		rho = 1.29;
		aceleador = 0;
		shots = 0;
		chassi = new Cube();
		chassi->iSize.x = 4.5;
		chassi->iSize.y = 3.5;
		chassi->iSize.z = 1.0;
		chassi->iM = 0.4;
		chassi->data->setName("Chassi");
		chassi->MakeGeom(world->topLevelSpace);
		chassi->MakeBody(world->world);
		chassi->LinkBodyWithGeom();

		chassi->setPosition(pos.x,pos.y,pos.z);
		chassi->setRotation(0,0,0);




		canonBody = new Sphere(1.0,128,128);
		canonBody->iM = 0.1;
		canonBody->data->setName("CanonBody");
		canonBody->MakeGeom(world->topLevelSpace);
		canonBody->MakeBody(world->world);
		canonBody->LinkBodyWithGeom();
		canonBody->setPosition(pos.x,pos.y,pos.z+1);
		canonBody->setRotation(0,0,90);

		canonGun = new Cylinder(0.2,3.0,24,24);
		canonGun->iM = 0.1;
		canonBody->data->setName("GunBody");
		canonGun->MakeGeom(world->topLevelSpace);
		canonGun->MakeBody(world->world);
		canonGun->LinkBodyWithGeom();
		canonGun->setPosition(pos.x,pos.y-0.5,pos.z+1.0);
		//canonGun->setRotation(0,0,0);




		vec3d p;
		p.x = pos.x+2;
		p.y = pos.y+1.5;
		p.z = pos.z-0.5;


		rodaFrontalEsquerda = new Cylinder(0.6,0.6,24,24);
		rodaFrontalEsquerda->iM = 0.2;
		rodaFrontalEsquerda->MakeGeom(world->topLevelSpace);
		rodaFrontalEsquerda->MakeBody(world->world);
		rodaFrontalEsquerda->LinkBodyWithGeom();
		rodaFrontalEsquerda->setPosition(pos.x+chassi->iSize.x/2,pos.y+chassi->iSize.y/2,pos.z-chassi->iSize.z/2);


		rodaFrontalDireita = new Cylinder(0.6,0.6,24,24);
		rodaFrontalDireita->iM = 0.2;
		rodaFrontalDireita->MakeGeom(world->topLevelSpace);
		rodaFrontalDireita->MakeBody(world->world);
		rodaFrontalDireita->LinkBodyWithGeom();
		rodaFrontalDireita->setPosition(pos.x+chassi->iSize.x/2,pos.y-chassi->iSize.y/2,pos.z-chassi->iSize.z/2);


		rodaTraseiraEsquerda = new Cylinder(0.6,0.6,24,24);
		rodaTraseiraEsquerda->iM = 0.2;
		rodaTraseiraEsquerda->MakeGeom(world->topLevelSpace);
		rodaTraseiraEsquerda->MakeBody(world->world);
		rodaTraseiraEsquerda->LinkBodyWithGeom();
		rodaTraseiraEsquerda->setPosition(pos.x-chassi->iSize.x/2,pos.y+chassi->iSize.y/2,pos.z-chassi->iSize.z/2);



		rodaTraseiraDireita = new Cylinder(0.6,0.6,24,24);
		rodaTraseiraDireita->iM = 0.2;
		rodaTraseiraDireita->MakeGeom(world->topLevelSpace);
		rodaTraseiraDireita->MakeBody(world->world);
		rodaTraseiraDireita->LinkBodyWithGeom();
		rodaTraseiraDireita->setPosition(pos.x-chassi->iSize.x/2,pos.y-chassi->iSize.y/2,pos.z-chassi->iSize.z/2);



		


		
		p.x = pos.x+2;
		p.y = pos.y+1.5;
		p.z = pos.z-0.5;


		rodaFrontalEsquerda = new Cylinder(0.6,0.6,24,24);
		rodaFrontalEsquerda->iM = 0.2;
		rodaFrontalEsquerda->MakeGeom(world->topLevelSpace);
		rodaFrontalEsquerda->MakeBody(world->world);
		rodaFrontalEsquerda->LinkBodyWithGeom();
		rodaFrontalEsquerda->setPosition(pos.x+chassi->iSize.x/2,pos.y+chassi->iSize.y/2,pos.z-chassi->iSize.z/2);


		rodaFrontalDireita = new Cylinder(0.6,0.6,24,24);
		rodaFrontalDireita->iM = 0.2;
		rodaFrontalDireita->MakeGeom(world->topLevelSpace);
		rodaFrontalDireita->MakeBody(world->world);
		rodaFrontalDireita->LinkBodyWithGeom();
		rodaFrontalDireita->setPosition(pos.x+chassi->iSize.x/2,pos.y-chassi->iSize.y/2,pos.z-chassi->iSize.z/2);


		rodaTraseiraEsquerda = new Cylinder(0.6,0.6,24,24);
		rodaTraseiraEsquerda->iM = 0.2;
		rodaTraseiraEsquerda->MakeGeom(world->topLevelSpace);
		rodaTraseiraEsquerda->MakeBody(world->world);
		rodaTraseiraEsquerda->LinkBodyWithGeom();
		rodaTraseiraEsquerda->setPosition(pos.x-chassi->iSize.x/2,pos.y+chassi->iSize.y/2,pos.z-chassi->iSize.z/2);



		rodaTraseiraDireita = new Cylinder(0.6,0.6,24,24);
		rodaTraseiraDireita->iM = 0.2;
		rodaTraseiraDireita->MakeGeom(world->topLevelSpace);
		rodaTraseiraDireita->MakeBody(world->world);
		rodaTraseiraDireita->LinkBodyWithGeom();
		rodaTraseiraDireita->setPosition(pos.x-chassi->iSize.x/2,pos.y-chassi->iSize.y/2,pos.z-chassi->iSize.z/2);

		vec3d servoBodyPos = {pos.x,pos.y,pos.z+1.0};
		vec3d servoGunPos  = {pos.x,pos.y-0.5,pos.z+1.0};
		vec3d rodaFLPos =  {pos.x+chassi->iSize.x/2,pos.y+chassi->iSize.y/2,pos.z-chassi->iSize.z/2};
		vec3d rodaFDPos = {pos.x+chassi->iSize.x/2,pos.y-chassi->iSize.y/2,pos.z-chassi->iSize.z/2};
		vec3d rodaBLPos = {pos.x-chassi->iSize.x/2,pos.y+chassi->iSize.y/2,pos.z-chassi->iSize.z/2};
		vec3d rodaBRPos = {pos.x-chassi->iSize.x/2,pos.y-chassi->iSize.y/2,pos.z-chassi->iSize.z/2};

		vec3d xAixis = {1,0,0};
		vec3d yAixis =  {0,1,0};
		vec3d zAixis =  {0,0,1};


		servoBody = new Servo(chassi,canonBody,servoBodyPos,zAixis,world->world);
		servoGun = new Servo(canonBody,canonGun,servoGunPos,xAixis,world->world);


		jointRodaFL = new CarWheel(chassi,rodaFrontalEsquerda,rodaFLPos,zAixis,yAixis,world);

		dJointSetHinge2Param (jointRodaFL->iJoint,dParamSuspensionERP,0.8);
		dJointSetHinge2Param (jointRodaFL->iJoint,dParamSuspensionCFM,0.5);


		jointRodaFR = new CarWheel(chassi,rodaFrontalDireita,rodaFDPos,zAixis,yAixis,world);

		dJointSetHinge2Param (jointRodaFR->iJoint,dParamSuspensionERP,0.8);
		dJointSetHinge2Param (jointRodaFR->iJoint,dParamSuspensionCFM,0.5);


		jointRodaBL = new CarWheel(chassi,rodaTraseiraEsquerda,rodaBLPos,zAixis,yAixis,world);

		dJointSetHinge2Param (jointRodaBL->iJoint,dParamSuspensionERP,0.8);
		dJointSetHinge2Param (jointRodaBL->iJoint,dParamSuspensionCFM,0.5);

		jointRodaBR = new CarWheel(chassi,rodaTraseiraDireita,rodaBRPos,zAixis,yAixis,world);

		dJointSetHinge2Param (jointRodaBR->iJoint,dParamSuspensionERP,0.8);
		dJointSetHinge2Param (jointRodaBR->iJoint,dParamSuspensionCFM,0.5);



		//        Object *chassi,Object *roda,vec3d anchor,vec3d {,vec3d aixs2,World *world


		setColor(rodaFrontalEsquerda->Mat->Ka,0.0,0.0,1.0);
		setColor(rodaFrontalEsquerda->Mat->Kd,0.0,0.0,1.0);
		setColor(rodaFrontalEsquerda->Mat->Ks,1.0,1.0,1.0);

		setColor(rodaFrontalDireita->Mat->Ka,0.0,0.0,1.0);
		setColor(rodaFrontalDireita->Mat->Kd,0.0,0.0,1.0);
		setColor(rodaFrontalDireita->Mat->Ks,1.0,1.0,1.0);

		setColor(rodaTraseiraEsquerda->Mat->Ka,1.0,1.0,1.0);
		setColor(rodaTraseiraEsquerda->Mat->Kd,0.0,0.0,1.0);
		setColor(rodaTraseiraEsquerda->Mat->Ks,1.0,1.0,1.0);

		setColor(rodaTraseiraDireita->Mat->Ka,1.0,1.0,1.0);
		setColor(rodaTraseiraDireita->Mat->Kd,0.0,0.0,1.0);
		setColor(rodaTraseiraDireita->Mat->Ks,1.0,1.0,1.0);



		//setColor(baseRodaFrontal->Mat->Ka,0.0,0.0,1.0);
		//setColor(baseRodaFrontal->Mat->Kd,0.0,0.0,1.0);
		//setColor(baseRodaFrontal->Mat->Ks,1.0,1.0,1.0);

		setColor(canonGun->Mat->Ka,1.0,1.0,1.0);
		setColor(canonGun->Mat->Kd,0.0,0.9,0.0);
		setColor(canonGun->Mat->Ks,1.0,1.0,1.0);



		setColor(canonBody->Mat->Ka,0.4,0.4,0.0);
		setColor(canonBody->Mat->Kd,0.4,0.4,0.0);
		setColor(canonBody->Mat->Ks,0.0,0.0,0.0);


		setColor(chassi->Mat->Ka,1.0,0.0,0.0);
		setColor(chassi->Mat->Kd,1.0,0.0,0.0);
		setColor(chassi->Mat->Ks,1.0,1.0,1.0);


		canonBals = new Sphere*[20];

		for (int i =0;i< 20;i++)
		{
			canonBals[i] = new Sphere(0.5,32,32);
			canonBals[i]->iM = 0.4;
			canonBody->data->setName("CanonBall");

			setColor(canonBals[i]->Mat->Ka,0.1,0.1,0.1);
			setColor(canonBals[i]->Mat->Kd,0.1,0.1,0.1);
			setColor(canonBals[i]->Mat->Ks,0.6,0.5,0.6);



		}

	};

	void shot()
	{
		shots++;

		if (shots >= 20)
		{
			shots = 1;
			allShotsAlocated = true;
		}


		if (allShotsAlocated == false)
		{


			canonBals[shots-1]->MakeGeom(dGeomGetSpace(chassi->iGeom));
			canonBals[shots-1]->MakeBody(dBodyGetWorld(chassi->iBody));
			canonBals[shots-1]->LinkBodyWithGeom();

		}
		else
		{



		}
		dMatrix3 R2,R3;
		const dReal *R4 =  dGeomGetRotation(canonGun->iGeom);

		//dMultiply0 (R4,R2,R3,3,3,3);
		const dReal *ccpos = dGeomGetPosition(canonGun->iGeom);
		dReal cpos[3] = {ccpos[0],ccpos[1],ccpos[2]};
		for (int i=0; i<3; i++) cpos[i] += 3*R4[i*4+2];
		dBodySetPosition (canonBals[shots-1]->iBody,cpos[0],cpos[1],cpos[2]);
		dReal force = 25;
		dBodySetLinearVel (canonBals[shots-1]->iBody,force*R4[2],force*R4[6],force*R4[10]);
		dBodyAddForce (canonBals[shots-1]->iBody,force*(-R4[2]),force*(-R4[6]),force*(-R4[10]));
		dBodySetAngularVel (canonBals[shots-1]->iBody,0,0,0);






	}


	void Update(float dt)
	{
		float u = 0;

		int j;
		if (accellPressed)
			u = 1;
		else if (reversePressed)
			u = -1;
		else u = 0;


		
		float turn = 0;


		if (rightPressed)
			turn = 0.3;
		else if(leftPressed)
			turn = -0.3;


		dJointID _joint[4] =
		{
			jointRodaFL->iJoint,
			jointRodaFR->iJoint,
			jointRodaBL->iJoint,
			jointRodaBR->iJoint
		};

		speed = 1.2;
		force = 76;
		
		for (j = 0; j < 4; j++)
		{
			dReal curturn = dJointGetHinge2Angle1 (_joint[j]);

			if (j > 1)
				dJointSetHinge2Param(_joint[j],dParamVel,(turn-curturn)*1.0);
			else
				dJointSetHinge2Param(_joint[j],dParamVel,(0-curturn)*1.0);

			dJointSetHinge2Param(_joint[j],dParamFMax,dInfinity);
			dJointSetHinge2Param(_joint[j],dParamVel2,speed > 0 ? u*speed : 0);
			dJointSetHinge2Param(_joint[j],dParamFMax2,force >0 ? force/4 : 0);
			dBodyEnable(dJointGetBody(_joint[j],0));
			dBodyEnable(dJointGetBody(_joint[j],1));

		}


		servoBody->setTorque(dInfinity);
		servoGun->setTorque(dInfinity);

		if (rotingRight == true)
		{
			dJointSetHingeParam(servoBody->iJoint,dParamVel,0.2);
		}
		else if (rotingLeft == true)
		{
			dJointSetHingeParam(servoBody->iJoint,dParamVel,-0.2);
		}
		else
		{
			dJointSetHingeParam(servoBody->iJoint,dParamVel,0.0);
		}

		if (rotingUp == true)
		{
			gunRot++;
			dJointSetHingeParam(servoGun->iJoint,dParamHiStop,DEG2RAD(gunRot));
			dJointSetHingeParam(servoGun->iJoint,dParamLoStop,DEG2RAD(gunRot));
			if (gunRot > 13)
				gunRot = 13;
		}

		if (rotingDown == true)
		{
			gunRot--;
			dJointSetHingeParam(servoGun->iJoint,dParamHiStop,DEG2RAD(gunRot));
			dJointSetHingeParam(servoGun->iJoint,dParamLoStop,DEG2RAD(gunRot));
			if (gunRot < -13)
				gunRot  = -13;

		}





		chassi->Update();
		rodaFrontalEsquerda->Update();
		rodaFrontalDireita->Update();
		rodaTraseiraEsquerda->Update();
		rodaTraseiraDireita->Update();
		canonBody->Update();
		canonGun->Update();
		for (int i = 0; i <shots;i++)
		{
			canonBals[i]->Update();
		}
	};

	void Draw()
	{
		chassi->Draw();

		rodaFrontalEsquerda->Draw();
		rodaFrontalDireita->Draw();
		rodaTraseiraEsquerda->Draw();
		rodaTraseiraDireita->Draw();
		canonBody->Draw();
		canonGun->Draw();
		for (int i = 0; i <shots;i++)
		{
			canonBals[i]->Draw();

		}
	};

};
#endif
