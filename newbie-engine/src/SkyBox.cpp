#include "SkyBox.h"


SkyBox::SkyBox (const char *f,const char *b,const char *l,const char *r,const char *u)
{
    front = new Texture(f);
    back = new Texture(b);
    left = new Texture(l);
    right = new Texture(r);
    Up = new Texture(u);

}


void SkyBox::Draw(vec3d angles)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    float x = Size  * 0.5;
    float y = Size * 0.5;
    float z = Size * 0.5;
    float xs = Position.x*Size;
    float ys = Position.y*Size;
    float zs = Position.z*Size;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(angles.z,0,1,0);
    glScalef(Size,Size,Size);

    // Draw Front side
    glDisable(GL_CULL_FACE);
    if (front)
    {
        front->bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(-x,-y,-z);
        glTexCoord2f(1,1);
        glVertex3f(x,-y, -z);
        glTexCoord2f(1,0);
        glVertex3f(y, x, -z);
        glTexCoord2f(0,0);
        glVertex3f(-x, y,-z);
        glTexCoord2f(0,1);
        glVertex3f(-x, -y,-z);
        glEnd();
    }
    if (back)
    {
        back->bind();

        glColor3f(1.0f,1.0f,1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(-x,-y,z);
        glTexCoord2f(1,1);
        glVertex3f(x,-y, z);
        glTexCoord2f(1,0);
        glVertex3f(x, y, z);
        glTexCoord2f(0,0);
        glVertex3f(-x, y,z);
        glTexCoord2f(0,1);
        glVertex3f(-x, -y,z);
        glEnd();

    }

    if (left)
    {
        left->bind();


        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(-x,-y,z);
        glTexCoord2f(1,1);
        glVertex3f(-x,-y, -z);
        glTexCoord2f(1,0);
        glVertex3f(-x, y, -z);
        glTexCoord2f(0,0);
        glVertex3f(-x, y,z);
        glTexCoord2f(0,1);
        glVertex3f(-x, -y,z);
        glEnd();
    }

    if (right)
    {

        right->bind();

        glColor3f(1.0f,1.0f,1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(x,-y,-z);
        glTexCoord2f(1,1);
        glVertex3f(x,-y, z);
        glTexCoord2f(1,0);
        glVertex3f(x, y, z);
        glTexCoord2f(0,0);
        glVertex3f(x, y,-z);
        glTexCoord2f(0,1);
        glVertex3f(x, -y,-z);
        glEnd();

    }
    if (Up)
    {

        Up->bind();

        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(-x,y,-z);
        glTexCoord2f(1,1);
        glVertex3f(x,y, -z);
        glTexCoord2f(1,0);
        glVertex3f(x, y, z);
        glTexCoord2f(0,0);
        glVertex3f(-x, y,z);
        glTexCoord2f(0,1);
        glVertex3f(-x, y,-z);
        glEnd();

    }
    glEnable(GL_CULL_FACE);
    glPopMatrix();
//    if (Down)
//    {
//
//
//        Down->bind();
//
//        glBegin(GL_QUADS);
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(x,		  y,		z);
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(x,		  y,		z+length);
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(x+width, y,		z+length);
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(x+width, y,		z);
//        glEnd();
//    }
}
void SkyBox::SetPosition(vec3d pos)
{
    Position = pos;
}
void SkyBox::SetSize(float sz)
{
    Size = sz;
}

SkyBox::~SkyBox()
{
    if (front)
        delete front;

    if (back)
        delete back;

    if (left)
        delete left;

    if (right)
        delete right;

    if (Up)
        delete Up;




}
