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



	while (1)
	{

		/*struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TexCoord;
			float TexIndex;
			float TilingFactor;
		};*/

		//vertex 12 bytes
		//color 16 bytes
		//tex 8 bytes

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


	VertexData* vData = new VertexData[numIndexs];

	for (unsigned int i = 0; i < numIndexs; i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];
		unsigned int uvIndex = uvIndices[i];

		
		vData[i].vector.x = temp_vertices[vertexIndex - 1].x;
		vData[i].vector.y = temp_vertices[vertexIndex - 1].y;
		vData[i].vector.z = temp_vertices[vertexIndex - 1].z;


		vData[i].normal.x = temp_normals[normalIndex - 1].x;
		vData[i].normal.y = temp_normals[normalIndex - 1].y;
		vData[i].normal.z = temp_normals[normalIndex - 1].z;

	
		vData[i].texCoord.u = temp_uvs[uvIndex - 1].u;
		vData[i].texCoord.v = 1-temp_uvs[uvIndex - 1].v;
	}


	// first, configure the cube's VAO (and VBO)
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*numIndexs*8, vData, GL_STATIC_DRAW);

	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);



	temp_vertices.clear();
	temp_uvs.clear();
	temp_normals.clear();
	vertexIndices.clear();
	uvIndices.clear();
	normalIndices.clear();

	delete vData;
	fclose(file);



	//vbo = new VertexBufferObject();
	//vbo->glMode = GL_TRIANGLES;

	//vbo->setVertices(vecs, numIndexs);
	//vbo->setIndexs(indexs, numIndexs);

	//if (numNormals > 0)
	//	vbo->setNormals(normals, numIndexs);

	//if (numTexs > 0)
	//{
	//	vbo->setTexCoords(texCoord, numTexs);
//	}


}



void Mesh::Draw()
{
	
	if (texture != NULL)
	{
		texture->bind();
	}


	//vbo->draw();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numIndexs);

	glBindVertexArray(0);
	
	if (texture != NULL)
	{
		texture->end();
	}
	

}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	delete texture;
}
