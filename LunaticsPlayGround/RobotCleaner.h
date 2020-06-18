#include "baselib.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Joint.h"

class RobotCleaner
{
public:

	Cube* chassi;
	Mesh* bodyMesh;
	Mesh* wheelMesh;
	Cylinder* rodaFrontalEsquerda;
	Cylinder* rodaFrontalDireita;

	Cylinder* rodaTraseiraEsquerda;
	Cylinder* rodaTraseiraDireita;

	CarWheel* jointRodaFL;
	CarWheel* jointRodaFR;
	CarWheel* jointRodaBL;
	CarWheel* jointRodaBR;
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

	vec3d getPosition()
	{
		const dReal* pos = dBodyGetPosition(chassi->iBody);
		return vec3d{ pos[0],pos[1],pos[2] };
	};

	
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
		chassi = new Cube();
		chassi->iSize.x = 4.0f;
		chassi->iSize.y = 1.8;
		chassi->iSize.z = 1.2;
		chassi->iM = 0.4;
		chassi->data->setName("Chassi");
		chassi->MakeGeom(world->topLevelSpace);
		chassi->MakeBody(world->world);
		chassi->LinkBodyWithGeom();

		chassi->setPosition(pos.x, pos.y, pos.z);
		chassi->setRotation(0, 0, 0);

		bodyMesh = new Mesh("storage\\models\\car.obj");
		bodyMesh->texture = new Texture("storage\\textures\\CarTexture.png");

		vec3d p;
		p.x = pos.x + 2;
		p.y = pos.y + 1.5;
		p.z = pos.z - 0.5;


		rodaFrontalEsquerda = new Cylinder(0.6, 0.4, 24, 24);
		rodaFrontalEsquerda->iM = 0.2;
		rodaFrontalEsquerda->MakeGeom(world->topLevelSpace);
		rodaFrontalEsquerda->MakeBody(world->world);
		rodaFrontalEsquerda->LinkBodyWithGeom();
		rodaFrontalEsquerda->setPosition(pos.x + chassi->iSize.x / 2, pos.y + chassi->iSize.y / 2, pos.z - chassi->iSize.z / 2);


		rodaFrontalDireita = new Cylinder(0.6, 0.4, 24, 24);
		rodaFrontalDireita->iM = 0.2;
		rodaFrontalDireita->MakeGeom(world->topLevelSpace);
		rodaFrontalDireita->MakeBody(world->world);
		rodaFrontalDireita->LinkBodyWithGeom();
		rodaFrontalDireita->setPosition(pos.x + chassi->iSize.x / 2, pos.y - chassi->iSize.y / 2, pos.z - chassi->iSize.z / 2);


		rodaTraseiraEsquerda = new Cylinder(0.6, 0.4, 24, 24);
		rodaTraseiraEsquerda->iM = 0.2;
		rodaTraseiraEsquerda->MakeGeom(world->topLevelSpace);
		rodaTraseiraEsquerda->MakeBody(world->world);
		rodaTraseiraEsquerda->LinkBodyWithGeom();
		rodaTraseiraEsquerda->setPosition(pos.x - chassi->iSize.x / 2, pos.y + chassi->iSize.y / 2, pos.z - chassi->iSize.z / 2);



		rodaTraseiraDireita = new Cylinder(0.6, 0.4, 24, 24);
		rodaTraseiraDireita->iM = 0.2;
		rodaTraseiraDireita->MakeGeom(world->topLevelSpace);
		rodaTraseiraDireita->MakeBody(world->world);
		rodaTraseiraDireita->LinkBodyWithGeom();
		rodaTraseiraDireita->setPosition(pos.x - chassi->iSize.x / 2, pos.y - chassi->iSize.y / 2, pos.z - chassi->iSize.z / 2);


		p.x = pos.x + 2;
		p.y = pos.y + 1.5;
		p.z = pos.z - 0.5;


		vec3d servoBodyPos = { pos.x,pos.y,pos.z + 1.0 };
		vec3d servoGunPos = { pos.x,pos.y - 0.5,pos.z + 1.0 };
		vec3d rodaFLPos = { pos.x + chassi->iSize.x / 2,pos.y + chassi->iSize.y / 2,pos.z - chassi->iSize.z / 2 };
		vec3d rodaFDPos = { pos.x + chassi->iSize.x / 2,pos.y - chassi->iSize.y / 2,pos.z - chassi->iSize.z / 2 };
		vec3d rodaBLPos = { pos.x - chassi->iSize.x / 2,pos.y + chassi->iSize.y / 2,pos.z - chassi->iSize.z / 2 };
		vec3d rodaBRPos = { pos.x - chassi->iSize.x / 2,pos.y - chassi->iSize.y / 2,pos.z - chassi->iSize.z / 2 };

		vec3d xAixis = { 1,0,0 };
		vec3d yAixis = { 0,1,0 };
		vec3d zAixis = { 0,0,1 };


		jointRodaFL = new CarWheel(chassi, rodaFrontalEsquerda, rodaFLPos, zAixis, yAixis, world);

