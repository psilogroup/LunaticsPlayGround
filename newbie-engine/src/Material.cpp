#include "Material.h"
#include <stdio.h>

Material::Material()
{
   int i=0;
   //inicializa materiais
   ///TODO: otimizar isto usando memset
   for(i=0;i<=3;i++)
     {
	Ka[i] = Kd[i] = Ks[i] = Ke[i] = 0.0f;	
     }  
}

void Material::Build()
{
  float Sh[] = {10.0f};
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Ka);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Kd);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Ks);
 // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Ke);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,Sh);
}
  
