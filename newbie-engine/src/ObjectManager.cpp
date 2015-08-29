#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
  // iActors = new std::vector<Object>;
};

void ObjectManager::add(Object *o)
{
   iActors.Add(o);
}

int ObjectManager::totalObjects()
{
   return iActors.TotalItems();
}

void ObjectManager::Erase()
{
   iActors.EraseAll();
}

void ObjectManager::Update()
{
   int i;
   for(i=0;i<totalObjects();i++)
     {
	iActors[i]->Update();
//	printf("x\n");
     }
}

void ObjectManager::Draw()
{
   int i;
   for(i=0;i<totalObjects();i++)
     {
	iActors[i]->Draw();
//	printf("z\n");
     }
}
