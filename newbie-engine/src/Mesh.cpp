#include "BZK_ParsingTools.h"
#include "Mesh.h"
#include "Graphics.h"
#include "BZK_List.h"

Mesh::Mesh()
{
	iSize.x = iSize.y = iSize.z = 1;
	iPosition.x = iPosition.y = iPosition.z = 0;
	iVel.x = iVel.y = iVel.z = 0;

	iM = 1;

	Mat = new Material();
	setColor(Mat->Ka, 0.0, 0.0, 0.0);
	setColor(Mat->Kd, 1.0, 0.0, 0.0);
	setColor(Mat->Ks, 0.0, 0.0, 1.0);
}


Mesh::Mesh(std::string filepath)
{
	iSize.x = iSize.y = iSize.z = 1;
	iPosition.x = iPosition.y = iPosition.z = 0;
	iVel.x = iVel.y = iVel.z = 0;
	//   dMassSetZero(&iMass);
	iM = 1;

	Mat = new Material();
	setColor(Mat->Ka, 0.0, 0.0, 1.0);
	setColor(Mat->Kd, 0.0, 0.0, 1.0);
	setColor(Mat->Ks, 1.0, 1.0, 1.0);
	texture = NULL;

	FILE* file = fopen(filepath.c_str(), "r");
	std::vector<vec3d> temp_vertices;
	std::vector<vec3d> temp_uvs;
	std::vector<vec3d> temp_normals;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	numVecs = 0;
	numTexs = 0;

	while (1)
	{

		char lineHeader[128];
		int res = fscanf(file, "%s", &lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the lo

		if (strcmp(lineHeader, "v") == 0) {
			vec3d vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);

		}
		else if (strcmp(lineHeader, "vt") == 0) {
			vec3d uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3d normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			//int matches = fscanf(file, "%s", &lineHeader);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				fclose(file);
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	numVecs = temp_vertices.size();
	numIndexs = vertexIndices.size();
	numNormals = normalIndices.size();

	std::cout << "Vetores: " << numVecs << " " << std::endl;
	std::cout << "numIndexs: " << numIndexs << " " << std::endl;
	std::cout << "numNormals: " << numNormals << " " << std::endl;
	std::cout << "numUvs: " << temp_uvs.size() << " " << std::endl;
	vecs = new vec3d[numIndexs];
	indexs = new dTriIndex[numIndexs];
	normals = new vec3d[numIndexs];

	for (unsigned int i = 0; i < numIndexs; i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];
		unsigned int uvIndex = uvIndices[i];

		vecs[i].x = temp_vertices[vertexIndex - 1].x;
		vecs[i].y = temp_vertices[vertexIndex - 1].y;
		vecs[i].z = temp_vertices[vertexIndex - 1].z;

		normals[i].x = temp_normals[normalIndex - 1].x;
		normals[i].y = temp_normals[normalIndex - 1].y;
		normals[i].z = temp_normals[normalIndex - 1].z;
	}





	temp_vertices.clear();
	temp_uvs.clear();
	temp_normals.clear();
	vertexIndices.clear();
	uvIndices.clear();
	normalIndices.clear();

	fclose(file);



	vbo = new VertexBufferObject();
	vbo->glMode = GL_TRIANGLES;

	vbo->setVertices(vecs, numIndexs);
	//vbo->setIndexs(indexs, numIndexs);

	if (numNormals > 0)
		vbo->setNormals(normals, numIndexs);
	/*
	if (numTexs > 0)
	{
		vbo->setTexCoords(texCoord, numTexs);
	}
	*/

}
void Mesh::MakeBody(dWorldID world)
{

	/*iBody = dBodyCreate(world);
	dGeomSetBody(iGeom, iBody);
	dMassSetZero(&iMass);
	dMassSetTrimesh(&iMass, iM, iGeom);
	dMassTranslate(&iMass, -iMass.c[0], -iMass.c[1], -iMass.c[2]);
	dBodySetMass(iBody, &iMass);
	*/

}

void Mesh::MakeGeom(dSpaceID space)
{

	/*triData = dGeomTriMeshDataCreate();
	dGeomTriMeshDataBuildSimple(triData, (dReal*)vecs, numVecs, (dTriIndex*)indexs, numIndexs);
	iGeom = dCreateTriMesh(space, triData, 0, 0, 0);

	dMatrix3 R, R0, R1, R2, R3;

	dRFromAxisAndAngle(R1, 1, 0, 0, DEG2RAD(iRotate.x));
	dRFromAxisAndAngle(R2, 0, 1, 0, DEG2RAD(iRotate.y));
	dRFromAxisAndAngle(R3, 0, 0, 1, DEG2RAD(iRotate.z));
	dMultiply0(R0, R1, R2, 3, 3, 3);
	dMultiply0(R, R0, R3, 3, 3, 3);
	dGeomSetRotation(iGeom, R);
	// dGeomSetQuaternion(iGeom,q);
	dGeomSetPosition(iGeom, iPosition.x, iPosition.y, iPosition.z);
	//dMassTranslate(&iMass,-iPosition.x, -iPosition.y, -iPosition.z);*/
}

void Mesh::Draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glTranslatef(iPosition.x, iPosition.y, iPosition.z);
	
	if (Mat != NULL)
	{
		Mat->Build();

	}
	//Draw Here
	if (texture != NULL)
	{
		texture->bind();
	}

	vbo->draw();

	if (texture != NULL)
	{
		texture->end();
	}
	glPopMatrix();

}

void Mesh::Update()
{
	/*const dReal* p = dGeomGetPosition(iGeom);
	iPosition.x = p[0];
	iPosition.y = p[1];
	iPosition.z = p[2];
	*/
};

Mesh::~Mesh()
{
	delete vecs;
	delete indexs;
	delete normals;
}
