#include "NewbieEngine.h"

#include <iostream>


void setup_opengl( int width, int height )
{

    glEnable (GL_LIGHTING);
    glShadeModel (GL_SMOOTH);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace (GL_CCW);

    glViewport(0,0,width,height);
    glMatrixMode (GL_PROJECTION);
    

    //gluPerspective(50.0f, float(width) / float(height), .1f, 1200.0f);
    glm::mat4 Proj = glm::perspective(glm::radians(50.0f), 1.33f, 0.1f, 1200.f);
    glLoadMatrixf(glm::value_ptr(Proj));
   
    GLfloat light_Ka[]  = {1.0f,1.0f,1.0f,1.0f};
    GLfloat light_Kd[]  = {1.0f,1.0f,1.0f,1.0f};
    GLfloat light_Ks[]  = {1.0f,1.0f,1.0f,1.0f};

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    
    glLightfv(GL_LIGHT0,GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_Ka);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_Kd);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_Ks);
    glMateriali(GL_FRONT,GL_SHININESS,60);


}



int Iniciar()
{
    int width = 0;
    int height = 0;
    double stepSize = 30/1000.0;
    int bpp = 32;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Unable to initialize SDL";
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    Singleton::getInstance().rootCamera.width = 1920;
    Singleton::getInstance().rootCamera.height = 1080;

    Singleton::getInstance().mainwindow = SDL_CreateWindow( "Lunatycs PlayGround",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          Singleton::getInstance().rootCamera.width,
                                          Singleton::getInstance().rootCamera.height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP );

    if (!Singleton::getInstance().mainwindow)
    {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;

        SDL_Quit();

        return 1;

    }


    Singleton::getInstance().maincontext = SDL_GL_CreateContext(Singleton::getInstance().mainwindow);

    if( Singleton::getInstance().maincontext == NULL )
    {
        printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
//        success = false;
    }
    setup_opengl( Singleton::getInstance().rootCamera.width, Singleton::getInstance().rootCamera.height );

    char fakeParam[] = "fake";
    char *fakeargv[] = { fakeParam, NULL };
    int fakeargc = 1;

    glewInit();
    glutInit( &fakeargc, fakeargv );
    dInitODE2(0);
    dAllocateODEDataForThread(dAllocateMaskAll);
    
    return 1;
}


void draw_ground()
{


}

void drawString(const char *str,int x,int y,vec4d color, void *font)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
   // gluOrtho2D(0,800,0,600);


    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    glColor4f(color.x,color.y,color.z,color.w);
    glRasterPos2i(x,y);

    while (*str)
    {
        //glutBitmapCharacter(font,*str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();



}
