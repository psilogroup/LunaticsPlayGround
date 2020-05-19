#include <math.h>
#include <stdio.h>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "Terrian.h"
#include "vec3d.h"
#include "Graphics.h"
#include <stdlib.h>


Terrain::Terrain(unsigned int width, unsigned int height, float scale) {

	w = width * scale;
	h = height * scale;


	texture = NULL;

	//Prepara a Malha de terreno
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
			vec3d v;
			v.x = (x * scale);
			v.y = (y * scale);
			v.z = 0.0f;
			temp_vecsA.push_back(v);
		}

	for (int y = 0; y < height - 1; y++)
		for (int x = 0; x < width - 1; x++) {
			//a
			int a = width * y + x;
			TexCoord2 uv_a = { 0.0,1.0 };
			//b
			int b = width * y + (x + 1);
			TexCoord2 uv_b = { 1.0,1.0 };
			//c
			int c = width * (y + 1) + (x + 1);
			TexCoord2 uv_c = { 1.0,0.0 };
			//d
			int d = width * (y + 1) + x;
			TexCoord2 uv_d = { 0.0,0.0 };

			vec3d va = temp_vecsA[a];
			vec3d vb = temp_vecsA[b];
			vec3d vc = temp_vecsA[c];
			vec3d vd = temp_vecsA[d];

			temp_vecsB.push_back(va);
			temp_vecsB.push_back(vb);
			temp_vecsB.push_back(vc);
			temp_vecsB.push_back(vd);

			temp_tex.push_back(uv_a);
			temp_tex.push_back(uv_b);
			temp_tex.push_back(uv_c);
			temp_tex.push_back(uv_d);


		}

	iPosition.x = -(width * scale) / 2.0f;
	iPosition.y = -(height * scale) / 2.0f;
	iPosition.z = 0.0;

	vecs = new vec3d[temp_vecsB.size()];
	texCoord = new TexCoord2[temp_tex.size()];

	memcpy(vecs, &temp_vecsB[0], temp_vecsB.size() * 3 * sizeof(float));
	memcpy(texCoord, &temp_tex[0], temp_tex.size() * 2 * sizeof(float));
	vbo = new VertexBufferObject();
	vbo->glMode = GL_QUADS;

	vbo->setVertices(vecs, temp_vecsB.size());
	vbo->setTexCoords(texCoord, temp_tex.size());

}

void Terrain::MakeGeom(dSpaceID space) {

	// triData = dGeomTriMeshDataCreate();
	//Physic's Data

	//dGeomTriMeshDataBuildSimple(triData, (dReal*)data, numVecs,(dTriIndex*)indexs, numIndexs);
	//dGeomTriMeshDataBuildSingle(triData, vecs, 3 * sizeof(float), numVecs, indexs, numIndexs, 3 * sizeof(dTriIndex));
	//iGeom = dCreateTriMesh(space, triData,0,0,0);
	//dGeomSetPosition(iGeom,iPosition.x,iPosition.y,iPosition.z);


	printf("Terreno Criado\n");
}

void Terrain::Draw() {
	glColor3f(0.0, 0.0, 1.0);

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(iPosition.x, iPosition.y, iPosition.z);
	glScalef(10.0f, 10.0f, 1.0f);
	if (texture != NULL)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		texture->bind();

	}


	glDisable(GL_LIGHTING);
	vbo->draw();

	if (texture != NULL)
	{
		texture->end();
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	glPopMatrix();
}

Terrain::~Terrain()
{
	if (texture != NULL)
		delete texture;
}
