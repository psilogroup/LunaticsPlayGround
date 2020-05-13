#include "World.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Wavefront.h"
#include "BZK_ParsingTools.h"
#include <stdio.h>
#include "BZK_XMLTag.h"
#include <map>

void MeshObjProp(Object* obj);

World::World(string aWorld)
{
	space = "<Space>";
	endSpace = "</Space>";
	name = "<Name>";
	endName = "</Name>";
	cube = "<Cube>";
	endCube = "</Cube>";
	sphere = "<Sphere>";
	endSphere = "</Sphere>";
	size = "<Size>";
	endSize = "</Size>";
	position = "<Pos>";
	endPosition = "</Pos>";
	mass = "<Mass>";
	endMass = "</Mass>";
	rotation = "<Rot>";
	endRotation = "</Rot>";
	linearVel = "<VelLin>";
	endLinearVel = "</VelAng>";
	angularVel = "<VelAng>";
	endAngularVel = "</VelAng>";
	vec = "<Vec>";
	endVec = "</Vec>";
	type = "<Type>";
	endType = "</Type>";
	mesh = "<Mesh>";
	endMesh = "</Mesh>";
	path = "<Path>";
	endPath = "</Path>";
	material = "<Mat>";
	ka = "<Ka>";
	endKa = "</Ka>";
	kd = "<Kd>";
	endKd = "</Kd>";
	ks = "<Ks>";
	endKs = "</Ks>";
	ke = "<Ke>";
	endKe = "</Ke>";
	endMaterial = "</Mat>";
	vec4 = "<Vec4>";
	endVec4 = "</Vec4>";
	radius = "<Radius>";
	endRadius = "</Radius>";
	indexData = "<IndexData>";
	endIndexData = "</IndexData>";
	vertexData = "<VertexeData>";
	endVertexData = "</VertexeData>";
	uvData = "<UVData>";
	endUVData = "</UVData>";
	iniTexture = "<Texture>";
	endTexture = "</Texture>";


	assetLib = new AssetLibrary();
	stepSize = 30.0f / 1000.0f;
	world = dWorldCreate();
	dWorldSetGravity(world, 0.0, 0.0, -9.8);
	dWorldSetCFM(world, 1e-5);
	dWorldSetERP(world, 0.8);
	dWorldSetQuickStepNumIterations(world, 30);
	dWorldSetAutoDisableFlag(world, 1);
	dWorldSetAutoDisableAverageSamplesCount(world, 10);
	contactGroup = dJointGroupCreate(0);

	topLevelSpace = dSweepAndPruneSpaceCreate(0, dSAP_AXES_XYZ);
	// topLevelSpace = dHashSpaceCreate(0);
	iSpaces = new SpaceManager();
	currentSpace = new Space(topLevelSpace);
	//  currentSpace->iSpace = topLevelSpace;
	iSpaces->Add(currentSpace);
	vec3d pos = { 0.0f,0.0f,-80.0f };
	vec3d rot = { 0.0f,0.0f,0.0f };

	sceneNode = new Scene();
	sceneNode->camera->setPosition(pos);
	sceneNode->camera->setRotation(rot);

	Datafile.clear();
	Datafile.open(aWorld.c_str());

	if (!Datafile.is_open())
	{
		cout << "Não foi possível abrir arquivo: " << aWorld.c_str() << std::endl;
		Datafile.clear();

	}
	while (!Datafile.eof())
	{
		Echo = BZK_ParsingTools::GetNextToken(&Datafile);
		if (Echo == space)
		{
			getSpace();
		}

		if (Echo == cube)
		{
			getCube();
		}

		if (Echo == mesh)
		{
			getMesh();
		}

		if (Echo == sphere)
		{
			getSphere();
		}

		if (Echo == endSpace)
		{
			iSpaces->Add(currentSpace);
			// delete currentSpace;
		}



	}
	Datafile.clear();
}

