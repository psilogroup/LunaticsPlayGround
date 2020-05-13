#ifndef __NEWBIE_ENGINE__
#define __NEWBIE_ENGINE__

/**
@brief Uma engine feita com OpenGL, SDL e ODE para jogos e
 pequenas simulações fisicas.
@author Gabriel da Silva Moreira
*/

#include "baselib.h"
#include "vec4.h"
#include "Terrian.h"
#include "World.h"
#include "Event.h"
#include "Singleton.h"

//static SDL_Surface *surface;


static dGeomID ground;
static World* currentWorld = NULL;
static GLfloat light_pos[4] = { 1000.0f,1.0f,10000.0f,0.0f };
static float xyz[3] = { 3.8548f,8.90843f,7.5900f };
static float hpr[3] = { -145.5,-22.5,-0.25 };
static EventFn* kupFn = NULL;
static EventFn* kdwFn = NULL;
static EventManager inputEvents;

static void nearCallback(void* data, dGeomID o1, dGeomID o2)
{
	int i, n;

	if (dGeomIsSpace(o1) || dGeomIsSpace(o2))
	{

		dSpaceCollide2(o1, o2, data, &nearCallback);
		return;
	}


	dBodyID b1 = dGeomGetBody(o1);
	dBodyID b2 = dGeomGetBody(o2);
	if (b1 && b2 && dAreConnected(b1, b2))
		return;


	const int N = 10;
	dContact contact[N];
	n = dCollide(o1, o2, N, &contact[0].geom, sizeof(dContact));
	if (n > 0)
	{
		for (i = 0; i < n; i++)
		{


			contact[i].surface.mode = dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;
			if (dGeomGetClass(o1) == dCylinderClass || dGeomGetClass(o2) == dCylinderClass)
				contact[i].surface.mu = 20;
			else
				contact[i].surface.mu = 0.5;
			contact[i].surface.slip1 = 0.01;
			contact[i].surface.slip2 = 0.1;
			contact[i].surface.soft_erp = 0.8;
			contact[i].surface.soft_cfm = 0.01;
			dJointID c = dJointCreateContact(currentWorld->world, currentWorld->contactGroup, contact + i);
			dJointAttach(c, dGeomGetBody(o1), dGeomGetBody(o2));
		}
	}

};



static void setKeyUpFunction(EventFn* fn)
{
	kupFn = fn;
}

static void setKeyDownFunction(EventFn* fn)
{
	kdwFn = fn;
}







void drawGround();

void setCamera(float x, float y, float z, float h, float p, float r);
void drawString(const char* str, int x, int y, vec4d color, void* font);
void setup_opengl(int width, int height);
int Iniciar();



#endif
