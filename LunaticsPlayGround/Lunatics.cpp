#include "NewbieEngine.h"

#include "RobotCleaner.h"

void onKeyUp(void* k);
void onKeyDown(void* k);

static Uint32 next_time;
static Uint32 elapsedTime = 1;


Terrain* terreno = NULL;
SkyBox* sky = NULL;
RobotCleaner* cleaner = NULL; //Nosso Robo
Shader* perpixelLighting = NULL;
Shader* textureShader = NULL;
vec3d _lightPos = { 1.2f, 1.0f, 2.0f };

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

char strBuff[255];
int yaw = 0.1f;


static void draw_screen(void) {

	int i;

	glClearColor(0.0, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (cleaner != NULL)
	{
		const dReal* pos = dBodyGetPosition(cleaner->chassi->iBody);
		Singleton::getInstance().rootCamera.setPosition(vec3d{ pos[0] + 13,pos[1], pos[2] + 2 });
		Singleton::getInstance().rootCamera.setCamera();
	}

	Singleton::getInstance().rootCamera.recalculateViewMatrix();

	//if (sky)
		//sky->Draw(vec3d{ 0,0,0 });

	textureShader->Enable();
	textureShader->SetInteger("texture_slot_0", 0);
	textureShader->SetMat4("u_projection", glm::value_ptr(Singleton::getInstance().rootCamera.projection));
	textureShader->SetMat4("u_view", glm::value_ptr(Singleton::getInstance().rootCamera.view));

	terreno->Draw(textureShader);
	currentWorld->Draw(textureShader);
	cleaner->Draw(textureShader);

	

	textureShader->Disable();

	/*if (perpixelLighting != NULL)
		perpixelLighting->Enable();

	

	if (perpixelLighting != NULL)
		perpixelLighting->Disable();
*/
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

	terreno = new Terrain(512, 512, 1);

	//terreno->MakeGeom(currentWorld->topLevelSpace);
	ground = dCreatePlane(currentWorld->topLevelSpace, 0, 0, 1, 0);
	terreno->texture = new Texture("storage/textures/ground1.png");
	
	SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	vec3d p;
	p.x = 0;
	p.y = -0;
	p.z = 0;
	vec3d r;
	r.x = 180;
	r.y = 0;
	r.z = 0;
	Singleton::getInstance().rootCamera.setPosition(p);
	Singleton::getInstance().rootCamera.setRotation(r);
	Singleton::getInstance().rootCamera.setProjectionMatrix(50.0f, 0.1f, 1200.0f);

	vec3d R1Pos;
	R1Pos.x = 60;
	R1Pos.y = 0;
	R1Pos.z = 1;

	cleaner = new RobotCleaner(R1Pos, currentWorld);
	
	sky = new SkyBox("storage\\textures\\skybox\\front.png",
		"storage\\textures\\skybox\\back.png",
		"storage\\textures\\skybox\\left.png",
		"storage\\textures\\skybox\\right.png",
		"storage\\textures\\skybox\\top.png");

	sky->SetPosition(vec3d{ 0,0,40 });
	sky->SetSize(40);
	
	textureShader = new Shader();
	textureShader->Load("storage\\shaders\\Texture\\vertexshader.glsl", "storage\\shaders\\Texture\\fragmentshader.glsl");

	double simstep = 0.05;

	next_time = SDL_GetTicks() + TICK_INTERVAL;

	while (!quit) {

		int nrofsteps = (int)ceilf((TICK_INTERVAL / simstep) / 100);
		simstep = 0.05;
		
		simstep = simstep > 0 ? simstep : 0.05;
		process_events();
		cleaner->Update(simstep);
		for (int i = 0; i < nrofsteps; i++)
		{
			dSpaceCollide(currentWorld->topLevelSpace, 0, &nearCallback);
			currentWorld->Update(simstep);
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
			Singleton::getInstance().rootCamera.Turn(1, 0);
		}

		if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			Singleton::getInstance().rootCamera.Turn(-1, 0);
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
			Singleton::getInstance().rootCamera.Turn(mouseX, mouseY);
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
