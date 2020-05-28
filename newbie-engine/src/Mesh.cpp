#include "BZK_ParsingTools.h"
#include "Mesh.h"
#include "Graphics.h"
#include "BZK_List.h"

Mesh::Mesh()
{
	
}


Mesh::Mesh(std::string filepath)
{
	texture = NULL;

	FILE* file = fopen(filepath.c_str(), "r");
	std::vector<vec3d> temp_vertices;
	std::vector<TexCoord2> temp_uvs;
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
			TexCoord2 uv;
			fscanf(file, "%f %f\n", &uv.u, &uv.v);
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
	numTexs = uvIndices.size();
	std::cout << "Vetores: " << numVecs << " " << std::endl;
	std::cout << "numIndexs: " << numIndexs << " " << std::endl;
	std::cout << "numNormals: " << numNormals << " " << std::endl;
	std::cout << "numUvs: " << temp_uvs.size() << " " << std::endl;
	vecs = new vec3d[numIndexs];
	indexs = new dTriIndex[numIndexs];
	normals = new vec3d[numIndexs];
	texCoord = new TexCoord2[numIndexs];

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

		texCoord[i].u = temp_uvs[uvIndex - 1].u;
		texCoord[i].v = 1-temp_uvs[uvIndex - 1].v;
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

	if (numTexs > 0)
	{
		vbo->setTexCoords(texCoord, numTexs);
	}


}



void Mesh::Draw()
{
	
	if (texture != NULL)
	{
		texture->bind();
	}

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	
	vbo->draw();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	if (texture != NULL)
	{
		texture->end();
	}
	

}

Mesh::~Mesh()
{
	delete vecs;
	delete indexs;
	delete normals;
	delete texCoord;
	delete vbo;
	delete texture;
}
