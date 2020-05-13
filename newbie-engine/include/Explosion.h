/*
 * Explosion.h
 *
 *  Created on: 10/04/2009
 *      Author: newbie
 */

#ifndef EXPLOSION_H_
#define EXPLOSION_H_
# ifdef WIN32
#  include <windows.h>
# endif
#include <ParticleSystem.h>

class Explosion : ParticleSystem{
public:
	int maxEnergy;
	int speedy;
	Explosion(vec3d c, vec3d grav, int number, int mEnergy, int spd);
	virtual void update();
	virtual void draw();
	virtual void CreateSystem();
	virtual ~Explosion();
};

#endif /* EXPLOSION_H_ */
