#ifndef __XML_TAG__
# define __XML_TAG__

# ifdef WIN32
#  include <windows.h>
# endif

# include <iostream>
# include <fstream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

# include "vec3d.h"
#include "vec4.h"
;
class BZK_XMLTag
{
 public:
   BZK_XMLTag(){};
	 bool doProcess(std::fstream *aFile,void *obj){return false;};
    std::string getTagName(){return "";};
};

class TAGVec3d : public BZK_XMLTag
{
    public:
    	TAGVec3d(){};
        bool doProcess(std::ifstream *aFile,void *v);
        std::string getTagName();
};

class TAGVec4d : public BZK_XMLTag
{
public:
	TAGVec4d(){}
	 bool doProcess (std::ifstream *aFile,void *v);
	std::string getTagName();
};

class TAGPosition : public BZK_XMLTag
{
public:
	TAGPosition(){}
	 bool doProcess (std::ifstream *aFile,void *v);
	std::string getTagName();
};
#endif
