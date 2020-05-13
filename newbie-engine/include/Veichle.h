#ifndef __VEICHLE__
#define __VEICHLE__
#ifdef WIN32
#include <windows.h>
#endif
#include <ode/ode.h>
#include "vec3d.h"
#include "Matrix.h"

#define s_pi (3.141592654f)			// pi


typedef struct engineProperties
{
	float torque;					// engine torque
	float rpm;						// engine rpm (revolutions per minute)
};

struct vehicleProperties
{
	char* name;						// name of the vehicle
	char* bodyObj;					// path of the body object
	char* tyreObj;					// path of the tyre object
	char* bodyTex;					// path of the body texture
	char* tyreTex;					// path of the tyre texture
	char* engineSnd;				// path of the engine sound
	char* hornSnd;					// path of the horn sound
	char* brakeSnd;					// path of the brake sound

	float mass;						// vehicle mass
	float wheelMass;				// vehicle wheel mass
	float drag;						// coefficient of frition
	float frontArea;				// frontal area
	float bodyLength;				// length of vehicle body
	float bodyWidth;				// width of vehicle body
	float bodyHeight;				// height of vehicle body
	float wheelRadius;				// radius of the vehicle wheel
	float groundHeight;				// height between vehicle and ground
	float springLength;				// original length of the suspension spring
	float springConst;				// suspension spring constant
	float brakeTorque;				// torque applied to lock wheels
	float gearRatio[7];				// stores the gear 1 to 6 ratios (0 is reverse)
	float diffRatio;				// stores the differential ratio
	float transEff;					// stores the transmission efficiency

	vec3d cog;				// vehicle centre of gravity (z axis offset)
	vec3d fl;					// default position of front left wheel
	vec3d fr;					// default position of front right wheel
	vec3d bl;					// default position of back left wheel
	vec3d br;					// default position of back right wheel
	vec3d bScl;				// scale factors for the vehicle body
	vec3d wScl;				// scale factors for the vehicle tyre

	engineProperties engine[6];		// rpm/torque lookup curve container
};

class Veichle
{
 public:

    Matrix *chassiRotationMatrix;


   dGeomID geom[5];
   dBodyID chassi;
   dBodyID wheel[4];
   dJointID joints[4];
   dJointFeedback feedBack[4];

   Veichle(){};
   Veichle(dSpaceID space, dWorldID world){};
   Matrix* getRotation();
   vec3d getPosition();
};

#endif
