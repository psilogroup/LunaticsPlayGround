#ifndef __TERRIAN__
#define __TERRIAN__

#include "Object.h"
#include "VertexBufferObject.h"
#include "vec3d.h"
#include "Mesh.h"




class Terrain : public Object
{
public:
	unsigned int w;
	unsigned int h;
	float centerX;
	float centerY;
	std::vector<vec3d> temp_vecsA;
	std::vector<vec3d> temp_vecsB;
	std::vector<TexCoord2> temp_tex;
	vec3d* vecs;
	vec3d* normals;
	dTriIndex* indexs;
	TexCoord2* texCoord;
	Texture* texture;
	Terrain(unsigned int width, unsigned int height, float scale);

	void MakeGeom(dSpaceID space);
	Terrain();
	virtual void Draw();
	virtual ~Terrain();

};

class SplitedTerrain
{
public:
	int numChunks;
	int chunksX;
	int chunksY;
	Terrain* chunks;

};

#endif
