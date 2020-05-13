#include "baselib.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Joint.h"

class RobotCleaner
{
public:

	Cylinder* chassi;



	Cylinder* rodaFrontalEsquerda;
	Cylinder* rodaFrontalDireita;

	Cylinder* rodaCentral;


	CarWheel* rodaEsquerda;
	CarWheel* RodaDireita;
	CarWheel* jointRodaBL;

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

	float getFrr() { return Frr; };
	float getSpeed() { return speed; };
	float getTorque() { return torque; };
	float getFdrag() { return Fdrag; };
	float getForce() { return force; };
	float bodyRot;
	float gunRot;
	int shots;
	bool allShotsAlocated;


	RobotCleaner(vec3d pos, World* world)
	{
		rightPressed = leftPressed = accellPressed = reversePressed =
			breaking = rotingRight = rotingLeft =
			rotingUp = rotingDown = allShotsAlocated = false;
		gunRot = bodyRot = 0.1;
		Cd = 0.50;
		S = 4.0;
		rho = 1.29;
		aceleador = 0;
		shots = 0;
		chassi = new Cylinder(3.8, 1.5, 64, 64);
		chassi->iSize.x = 4.5;
		chassi->iSize.y = 3.5;
		chassi->iSize.z = 1.0;
		chassi->iM = 0.4;
		chassi->data->setName("Chassi");
		chassi->MakeGeom(world->topLevelSpace);
		chassi->MakeBody(world->world);
		chassi->LinkBodyWithGeom();

		chassi->setPosition(pos.x, pos.y, pos.z);
		chassi->setRotation(0, 0, 0);

		vec3d p;
		p.x = pos.x + 2;
		p.y = pos.y + 1.5;
		p.z = pos.z - 0.5;


		rodaFrontalEsquerda = new Cylinder(0.6, 0.6, 24, 24);
		rodaFrontalEsquerda->iM = 0.2;
		rodaFrontalEsquerda->MakeGeom(world->topLevelSpace);
		rodaFrontalEsquerda->MakeBody(world->world);
		rodaFrontalEsquerda->LinkBodyWithGeom();
		rodaFrontalEsquerda->setPosition(pos.x + chassi->iSize.x / 2, pos.y + chassi->iSize.y / 2, pos.z - chassi->iSize.z / 2);


		rodaFrontalDireita = new Cylinder(0.6, 0.6, 24, 24);
		rodaFrontalDireita->iM = 0.2;
		rodaFrontalDireita->MakeGeom(world->topLevelSpace);
		rodaFrontalDireita->MakeBody(world->world);
		rodaFrontalDireita->LinkBodyWithGeom();
		rodaFrontalDireita->setPosition(pos.x + chassi->iSize.x / 2, pos.y - chassi->iSize.y / 2, pos.z - chassi->iSize.z / 2);


		rodaCentral = new Cylinder(0.6, 0.6, 24, 24);
		rodaCentral->iM = 0.2;
		rodaCentral->MakeGeom(world->topLevelSpace);
		rodaCentral->MakeBody(world->world);
		rodaCentral->LinkBodyWithGeom();
		rodaCentral->setPosition(pos.x - chassi->iSize.x / 2, pos.y, pos.z - chassi->iSize.z / 2);


		p.x = pos.x + 2;
		p.y = pos.y + 1.5;
		p.z = pos.z - 0.5;


		vec3d servoBodyPos = { pos.x,pos.y,pos.z + 1.0 };
		vec3d servoGunPos = { pos.x,pos.y - 0.5,pos.z + 1.0 };
		vec3d rodaEsquerdaPos = { pos.x + chassi->iSize.x / 2,pos.y + chassi->iSize.y / 2,pos.z - chassi->iSize.z / 2 };
		vec3d rodaDireitaPos = { pos.x + chassi->iSize.x / 2,pos.y - chassi->iSize.y / 2,pos.z - chassi->iSize.z / 2 };
		vec3d rodaCentralPos = { pos.x - chassi->iSize.x / 2,pos.y,pos.z - chassi->iSize.z / 2 };


		vec3d xAixis = { 1,0,0 };
		vec3d yAixis = { 0,1,0 };
		vec3d zAixis = { 0,0,1 };


		rodaEsquerda = new CarWheel(chassi, rodaFrontalEsquerda, rodaEsquerdaPos, zAixis, yAixis, world);

		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamSuspensionERP, 0.8);
		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamSuspensionCFM, 0.5);


		RodaDireita = new CarWheel(chassi, rodaFrontalDireita, rodaDireitaPos, zAixis, yAixis, world);

		dJointSetHinge2Param(RodaDireita->iJoint, dParamSuspensionERP, 0.8);
		dJointSetHinge2Param(RodaDireita->iJoint, dParamSuspensionCFM, 0.5);


		jointRodaBL = new CarWheel(chassi, rodaCentral, rodaCentralPos, zAixis, yAixis, world);

		dJointSetHinge2Param(jointRodaBL->iJoint, dParamSuspensionERP, 0.8);
		dJointSetHinge2Param(jointRodaBL->iJoint, dParamSuspensionCFM, 0.5);





		//        Object *chassi,Object *roda,vec3d anchor,vec3d {,vec3d aixs2,World *world


		setColor(rodaFrontalEsquerda->Mat->Ka, 0.0, 0.0, 1.0);
		setColor(rodaFrontalEsquerda->Mat->Kd, 0.0, 0.0, 1.0);
		setColor(rodaFrontalEsquerda->Mat->Ks, 1.0, 1.0, 1.0);

		setColor(rodaFrontalDireita->Mat->Ka, 0.0, 0.0, 1.0);
		setColor(rodaFrontalDireita->Mat->Kd, 0.0, 0.0, 1.0);
		setColor(rodaFrontalDireita->Mat->Ks, 1.0, 1.0, 1.0);

		setColor(rodaCentral->Mat->Ka, 0.0, 0.0, 1.0);
		setColor(rodaCentral->Mat->Kd, 0.0, 0.0, 1.0);
		setColor(rodaCentral->Mat->Ks, 1.0, 1.0, 1.0);



		setColor(chassi->Mat->Ka, 1.0, 0.0, 0.0);
		setColor(chassi->Mat->Kd, 1.0, 0.0, 0.0);
		setColor(chassi->Mat->Ks, 1.0, 1.0, 1.0);

	};

	void shot()
	{


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
		else if (leftPressed)
			turn = -0.3;

		speed = 1.2;
		force = 2;

		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamVel, 0);
		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamFMax, 0);
		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamLoStop, 0);
		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamHiStop, 0);
		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamVel2, speed);
		dJointSetHinge2Param(rodaEsquerda->iJoint, dParamFMax2, force);

		dJointSetHinge2Param(RodaDireita->iJoint, dParamVel, 0);
		dJointSetHinge2Param(RodaDireita->iJoint, dParamFMax, 0);
		dJointSetHinge2Param(RodaDireita->iJoint, dParamVel2, speed);
		dJointSetHinge2Param(RodaDireita->iJoint, dParamFMax2, force);
		dJointSetHinge2Param(RodaDireita->iJoint, dParamLoStop, 0);
		dJointSetHinge2Param(RodaDireita->iJoint, dParamHiStop, 0);


		chassi->Update();
		rodaFrontalEsquerda->Update();
		rodaFrontalDireita->Update();
		rodaCentral->Update();

	};

	void Draw()
	{
		chassi->Draw();

		rodaFrontalEsquerda->Draw();
		rodaFrontalDireita->Draw();
		rodaCentral->Draw();


	};

};
