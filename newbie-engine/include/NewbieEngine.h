#ifndef __NEWBIE_ENGINE__
#define __NEWBIE_ENGINE__

/**
@brief Uma engine feita com OpenGL, SDL e ODE para jogos e
 pequenas simulações fisicas.
@author Gabriel da Silva Moreira
*/
#ifdef WIN32
#include <windows.h>
#endif

#include <windows.h>

#include <ode/ode.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"
#include "Matrix.h"
#include "Shader.h"
#include "BZK_Time.h"
#include "Cube.h"
#include "Cylinder.h"
#include "ObjectManager.h"
#include "Sphere.h"
#include "Wavefront.h"
#include "World.h"
#include "Graphics.h"
#include "ParticleSystem.h"
#include "Explosion.h"
#include "Camera.h"
#include "Texture.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "Joint.h"
#include "Buggy.h"
#include "Terrian.h"
#include "VertexBufferObject.h"
#include "Event.h"
#include "glsl.h"
#include "Audio.h"

static SDL_Surface *surface;

static World *currentWorld = NULL;
static dGeomID ground;
static GLfloat light_pos[4] = {0.0f,-30.0f,0.0f,0.0f};
//vec3d pos = {0.0f,-8.0f,-50.0f};
//vec3d rot = {-90.0f,0.0f,0.0f};
static float xyz[3] = {3.8548f,8.90843f,7.5900f};
static float hpr[3] = {-145.5,-22.5,-0.25};
static EventManager inputEvents;
static EventFn *kupFn = NULL;
static EventFn *kdwFn = NULL;
static cwc::glShaderManager ShaderManager;

static void nearCallback (void *data, dGeomID o1, dGeomID o2)
{
    int i,n;

    if (dGeomIsSpace(o1) || dGeomIsSpace(o2))
    {

        dSpaceCollide2(o1,o2,data,&nearCallback);
        return;
    }


    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    if (b1 && b2 && dAreConnected(b1, b2))
        return;


    const int N = 10;
    dContact contact[N];
    n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
    if (n > 0)
    {
        for (i=0; i<n; i++)
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



static void setKeyUpFunction(EventFn *fn)
{
    kupFn = fn;
}

static void setKeyDownFunction(EventFn *fn)
{
    kdwFn =fn;
}

static void handle_key_down( SDL_keysym* keysym )
{
    KeyBoardEvent kdw;
    kdw.subType = KeyDown;
    kdw.setKey(keysym->sym);
    kdw.fn = kdwFn;
    inputEvents.addKeyBoadEvent(kdw);

}

static void handle_key_up( SDL_keysym* keysym )
{
    KeyBoardEvent kup;
    kup.subType = KeyUp;
    kup.setKey(keysym->sym);
    kup.fn = kupFn;
    inputEvents.addKeyBoadEvent(kup);

}


static void process_events( void )
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) )
    {

        switch( event.type )
        {
        case SDL_KEYUP:

           handle_key_down(&event.key.keysym);
            break;

        case SDL_KEYDOWN:
            handle_key_up(&event.key.keysym);
            break;

        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
            //TODO os angulos devem ser convertidos de radianos p/ graus
//            if (event.motion.state == 1 )
//            {
//                if (event.motion.xrel > 0)
//                    eye->Turn(event.motion.xrel,0);
//
//                if (event.motion.xrel < 0 )
//                    eye->Turn(event.motion.xrel,0);
//            }
//
//            if (event.motion.state == SDL_BUTTON(3))
//            {
//                eye->UpDown(event.motion.xrel,event.motion.yrel);
//            }

        default:
            break;
        }


        inputEvents.processEvents();

    }


};


void drawGround();

void setCamera (float x,float y,float z, float h, float p, float r);
void drawString(const char *str,int x,int y,vec4d color, void *font);
void setup_opengl( int width, int height );
int Iniciar();



#endif
