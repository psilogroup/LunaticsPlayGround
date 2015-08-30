#include "NewbieEngine.h"
#include <GL/freeglut.h>



void setCamera (float x,float y,float z, float h, float p, float r)
{
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    glRotatef(90, 0,0,1);
    glRotatef(90, 0,1,0);
    glRotatef(r, 1,0,0);
    glRotatef(p, 0,1,0);
    glRotatef(-h, 0,0,1);

    glTranslatef(-x,-y,-z);

}


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
    glLoadIdentity();

    const float vnear = 0.1f;
    const float vfar = 6000.0f;
    const float k = 1.0f;

    if (width >= height)
    {
        float k2 = float(height)/float(width);
        glFrustum(-vnear*k,vnear*k,-vnear*k*k2,vnear*k*k2,vnear,vfar);
    }
    else
    {
        float k2 = float(width)/float(height);
        glFrustum (-vnear*k*k2,vnear*k*k2,-vnear*k,vnear*k,vnear,vfar);

    }



    glClearColor (0.0,0.0,0.0,0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    setCamera(xyz[0],xyz[1],xyz[2],hpr[0],hpr[1],hpr[2]);

    GLfloat light_Ka[]  = {0.1f,0.1f,0.1f,1.0f};
    GLfloat light_Kd[]  = {1.0f,1.0f,1.0f,1.0f};
    GLfloat light_Ks[]  = {1.0f,1.0f,1.0f,1.0f};

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

    Singleton::getInstance().rootCamera.width = 800;
    Singleton::getInstance().rootCamera.height = 600;

    Singleton::getInstance().mainwindow = SDL_CreateWindow( "Lunatycs PlayGround",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          Singleton::getInstance().rootCamera.width,
                                          Singleton::getInstance().rootCamera.height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

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

    glutInit( &fakeargc, fakeargv );
    dInitODE2(0);
    dAllocateODEDataForThread(dAllocateMaskAll);
    glewInit();
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
    gluOrtho2D(0,800,0,600);


    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    glColor4f(color.x,color.y,color.z,color.w);
    glRasterPos2i(x,y);

    while (*str)
    {
        glutBitmapCharacter(font,*str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();



}
