#ifndef __PARTICLE_SYSTEM__
#define __PARTICLE_SYSTEM__
#ifdef WIN32
#include <windows.h>
#endif
//#include <GL/glew.h>


#include "vec3d.h"
#include "vec4.h"

typedef struct
{
 vec3d position;
 vec3d velocity;
 int energy;
 bool dead;
 vec4d color;
} Particle;

class ParticleSystem
{
 public:
        int NumParticles;
        int ParticlesDead;
        Particle *Particles;
        vec3d center;
        vec3d gravity;
        bool systemDead;
        virtual void update(){};
        virtual void draw(){};
        ParticleSystem();
        ParticleSystem(vec3d center,vec3d grav,int number);
        virtual void CreateSystem(){};
        virtual ~ParticleSystem(){};
};
#endif
