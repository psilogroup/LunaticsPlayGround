#ifdef WIN32
#include <windows.h>
#endif

#include <NewbieEngine.h>
#include "R1D1.h"
#include <stdio.h>
#include <stdlib.h>

cwc::glShader *PPLshader;
cwc::glShaderManager SM;



void onKeyUp(void *k);
void onKeyDown(void *k);


Camera *eye = NULL;
Terrain* terreno = NULL;



Mesh *ms;

void *font = GLUT_BITMAP_8_BY_13;

long fps = 0;
float dt = 0;


Robot1 *R1D1 = NULL; //Nosso Robo
static Uint32 next_time;
static Uint32 elapsedTime = 1;

void sair(int code) {
	SDL_Quit();
	//dWorldDestroy(world);
	/* Exit program. */
	exit(code);
};

void posicionaCamera() {

	// setCamera(eye->position.x,eye->position.y,eye->position.z,
	//        eye->rotation.x,eye->rotation.y,eye->rotation.z);


	if (R1D1 != NULL) {


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glScalef(0.5f,0.5f,0.5f);
		//Camera acompanhando o robo
		const dReal *pos = dBodyGetPosition(R1D1->chassi->iBody);
		const dReal *rot = dBodyGetRotation(R1D1->chassi->iBody);
		gluLookAt(
			pos[0] + 13 - rot[0] + rot[2],
			pos[1] - rot[4] + rot[6],
			pos[2] + 1.5 - rot[8] + rot[10],
			pos[0] + rot[0],
			pos[1] + rot[4],
			pos[2] + rot[8],
			rot[2], rot[6], rot[10]
		);
	}
}

char strBuff[255];

void drawMenssagens() {
	vec4d color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	float velocidade = (R1D1->getSpeed() * 15) -7;
	//sprintf_s((char*) strBuff, "Velocidade: %d R4/h\0",(int)velocidade );
	drawString(strBuff, 0, 470, color, font);
	/*
	sprintf((char*) strBuff, "Torque:%f\0", R1D1->getTorque());
	drawString(strBuff, 0, 460, color, font);

	sprintf((char*) strBuff, "Time:%d\0", elapsedTime);
	drawString(strBuff, 0, 450, color, font);

	sprintf((char*) strBuff, "Frr:%f\0", R1D1->getFrr());
	drawString(strBuff, 0, 440, color, font);
	*/
}

static void draw_screen(void) {

	int i;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	posicionaCamera();



	glColor3f(0.0,1.0,0.0);

	if (PPLshader != 0)
		PPLshader->begin();
	terreno->Draw();
	R1D1->Draw();

	glColor3f(1.0, 0.0, 0.0);

	//Desenha objetos carregados do XML
	currentWorld->Draw();
	if (PPLshader != 0)
		PPLshader->end();


	/*    
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	glColor4f(0.0, 0.0, 0.8, 0.5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-1.6, 0.6, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, -2.0);
	glVertex3f(1.0, 0.0, -2.0);
	glVertex3f(1.0, 1.0, -2.0);
	glVertex3f(0.0, 1.0, -2.0);
	glVertex3f(0.0, 0.0, -2.0);
	glEnd();

	glPopMatrix();

	glDisable(GL_BLEND);
	*/  

	drawMenssagens();
	SDL_GL_SwapBuffers();
}

#define TICK_INTERVAL    30

Uint32 time_left(void) {
	Uint32 now;

	now = SDL_GetTicks();
	elapsedTime = next_time - now;
	if (next_time <= now)
		return 0;
	else
		return next_time - now;
}

int main(int argc, char* argv[]) {

	if (!Iniciar()) {
		printf("Erro ao iniciar\n");
		exit(1);

	}

	currentWorld = new World("storage\\rampas.xml");


	int i = 0;
	int j = 0;
	terreno = new Terrain(256, 256, 5);

	//terreno->MakeGeom(currentWorld->topLevelSpace);
	ground = dCreatePlane(currentWorld->topLevelSpace, 0, 0, 1, 0);


	vec3d R1Pos;
	R1Pos.x = 60;
	R1Pos.y = 0;
	R1Pos.z = 1;

	 PPLshader = SM.loadfromFile("storage\\shaders\\PerPixelLight\\vertexshader.txt","storage\\shaders\\PerPixelLight\\fragmentshader.txt");
    if (PPLshader == 0)
        printf("Shader não foi compilado");
      




	R1D1 = new Robot1(R1Pos, currentWorld);
	eye = new Camera();
	vec3d p;
	p.x = 10;
	p.y = -0;
	p.z = 5;
	vec3d r;
	r.x = 180.0;
	r.y = -20;
	r.z = 0;
	eye->setPosition(p);
	eye->setRotation(r);


	// BZK_Time Timer(20);
	// Timer.Start();


	setKeyDownFunction(&onKeyDown);
	setKeyUpFunction(&onKeyUp);

	double simstep = 0.05;
	//    rz = ry = rx = 0.0f;


	next_time = SDL_GetTicks() + TICK_INTERVAL;
	while (1) {


		int nrofsteps = (int) ceilf((TICK_INTERVAL / simstep) / 100);
		process_events();

		currentWorld->iSpaces->Update();



		R1D1->Update(0.05);
		for (int i = 0; i < nrofsteps; i++) {
			dSpaceCollide(currentWorld->topLevelSpace, 0, &nearCallback);
			currentWorld->Update(0.05f);
		}
		draw_screen();
		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;


	}
	return 0;
}

void onKeyUp(void *p) {


	int k = int(p);
	switch (k) {
	case SDLK_w:
		R1D1->accellPressed = true;
		break;


	case SDLK_d:
		R1D1->rightPressed = true;
		break;
	case SDLK_a:
		R1D1->leftPressed = true;
		break;


	case SDLK_s:
		R1D1->reversePressed = true;
		break;

	case SDLK_SPACE:
		R1D1->breaking = true;
		break;
	case SDLK_LEFT:
		R1D1->rotingLeft = true;
		break;

	case SDLK_RIGHT:
		R1D1->rotingRight = true;

		break;

	case SDLK_LCTRL:
		R1D1->shot();
		break;

	case SDLK_UP:
		R1D1->rotingUp = true;
		break;

	case SDLK_DOWN:
		R1D1->rotingDown = true;
		break;

	default:
		break;
	}
}

void onKeyDown(void *p) {
	int k = int(p);
	switch (k) {

	case SDLK_w:
		R1D1->accellPressed = false;
		break;



	case SDLK_SPACE:
		R1D1->breaking = false;
		break;

	case SDLK_a:
		R1D1->leftPressed = false;
		break;

	case SDLK_d:
		R1D1->rightPressed = false;

		break;

	case SDLK_s:
		R1D1->reversePressed = false;
		break;

	case SDLK_ESCAPE:
		sair(0);
		break;

	case SDLK_LEFT:
		R1D1->rotingLeft = false;
		break;

	case SDLK_RIGHT:
		R1D1->rotingRight = false;

		break;

	case SDLK_UP:
		R1D1->rotingUp = false;
		break;

	case SDLK_DOWN:
		R1D1->rotingDown = false;
		break;

	default:
		break;
	}
}