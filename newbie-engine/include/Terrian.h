#ifndef __TERRIAN__
#define __TERRIAN__

#include "Object.h"
#include "VertexBufferObject.h"
#include "vec3d.h"
#include "Mesh.h"
#include "Shader.h"



class Terrain : public Object
{
public:
	unsigned int w;
	unsigned int h;
	float centerX;
	float centerY;
	
	
	int numVecs;
	
	Terrain(unsigned int width, unsigned int height, float scale);

	void MakeGeom(dSpaceID space);
	Terrain();
	virtual void Draw(Shader * shader);
	virtual ~Terrain();

private:
	unsigned int VAO;
	unsigned int VBO;

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