World::World(vec3d pos, vec3d rot, vec3d grav)
{
	stepSize = 30.0f / 1000.0f;
	world = dWorldCreate();
	dWorldSetGravity(world, grav.x, grav.y, grav.z);
	dWorldSetCFM(world, 1e-5);
	dWorldSetERP(world, 0.4);
	contactGroup = dJointGroupCreate(0);
	topLevelSpace = dSimpleSpaceCreate(0);
	iSpaces = new SpaceManager();
	currentSpace = new Space(topLevelSpace);
	iSpaces->Add(currentSpace);
	sceneNode = new Scene();
	sceneNode->camera->setPosition(pos);
	sceneNode->camera->setRotation(rot);

}
void World::getObjectDetails()
{

}

void World::getSpace()
{
	Space* tmp = currentSpace;
	currentSpace = new Space(tmp->iSpace);
}

void World::NextObjectProperty(Object* obj)
{

	Echo = BZK_ParsingTools::GetNextToken(&Datafile);

	if (Echo == size)
	{
		obj->iSize = getVec();
	}

	if (Echo == position)
		obj->iPosition = getVec();

	if (Echo == rotation)
	{
		obj->iRotate = getVec();
		obj->iRotate.x = RAD2DEG(obj->iRotate.x);
		obj->iRotate.y = RAD2DEG(obj->iRotate.y);
		obj->iRotate.z = RAD2DEG(obj->iRotate.z);
	}

	if (Echo == mass)
	{
		obj->iM = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
	}

	if (Echo == material)
		getMaterial(obj);



	if (Echo == type)
	{
		string str = BZK_ParsingTools::GetNextToken(&Datafile);
		if (str == "1")
		{

			obj->MakeGeom(topLevelSpace);
			obj->MakeBody(world);
			obj->LinkBodyWithGeom();
		}
		else
		{
			obj->MakeGeom(topLevelSpace);
		}
	}

	if (Echo == indexData)
	{
		getIndexData();
	}

	if (Echo == vertexData)
	{
		getVertexData();
	}

	if (Echo == uvData)
	{
		getUVData();
	}

	if (Echo == iniTexture)
	{
		getTexture(obj);
	}

}

void World::getCube()
{
	Cube* Cubo = new Cube();
	vec3d v;

	while (Echo != endCube)
	{
		NextObjectProperty(Cubo);
	}


	/*
	std::cout << "Cubo: Indices " << lstInt.TotalItems() << " Vertices " << lstVertex.TotalItems() << " UV " << lstUV.TotalItems() << std::endl;

	//Dados do VertexBuffer Object
	void* vecs = malloc(lstVertex.TotalItems()*sizeof(float));
	memcpy(vecs,&lstVertex[0],lstVertex.TotalItems()*sizeof(float));

	//Dados das Coordendas UV
	void* uvs = malloc(lstUV.TotalItems()*sizeof(float));
	memcpy(uvs,&lstUV[0],lstUV.TotalItems()*sizeof(float));

	//Dados dos indices
	void* indexs = malloc(lstInt.TotalItems()*sizeof(unsigned int));
	memcpy(indexs,&lstInt[0],lstInt.TotalItems()*sizeof(unsigned int));

	Cubo->vbo = new VertexBufferObject();
	Cubo->vbo->glMode = GL_TRIANGLES;

	Cubo->vbo->setVertices(vecs,lstVertex.TotalItems());
	Cubo->vbo->setTexCoords(uvs,lstUV.TotalItems()/2);
	Cubo->vbo->setIndexs(indexs,lstInt.TotalItems());

	Cubo->texture = new Texture("storage/textures/layout_cubo.png");
	free(vecs);
	free(uvs);
	free(indexs);


*/
	currentSpace->addObject(Cubo);
	//delete Cubo;
}

void World::getMesh()
{
	Wavefront* obj = new Wavefront();
	while (Echo != endMesh)
	{
		if (Datafile.eof()) //Memory leak!!
			return;

		NextObjectProperty(obj);


	}

	printf("Mesh Adicionado\n");

	currentSpace->addObject(obj);
}

