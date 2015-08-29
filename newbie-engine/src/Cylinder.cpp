#include "Cylinder.h"
#include "Graphics.h"
#include <GL/glut.h>
#include <stdio.h>
#include "VertexBufferObject.h"

#include <math.h>

// draw a cylinder of length l and radius r, aligned along the z axis

static void drawCylinder(float l, float r, float zoffset) {
    int i;
    float tmp, ny, nz, a, ca, sa;
    const int n = 64; // number of sides to the cylinder (divisible by 4)

    l *= 0.5;
    a = float(M_PI * 2.0) / float(n);
    sa = (float) sin(a);
    ca = (float) cos(a);

    // draw cylinder body
    ny = 1;
    nz = 0; // normal vector = (0,ny,nz)
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= n; i++) {
        glNormal3d(ny, nz, 0);
        glVertex3d(ny*r, nz*r, l + zoffset);
        glNormal3d(ny, nz, 0);
        glVertex3d(ny*r, nz*r, -l + zoffset);
        // rotate ny,nz
        tmp = ca * ny - sa*nz;
        nz = sa * ny + ca*nz;
        ny = tmp;
    }
    glEnd();

    // draw top cap
    glShadeModel(GL_FLAT);
    ny = 1;
    nz = 0; // normal vector = (0,ny,nz)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, 0, 1);
    glVertex3d(0, 0, l + zoffset);
    for (i = 0; i <= n; i++) {


        glNormal3d(0, 0, 1);
        glVertex3d(ny*r, nz*r, l + zoffset);



        // rotate ny,nz
        tmp = ca * ny - sa*nz;
        nz = sa * ny + ca*nz;
        ny = tmp;
    }
    glEnd();

    // draw bottom cap
    ny = 1;
    nz = 0; // normal vector = (0,ny,nz)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, 0, -1);
    glVertex3d(0, 0, -l + zoffset);
    for (i = 0; i <= n; i++) {


        glNormal3d(0, 0, -1);
        glVertex3d(ny*r, nz*r, -l + zoffset);


        // rotate ny,nz
        tmp = ca * ny + sa*nz;
        nz = -sa * ny + ca*nz;
        ny = tmp;
    }
    glEnd();
}

Cylinder::Cylinder(float radius_, float height_, float slices_, float stacks_) {
    radius = radius_;
    height = height_;
    slices = slices_;
    stacks = stacks_;

    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y = iVel.z = 0;
    iRotate.x = iRotate.y = iRotate.z = 0.0f;
    iM = 1;
    Mat = new Material();
    dQFromAxisAndAngle(q, 1, 0, 0, M_PI * 0.5);
    useTexture = false;
    data = new BodyData();
    data->setName("Cylinder");

}

void Cylinder::Draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Transform();




    if (Mat != NULL) {
        Mat->Build();

    }

    drawCylinder(height, radius, 0);
   
    glPopMatrix();
}

void Cylinder::Update() {
}

void Cylinder::MakeGeom(dSpaceID space) {
    iGeom = dCreateCylinder(space, radius, height);

    dMatrix3 R, R0, R1, R2, R3;

    dRFromAxisAndAngle(R1, 1, 0, 0, DEG2RAD(iRotate.x));
    dRFromAxisAndAngle(R2, 0, 1, 0, DEG2RAD(iRotate.y));
    dRFromAxisAndAngle(R3, 0, 0, 1, DEG2RAD(iRotate.z));
    dMultiply0(R0, R1, R2, 3, 3, 3);
    dMultiply0(R, R0, R3, 3, 3, 3);

    dGeomSetRotation(iGeom, R);
    dGeomSetPosition(iGeom, iPosition.x, iPosition.y, iPosition.z);
};

void Cylinder::MakeBody(dWorldID world) {

    iBody = dBodyCreate(world);
    dBodySetQuaternion(iBody, q);
    dBodySetPosition(iBody, iPosition.x, iPosition.y, iPosition.z);
    dBodySetLinearVel(iBody, iVel.x, iVel.y, iVel.z);
    dMassSetCylinder(&iMass, iM, 3, radius, height);

    dBodySetMass(iBody, &iMass);

    disabledSteps = 0;
    dBodySetAutoDisableFlag(iBody, 1);
    dBodySetData(iBody, data);
};