		dJointSetHinge2Param(jointRodaFL->iJoint, dParamSuspensionERP, 0.8);
		dJointSetHinge2Param(jointRodaFL->iJoint, dParamSuspensionCFM, 0.5);


		jointRodaFR = new CarWheel(chassi, rodaFrontalDireita, rodaFDPos, zAixis, yAixis, world);

		dJointSetHinge2Param(jointRodaFR->iJoint, dParamSuspensionERP, 0.8);
		dJointSetHinge2Param(jointRodaFR->iJoint, dParamSuspensionCFM, 0.5);


		jointRodaBL = new CarWheel(chassi, rodaTraseiraEsquerda, rodaBLPos, zAixis, yAixis, world);

		dJointSetHinge2Param(jointRodaBL->iJoint, dParamSuspensionERP, 0.8);
		dJointSetHinge2Param(jointRodaBL->iJoint, dParamSuspensionCFM, 0.5);

		jointRodaBR = new CarWheel(chassi, rodaTraseiraDireita, rodaBRPos, zAixis, yAixis, world);

		dJointSetHinge2Param(jointRodaBR->iJoint, dParamSuspensionERP, 0.8);
		dJointSetHinge2Param(jointRodaBR->iJoint, dParamSuspensionCFM, 0.5);



		//        Object *chassi,Object *roda,vec3d anchor,vec3d {,vec3d aixs2,World *world


		setColor(rodaFrontalEsquerda->Mat->Ka, 0.0, 0.0, 1.0);
		setColor(rodaFrontalEsquerda->Mat->Kd, 0.0, 0.0, 1.0);
		setColor(rodaFrontalEsquerda->Mat->Ks, 1.0, 1.0, 1.0);

		setColor(rodaFrontalDireita->Mat->Ka, 0.0, 0.0, 1.0);
		setColor(rodaFrontalDireita->Mat->Kd, 0.0, 0.0, 1.0);
		setColor(rodaFrontalDireita->Mat->Ks, 1.0, 1.0, 1.0);

		setColor(rodaTraseiraEsquerda->Mat->Ka, 0.0, 0.0, 1.0);
		setColor(rodaTraseiraEsquerda->Mat->Kd, 0.0, 0.0, 1.0);
		setColor(rodaTraseiraEsquerda->Mat->Ks, 1.0, 1.0, 1.0);

		setColor(rodaTraseiraDireita->Mat->Ka, 0.0, 0.0, 1.0);
		setColor(rodaTraseiraDireita->Mat->Kd, 0.0, 0.0, 1.0);
		setColor(rodaTraseiraDireita->Mat->Ks, 1.0, 1.0, 1.0);

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
			turn = 0.6;
		else if (leftPressed)
			turn = -0.6;


		dJointID _joint[4] =
		{
			jointRodaFL->iJoint,
			jointRodaFR->iJoint,
			jointRodaBL->iJoint,
			jointRodaBR->iJoint
		};

		speed = 3;
		force = 10;

		for (j = 0; j < 4; j++)
		{
			dReal curturn = dJointGetHinge2Angle1(_joint[j]);

			if (j > 1)
				dJointSetHinge2Param(_joint[j], dParamVel, (turn - curturn) * 1.0);
			else
				dJointSetHinge2Param(_joint[j], dParamVel, (0 - curturn) * 1.0);

			dJointSetHinge2Param(_joint[j], dParamFMax, dInfinity);
			dJointSetHinge2Param(_joint[j], dParamVel2, speed > 0 ? u * speed : 0);
			dJointSetHinge2Param(_joint[j], dParamFMax2, force > 0 ? force / 4 : 0);
			dBodyEnable(dJointGetBody(_joint[j], 0));
			dBodyEnable(dJointGetBody(_joint[j], 1));

		}

		chassi->Update();
		rodaFrontalEsquerda->Update();
		rodaFrontalDireita->Update();
		rodaTraseiraEsquerda->Update();
		rodaTraseiraDireita->Update();
	};

	void Draw(Shader *shader)
	{
		//chassi->Draw(shader);

		const float* pos = dGeomGetPosition(this->chassi->iGeom);
		const float* R = dGeomGetRotation(this->chassi->iGeom);

		glm::mat4 m1 = glm::mat4(1.0f);

		float* matrix = glm::value_ptr(m1);
		matrix[0] = R[0];
		matrix[1] = R[4];
		matrix[2] = R[8];
		matrix[3] = 0;
		matrix[4] = R[1];
		matrix[5] = R[5];
		matrix[6] = R[9];
		matrix[7] = 0;
		matrix[8] = R[2];
		matrix[9] = R[6];
		matrix[10] = R[10];
		matrix[11] = 0;
		matrix[12] = pos[0];
		matrix[13] = pos[1];
		matrix[14] = pos[2];
		matrix[15] = 1;

		glm::mat4 model = glm::scale(m1, glm::vec3{ 1.0f,1.0f,1.0f });

		
		shader->SetMat4("u_model", glm::value_ptr(model));

		bodyMesh->Draw();
		//rodaFrontalEsquerda->Draw();
		//rodaFrontalDireita->Draw();
		//rodaTraseiraEsquerda->Draw();
		//rodaTraseiraDireita->Draw();
	};

};
