#ifndef __TERRIAN__
#define __TERRIAN__

#include "VertexBufferObject.h"
#include "vec3d.h"
#include "Mesh.h"




class Terrain : public Mesh
{
public:
	unsigned int w;
	unsigned int h;
	float centerX;
	float centerY;
	std::vector<vec3d> temp_vecsA;
	std::vector<vec3d> temp_vecsB;
	std::vector<TexCoord2> temp_tex;

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
