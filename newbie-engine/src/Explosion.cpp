/*
 * Explosion.cpp
 *
 *  Created on: 10/04/2009
 *      Author: newbie
 */

#include "Explosion.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Graphics.h"

#ifndef M_PI
#define M_PI 3.141592654
#endif

Explosion::Explosion(vec3d c, vec3d grav, int number, int mEnergy, int spd) {
center.x = c.x;
center.y = c.y;
center.z = c.z;
ParticlesDead = 0;
systemDead = false;
gravity.x = grav.x;
gravity.y = grav.y;
gravity.z = grav.z;

NumParticles = number;
maxEnergy = mEnergy;
speedy = spd;

CreateSystem();

}

/* Atualiza o sistema de particulas
 * operações de atualização da posição
 * das particulas
 */
void Explosion::update() {

	register int i;

	for (i = 0; i < NumParticles; i++) {
		if (Particles[i].energy > 0) {
			Particles[i].energy--;

			if (Particles[i].energy <= 0) {
				ParticlesDead--;
			}

			Particles[i].position.x += Particles[i].velocity.x - gravity.x;
			Particles[i].position.y += Particles[i].velocity.y - gravity.y;
			Particles[i].position.z += Particles[i].velocity.z - gravity.z;

		} else {

			Particles[i].dead = true;
			Particles[i].position.y -= 0.2f;
		}

	}
}
/*
 * Desenha o sistema de particulas
 */

void Explosion::draw() {
	vec3d a, b, c;
	int i;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(center.x, center.y, center.z);

	for (i = 0; i < NumParticles; i++) {

		glColor4f(Particles[i].color.x, Particles[i].color.y,
				Particles[i].color.z, Particles[i].color.w);

		glBegin(GL_POINTS);
		glVertex3f(Particles[i].position.x, Particles[i].position.y,
				Particles[i].position.z);
		glEnd();

	}
	glPopMatrix();
}

/**
 * Cria uma nova instancia do sistema de particulas
 * @param c centro do sistema de particulas
 *
 **/

/**
 * Inicia o sistema de particulas
 */
void Explosion::CreateSystem() {
	float angleX, angleY, angleZ;
	float sx, sy, sz;
	float cx, cy, cz;

	int i;
	Particles = (Particle*) malloc(sizeof(Particle) * NumParticles);
	if (Particles == NULL)
		return;

	for (i = 0; i < NumParticles; i++) {
		Particles[i].position.x = Particles[i].position.y
				= Particles[i].position.z = 0.0f;
		//     initalizeParticle(&Particles[i]);

		angleX = (float) (1 + (rand() % 360)) * (180 / M_PI);
		angleY = (float) (1 + (rand() % 360)) * (180 / M_PI);
		angleZ = (float) (1 + (rand() % 360)) * (180 / M_PI);

		sx = sinf(angleX);
		sy = sinf(angleY);
		sz = sinf(angleZ);

		cx = cosf(angleX);
		cy = cosf(angleY);
		cz = cosf(angleZ);


		Particles[i].velocity.x = -cy * cz * sy;
		Particles[i].velocity.y = -sz * cx * cz * sx;
		Particles[i].velocity.z = -sx * cx - sy * cy;
		Particles[i].energy = (rand() % maxEnergy + maxEnergy);

	}

}

Explosion::~Explosion() {
	free(Particles);
}