void World::getSphere()
{
	Sphere* bola = new Sphere(1.0, 24, 24);

	while (Echo != endSphere)
	{
		if (Datafile.eof()) //Memory leak!!
			return;

		NextObjectProperty(bola);

		if (Echo == radius)
		{
			bola->iRadius = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
		}
	}

	currentSpace->addObject(bola);
}

vec3d World::getVec()
{
	vec3d v;
	Echo = BZK_ParsingTools::GetNextToken(&Datafile);
	if (Echo == vec)
	{

		v.x = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
		v.y = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
		v.z = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
	}

	Echo = BZK_ParsingTools::GetNextToken(&Datafile);
	if (Echo == endVec)
		return v;
	else
	{

		v.x = v.y = v.z = 0;
	}
}

void World::getMaterial(Object* obj)
{
	while (Echo != endMaterial)
	{
		vec4d v;
		Echo = BZK_ParsingTools::GetNextToken(&Datafile);
		if (Datafile.eof())
			return;

		if (Echo == ka)
		{
			v = getVec4();
			obj->Mat->Ka[0] = v.x;
			obj->Mat->Ka[1] = v.y;
			obj->Mat->Ka[2] = v.z;
			obj->Mat->Ka[3] = v.w;
		};

		if (Echo == kd)
		{
			v = getVec4();
			obj->Mat->Kd[0] = v.x;
			obj->Mat->Kd[1] = v.y;
			obj->Mat->Kd[2] = v.z;
			obj->Mat->Kd[3] = v.w;

		}

		if (Echo == ks)
		{
			v = getVec4();
			obj->Mat->Ks[0] = v.x;
			obj->Mat->Ks[1] = v.y;
			obj->Mat->Ks[2] = v.z;
			obj->Mat->Ks[3] = v.w;
		}

	}

}

vec4d World::getVec4()
{
	vec4d v;
	Echo = BZK_ParsingTools::GetNextToken(&Datafile);

	if (Echo == vec4)
	{
		v.x = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
		v.y = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
		v.z = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
		v.w = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
		// cout << "x " << v.x << "y " << v.y << "z " << v.z << "w " << v.w << endl;
	}
	return v;
}

void World::getIndexData()
{
	lstInt.EraseAll();
	std::cout << Echo << std::endl;
	while (Echo != endIndexData)
	{
		Echo = BZK_ParsingTools::GetNextToken(&Datafile);
		if (BZK_ParsingTools::IsNumeric(&Echo))
		{
			lstInt.Add((unsigned int)BZK_ParsingTools::GetNumber(Echo));
		}
	}
}

void World::getTexture(Object* obj)
{
	while (Echo != endTexture)
	{
		Echo = BZK_ParsingTools::GetNextToken(&Datafile);
		std::string _name = "storage/textures/"; _name += Echo;
		//std::cout << _name << std::endl;
		obj->texture = assetLib->AddTexture(Echo);
		break;
	}
}
void World::getVertexData()
{
	lstVertex.EraseAll();
	std::cout << Echo << std::endl;
	while (Echo != endVertexData)
	{
		Echo = BZK_ParsingTools::GetNextToken(&Datafile);
		if (BZK_ParsingTools::IsNumeric(&Echo))
		{
			lstVertex.Add(BZK_ParsingTools::GetNumber(Echo));
		}
	}
}

void World::getUVData()
{
	lstUV.EraseAll();
	std::cout << Echo << std::endl;
	while (Echo != endUVData)
	{
		Echo = BZK_ParsingTools::GetNextToken(&Datafile);
		if (BZK_ParsingTools::IsNumeric(&Echo))
		{
			lstUV.Add(BZK_ParsingTools::GetNumber(Echo));
		}
	}
}
void World::Update(float dt)
{

	dWorldStep(world, dt);
	dJointGroupEmpty(contactGroup);

}

void World::Draw()
{
	iSpaces->Draw();
}