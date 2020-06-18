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

	std::vector<vec3d> temp_vecsA;
	std::vector<vec3d> temp_vecsB;
	std::vector<TexCoord2> temp_tex;

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

	numVecs = temp_vecsB.size();


	VertexData* vData = new VertexData[temp_vecsB.size()];

	for (unsigned int i = 0; i < numVecs; i++) {
		


		vData[i].vector.x = temp_vecsB[i].x;
		vData[i].vector.y = temp_vecsB[i].y;
		vData[i].vector.z = temp_vecsB[i].z;


		vData[i].normal.x = 0.0f;
		vData[i].normal.y = 0.0f;
		vData[i].normal.z = 1.0f;


		vData[i].texCoord.u = temp_tex[i].u;
		vData[i].texCoord.v = temp_tex[i].v;
	}


	// first, configure the cube's VAO (and VBO)

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVecs * 8, vData, GL_STATIC_DRAW);

	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	delete vData;
	temp_vecsA.clear();
	temp_vecsB.clear();
	temp_tex.clear();



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

void Terrain::Draw(Shader* shader) {
	
	glm::mat4 m1 = glm::mat4(1.0f);
	glm::mat4 m2 = glm::scale(m1, glm::vec3{ 1.0f,1.0f,1.0f });

	glm::mat4 model = glm::translate(m2, glm::vec3{ iPosition.x,iPosition.y,iPosition.z });
	shader->SetMat4("u_model", glm::value_ptr(model));

	if (texture != NULL)
	{
		texture->bind();
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, numVecs);

	if (texture != NULL)
	{
		texture->end();
	}
	glPopMatrix();
}

Terrain::~Terrain()
{
	if (texture != NULL)
		delete texture;
}
