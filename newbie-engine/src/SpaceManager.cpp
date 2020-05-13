#include "SpaceManager.h"

SpaceManager::SpaceManager()
{
   
}

void SpaceManager::Add(Space *s)
{
   iSpaces.Add(s);
};

void SpaceManager::Update()
{
   int i;
   for (i=0;i<iSpaces.TotalItems();i++)
     {
	iSpaces[i]->Update();
     }
}

void SpaceManager::Draw()
{
   int i;
   for (i=0;i<iSpaces.TotalItems();i++)
     {
	  iSpaces[i]->Draw();
     }
}
