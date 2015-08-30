#include "Cube.h"
#include "Graphics.h"
#include <GL/glut.h>
#include <stdio.h>
#include "VertexBufferObject.h"

#include <math.h>

Cube::Cube()
{

    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y =iVel.z = 0;
    iRotate.x = iRotate.y = iRotate.z = 0.0f;
    iM = 1;
    Mat = new Material();
    dQFromAxisAndAngle(q,1,0,0,M_PI*0.5);

    data = new BodyData();
    data->setName("Cube");

    vecs = new vec3d[24];
    texCoord = new TexCoord2[24];
    texture = NULL;


    //Make Verte Buffer Object
    // Front Face
    vecs[0] = {-1.0f, -1.0f,  1.0f};
    vecs[1] = {1.0f, -1.0f,  1.0f};
    vecs[2] = {1.0f,  1.0f,  1.0f};
    vecs[3] = {-1.0f,  1.0f,  1.0f};
    // Back Face
    vecs[4] = {-1.0f, -1.0f, -1.0f};
    vecs[5] = {-1.0f,  1.0f, -1.0f};
    vecs[6] = { 1.0f,  1.0f, -1.0f};
    vecs[7] = { 1.0f, -1.0f, -1.0f};
    // Top Face
    vecs[8] = {-1.0f,  1.0f, -1.0f};
    vecs[9] = {-1.0f,  1.0f,  1.0f};
    vecs[10] = { 1.0f,  1.0f,  1.0f};
    vecs[11] = { 1.0f,  1.0f, -1.0f};
    // Bottom Face
    vecs[12] = {-1.0f, -1.0f, -1.0f};
    vecs[13] = { 1.0f, -1.0f, -1.0f};
    vecs[14] = { 1.0f, -1.0f,  1.0f};
    vecs[15] = {-1.0f, -1.0f,  1.0f};
    // Right face
    vecs[16] = { 1.0f, -1.0f, -1.0f};
    vecs[17] = { 1.0f,  1.0f, -1.0f};
    vecs[18] = { 1.0f,  1.0f,  1.0f};
    vecs[19] = { 1.0f, -1.0f,  1.0f};
    // Left Face
    vecs[20] = {-1.0f, -1.0f, -1.0f};
    vecs[21] = {-1.0f, -1.0f,  1.0f};
    vecs[22] = {-1.0f,  1.0f,  1.0f};
    vecs[23] = {-1.0f,  1.0f, -1.0f};

    texCoord[0] = {0.0f, 0.0f};
    texCoord[1] = {1.0f, 0.0f};
    texCoord[2] = {1.0f, 1.0f};
    texCoord[3] = {0.0f, 1.0f};
    // Back Face
    texCoord[4] = {1.0f, 0.0f};
    texCoord[5] = {1.0f, 1.0f};
    texCoord[6] = {0.0f, 1.0f};
    texCoord[7] = {0.0f, 0.0f};
    // Top Face
    texCoord[8] = {0.0f, 1.0f};
    texCoord[9] = {0.0f, 0.0f};
    texCoord[10] = {1.0f, 0.0f};
    texCoord[11] = {1.0f, 1.0f};
    // Bottom Face
    texCoord[12] = {1.0f, 1.0f};
    texCoord[13] = {0.0f, 1.0f};
    texCoord[14] = {0.0f, 0.0f};
    texCoord[15] = {1.0f, 0.0f};
    // Right face
    texCoord[16] = {1.0f, 0.0f};
    texCoord[17] = {1.0f, 1.0f};
    texCoord[18] = {0.0f, 1.0f};
    texCoord[19] = {0.0f, 0.0f};
    // Left Face
    texCoord[20] = {0.0f, 0.0f};
    texCoord[21] = {1.0f, 0.0f};
    texCoord[22] = {1.0f, 1.0f};
    texCoord[23] = {0.0f, 1.0f};
    vbo = new VertexBufferObject();
    vbo->glMode = GL_QUADS;

    vbo->setVertices(vecs,24);
    vbo->setTexCoords(texCoord,24);

}
Cube::Cube::Cube(bool useVbo)
{
    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y =iVel.z = 0;
    iRotate.x = iRotate.y = iRotate.z = 0.0f;
    iM = 1;
    Mat = new Material();
    dQFromAxisAndAngle(q,1,0,0,M_PI*0.5);

    data = new BodyData();
    data->setName("Cube");

    vecs = new vec3d[24];
    texCoord = new TexCoord2[24];
    texture = NULL;
    vbo = NULL;

}
void Cube::Draw()
{
    float lx = iSize.x*0.5f;
    float ly = iSize.y*0.5f;
    float lz = iSize.z*0.5f;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Transform();
    glScalef(iSize.x*0.5,iSize.y*0.5,iSize.z*0.5);

    if (texture != NULL)
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        texture->bind();
    }
    if (vbo != NULL)
        vbo->draw();

     if (texture != NULL)
    {
        texture->end();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }


    glPopMatrix();

}

void Cube::Update()
{
    const dReal *p,*r;
    //UpdateDisableState();
    p = dGeomGetPosition(iGeom);
    iPosition.x = p[0];
    iPosition.y = p[1];
    iPosition.z = p[2];
}

Cube::~Cube()
{

}
