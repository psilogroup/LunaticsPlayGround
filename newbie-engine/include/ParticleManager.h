/*
 * ParticleManager.h
 *
 *  Created on: 10/04/2009
 *      Author: newbie
 */

#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#ifdef WIN32
#include <windows.h>
#endif

#include "BZK_List.h"
#include "ParticleSystem.h"

class ParticleManager {
public:
	ParticleManager();
	BZK_List<ParticleSystem*> iSystems;
	virtual void update();
	virtual void draw();
	void add(ParticleManager *system);
	void erase();
	virtual ~ParticleManager();
};

#endif /* PARTICLEMANAGER_H_ */
