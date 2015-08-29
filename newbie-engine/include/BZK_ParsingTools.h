#ifndef __BZK_PARSINGTOOLS__
# define __BZK_PARSINGTOOLS__

# ifdef WIN32
#  include <windows.h>
# endif

# include <iostream>
# include <fstream>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <math.h>
using namespace std;

/**
@brief class for general purpose parsing.
@author Daniel Monteiro and Carlos Muniz

*/

class BZK_ParsingTools
{

public:
 ///@brief test string for a substring, returning true or false.
  static bool Contains(string aSource,string aSub)
  {
    int sizesub=aSub.length();
    for (int c=0;c<aSource.length()-sizesub+1;c++)
	if (aSub==aSource.substr(c,sizesub))
	  return true;
    return false;
  }
///@brief returns the position of a given character in a string
static
int
  GetTokenDivider(std::string Father,std::string Separator)
{
  int pos1=0;

     while ((Father.substr(pos1,1)!=Separator)&&(pos1!=Father.length())) pos1++;
     return pos1;
}

///deprecated
static
bool
IsNumeric(std::string *Token)
{
  char**endptr=(char**)malloc(1);
  bool logical;
  int number=strtol(Token->c_str(),endptr,10);
  logical=!((!strcmp(Token->c_str(),*endptr))&&(number==0));
  delete endptr;
  return logical;
}

///@brief extracts the number contained in a string and returns as a math unit
static
float
GetNumber(std::string Token)
{
  if (Token==""||Token==" ") return 0;

	float number;
	std::istringstream ss(Token);
	ss >> number;
  return number;
}

///@deprecated
///@brief should be deleted. Use BZK_XMLReader instead
static
bool
IsTag(std::string *Token)
{
  std::string symbol("<");
  std::string symbol2(">");

  if ((Token->substr(0,1)==symbol)&&(Token->substr(Token->length()-1,1)==symbol2))
    return true;
  return false;
}

///@deprecated
///@brief should be deleted. Use BZK_XMLReader instead

static
bool
IsCloseTag(std::string *Token)
{
  std::string symbol3("/");

       if (Token->substr(1,1)==symbol3)
	 return true;
 return false;
}



///@brief retrieve the next token from a file stream
static
std::string
GetNextToken(std::ifstream *Datafile)
{
  // if (Datafile.eof()) throw ERR_END_OF_FILE
  //  std::string *Token=new std::string();
  std::string Token;
  *Datafile >> Token;
  return Token;
}

///@brief get the substring of a string, all the way before a separator
static
std::string
GetStringUntilSep(std::string aString,string aSeparator)
{
return aString.substr(0,GetTokenDivider(aString,aSeparator));
}

///@brief get the substring of a string, all the way after a separator
static
std::string
GetStringFromSep(std::string aString,string aSeparator)
{
  //+1 to skip the separator
return aString.substr(GetTokenDivider(aString,aSeparator)+1,aString.length());
}


///@brief get the n-esimal substring from a bigger string, separated by white spaces
static
std::string
GetSubToken(std::string aFather,int aWhere)
{


  std::string Father=TrimToken(aFather);



  if (Father=="") return "";

  if (aWhere==0)
    	return Father.substr(0,GetTokenDivider(Father," "));
    else
    {
      	//if (GetTokenDivider(Father," ")==strlen(Father.c_str()))  return "";
      	return GetSubToken(Father.substr(GetTokenDivider(Father," "),Father.length()),aWhere-1);
    }
}

///@brief trim token - eliminate whitespaces from the beggining and the end of a string,BUT NOT IN THE MIDDLE
static
std::string
TrimToken(std::string Father)
{
   if (((Father)!="")&&((Father)!=" "))
    {
      int pos1=0;
      int pos2=Father.length();
      while ((Father[pos1]==' ')&&(pos1!=(Father.length()))) pos1++;
      while ((Father[pos2]==' ')&&(pos2!=pos1)) pos2--;
      return Father.substr(pos1,pos2-pos1); //mexi nisso...e deu certo  delete newstring;
    }
   else
     return "";

}

///@deprecated
///@brief should be deleted. Use BZK_XMLReader instead
static
std::string
GetTagName(std::string &Father)
{
  int pos1=1;
  int pos2=Father.length()-2;
  if (IsCloseTag(&Father)) pos1=2;
  return Father.substr(pos1,pos2-pos1+1);
}


///@brief convert all the string to lower case
 static std::string
  toLowerCase(std::string &aOriginal)
{
  std::string newstring;
  for (int c=0;c<aOriginal.length();c++)
    if (aOriginal[c]>65 && aOriginal[c]<90 )
      newstring+=aOriginal[c]+32;
    else
      newstring+=aOriginal[c];
  return newstring;
}

///@brief convert all the string to upper case
 static std::string
  toHighCase(std::string &aOriginal)
{
  std::string newstring;
  for (int c=0;c<aOriginal.length();c++)
    if (aOriginal[c]>97 && aOriginal[c]<122)
      newstring+=aOriginal[c]-32;
    else
      newstring+=aOriginal[c];
  return newstring;
}

///@brief decode a char to its hexadecimal meaning
static int
   DecodeHexStr(char aOriginal)
{
  if (aOriginal>=65)
    return aOriginal-65+10;
  else return aOriginal-48;
}

///@brief decode a full string of hexa chars
 static int
   DecodeHexStr(std::string &aOriginal)
 {
   string unified= toHighCase(aOriginal);
   int currentDigit;
   int power=0;
   int pos=aOriginal.length()-1;
   int result=0;
   while (pos!=-1)
     {
       currentDigit=DecodeHexStr(unified[pos])*pow(16.0,(double)power);
       power++;
       pos--;
       result+=currentDigit;
     }
   /*
    	  Steps:

   1. Get the last digit of the hex number, call this digit the currentDigit.
   2. Make a variable, let's call it power.  Set the value to 0.
   3. Multiply the current digit with (16^power), store the result.
   4. Increment power by 1.
   5. Set the the currentDigit to the previous digit of the hex number.
   6. Repeat from step 3 until all digits have been multiplied.
   7. Sum the result of step 3 to get the answer number.

    */
   return result;
 }

};


#endif
