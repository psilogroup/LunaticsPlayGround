#include "BZK_XMLTag.h"
#include "BZK_ParsingTools.h"
# include <iostream>
# include <fstream>
#include <string>
#include <sstream>

bool
TAGVec3d::doProcess(std::ifstream *aFile, void* v)
{
  vec3d *p = (vec3d *) v;
  p->x = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(aFile));
  p->y = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(aFile));
  p->z = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(aFile));
  return true;

}

string
TAGVec3d::getTagName()
{
  return "Vec";
}

bool
TAGVec4d::doProcess(std::ifstream *aFile, void* v)
{
  vec4d *p = (vec4d *) v;
  p->x = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(aFile));
  p->y = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(aFile));
  p->z = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(aFile));
  p->w = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(aFile));
  return true;
}

string
TAGVec4d::getTagName()
{
  return "Vec4";
}

bool
TAGPosition::doProcess(std::ifstream *aFile, void *v)
{

  std::string token = BZK_ParsingTools::GetNextToken(aFile);
  std::string tagName = BZK_ParsingTools::GetTagName(token);
   if (tagName == "Vec")
     {
       TAGVec3d *child = new TAGVec3d();
       child->doProcess(aFile,v);
       vec3d *tmp = (vec3d *)v;
       std::cout << " X : " << tmp->x << " Y : " << tmp->y << " Z : " << tmp->z << std::endl;
     }
   return true;
}

std::string
TAGPosition::getTagName()
{
 return "Position";
}

