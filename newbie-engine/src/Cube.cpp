#include "Cube.h"
#include "Graphics.h"
#include <GL/glut.h>
#include <stdio.h>
#include "VertexBufferObject.h"

#include <math.h>

const int vCount =36;
const int nCount =  3;
const int iCount = 36;

const int one = 1;

float vertexData[vCount*3] =
{
    //face frontal
    -1,1,1, -1,-1,1, 1,-1,1,
    1,1,1, -1,1,1, 1,-1,1,

    //top face
    1,1,1, -1,1,1, -1,1,-1,
    1,1,-1, -1,1,-1, 1,1,1,


    //bottom face
    1,-1,1, -1,-1,1, -1,-1,-1,
    1,-1,-1, -1,-1,-1, 1,-1,1,

    //back face
    -1,1,-1, -1,-1,-1, 1,-1,-1,
    1,-1,-1, 1,1,-1, -1,1,-1,

    //Right face
    1,1,1, 1,-1,1, 1,-1,-1,
    1,-1,-1, 1,1,-1, 1,1,1,

    //left face
    -1,1,1, -1,-1,1, -1,-1,-1,
    -1,-1,-1, -1,1,-1, -1,1,1

};

float normalData [nCount] =
    {
       1,1,1
    };





Cube::Cube()
{
    
    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y =iVel.z = 0;
    iRotate.x = iRotate.y = iRotate.z = 0.0f;
    iM = 1;
    Mat = new Material();
    dQFromAxisAndAngle(q,1,0,0,M_PI*0.5);
    useTexture = false;

    data = new BodyData();
   data->setName("Cube");

}
void Cube::Draw()
{
    float lx = iSize.x*0.5f;
	float ly = iSize.y*0.5f;
	float lz = iSize.z*0.5f;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Transform();




    if (Mat != NULL)
    {
        Mat->Build();

    }
    Graphics::cube(iSize.x,iSize.y,iSize.z);

 
    glPopMatrix();

}

void Cube::Update()
{
    const dReal *p,*r;
	UpdateDisableState();
    p = dGeomGetPosition(iGeom);
    iPosition.x = p[0];
    iPosition.y = p[1];
    iPosition.z = p[2];
    
    

};
