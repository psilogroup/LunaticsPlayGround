#include "NewbieEngine.h"

#include "RobotCleaner.h"

void onKeyUp(void* k);
void onKeyDown(void* k);

static Uint32 next_time;
static Uint32 elapsedTime = 1;


Terrain* terreno = NULL;
Camera* eye = NULL;
SkyBox* sky = NULL;
RobotCleaner* cleaner = NULL; //Nosso Robo
Shader* perpixelLighting = NULL;


bool quit = false;
void process_events();
void MarchaRe();
void VirarDireita();
void VirarEsquerda();
void MoverFrente();
void sair(int code) {
	SDL_Quit();
	//dWorldDestroy(world);
	/* Exit program. */
	exit(code);
};

void posicionaCamera() {

	// setCamera(eye->position.x,eye->position.y,eye->position.z,
	//        eye->rotation.x,eye->rotation.y,eye->rotation.z);



}

char strBuff[255];


int yaw = 0.1f;
static void draw_screen(void) {

	int i;

	glClearColor(0.0, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	yaw += 1.0f;
	if (cleaner != NULL)
	{


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glScalef(0.5f,0.5f,0.5f);
		//Camera acompanhando o robo
		const dReal* pos = dBodyGetPosition(cleaner->chassi->iBody);
		const dReal* rot = dBodyGetRotation(cleaner->chassi->iBody);
		setCamera(pos[0] + 13, pos[1], pos[2] + 2,
			eye->rotation.x, eye->rotation.y, eye->rotation.z);

		/*gluLookAt(
			pos[0] + 13 - rot[0] + rot[2],
			pos[1] + rot[4] + rot[6],
			pos[2] + 1.5 - rot[8] + rot[10],
			pos[0] + rot[0] ,
			pos[1] + rot[4],
			pos[2] + rot[8],
			rot[2], rot[6], rot[10]
		);*/
	}


	//if (sky)
	//	sky->Draw(vec3d{ 0,0,0 });

	terreno->Draw();

	if (perpixelLighting != NULL)
		perpixelLighting->Enable();

	cleaner->Draw();

	if (perpixelLighting != NULL)
		perpixelLighting->Disable();

	currentWorld->Draw();


	SDL_GL_SwapWindow(Singleton::getInstance().mainwindow);
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

	currentWorld = new World("storage/Asset.xml");
	currentWorld->iSpaces->Update();

	terreno = new Terrain(256, 256, 2);

	terreno->MakeGeom(currentWorld->topLevelSpace);
	ground = dCreatePlane(currentWorld->topLevelSpace, 0, 0, 1, 0);
	terreno->texture = new Texture("storage/textures/ground1.png");
	eye = new Camera();
	SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	vec3d p;
	p.x = 0;
	p.y = -0;
	p.z = 0;
	vec3d r;
	r.x = 180;
	r.y = -10;
	r.z = 0;
	eye->setPosition(p);
	eye->setRotation(r);

	vec3d R1Pos;
	R1Pos.x = 60;
	R1Pos.y = 0;
	R1Pos.z = 1;

	cleaner = new RobotCleaner(R1Pos, currentWorld);
	perpixelLighting = new Shader();
	sky = new SkyBox("storage\\textures\\skybox\\front.png",
		"storage\\textures\\skybox\\back.png",
		"storage\\textures\\skybox\\left.png",
		"storage\\textures\\skybox\\right.png",
		"storage\\textures\\skybox\\top.png");

	sky->SetPosition(vec3d{ 0,0,40 });
	sky->SetSize(40);
	perpixelLighting->Load("storage\\shaders\\PerPixelLight\\vertexshader.txt", "storage\\shaders\\PerPixelLight\\fragmentshader.txt");
	double simstep = 0.05;
	next_time = SDL_GetTicks() + TICK_INTERVAL;
	while (!quit) {

		int nrofsteps = (int)ceilf((TICK_INTERVAL / simstep) / 100);

		process_events();
		cleaner->Update(0.05);
		for (int i = 0; i < nrofsteps; i++)
		{
			dSpaceCollide(currentWorld->topLevelSpace, 0, &nearCallback);
			currentWorld->Update(0.05f);
		}
		draw_screen();



		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;
	}

	return 0;
}


void process_events()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		cleaner->accellPressed = false;
		cleaner->rightPressed = false;
		cleaner->leftPressed = false;
		cleaner->reversePressed = false;
		cleaner->rotingLeft = false;
		cleaner->rotingRight = false;
		cleaner->rotingUp = false;
		cleaner->rotingDown = false;

		if (e.type == SDL_QUIT)
		{
			quit = true;
		}

		if (currentKeyStates[SDL_SCANCODE_W])
		{
			MoverFrente();
		}
		if (currentKeyStates[SDL_SCANCODE_D])
		{
			VirarDireita();
		}
		if (currentKeyStates[SDL_SCANCODE_A])
		{
			VirarEsquerda();
		}

		if (currentKeyStates[SDL_SCANCODE_S])
		{
			MarchaRe();
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			eye->Turn(1, 0);
		}

		if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			eye->Turn(-1, 0);
		}

		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{
			cleaner->shot();
		}

		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			cleaner->rotingUp = true;
		}

		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			cleaner->rotingDown = true;
		}

		if (currentKeyStates[SDL_SCANCODE_ESCAPE])
		{
			quit = true;
		}
		if (e.type == SDL_MOUSEMOTION) {
			int mouseX = (e.motion.xrel*-1) * 0.4;
			int mouseY = (e.motion.yrel*-1) * 0.4;
			eye->Turn(mouseX, mouseY);
		}

	}
}

void MarchaRe()
{
	cleaner->reversePressed = true;
}

void VirarEsquerda()
{
	cleaner->leftPressed = true;
}

void VirarDireita()
{
	cleaner->rightPressed = true;
}




void MoverFrente()
{
	cleaner->accellPressed = true;
}
