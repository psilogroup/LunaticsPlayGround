/* Modificações simples para o funcionamento aqui #ifdndef
 * Parte do projeto BZK toolset http://sourceforge.net/projects/bzk
 * Arquivo original http://bzk.svn.sourceforge.net/viewvc/bzk/bzk/Toolkit/BZK_DOMNode.h
 */

#ifndef __BZK_DOMNODE__
#define __BZK_DOMNODE__

# ifdef WIN32
#  include <windows.h>
# endif

#include <string>
#include <iostream>
using namespace std;
class BZK_DOMNode
{
 public:
   ///internal use only. should be encapsulated. marks whenever a node is
   ///well-formed or not.
  bool closed;

  ///defines the type of node
  enum {NAMESPACE,PROPERTY,VALUE,CONTENT,TAG,SPECIAL};
  //////////////// fields /////////////////
 private:

  int iType; /// type of node. See enumeration for types.
  BZK_DOMNode *iNext; /// next sibling
  BZK_DOMNode *iPrev; /// previous sibling
  BZK_DOMNode *iSon; /// internal nodes
  BZK_DOMNode *iFather; /// node's father
  string iName; /// name
  string iNameSpace; /// namespace. In XML is in the form of namespace:name
/**
content of the node.
- for a TAG, its empty. All the content is in a tag attached to it.
- PROPERTY is what helps definig a tag.eg: <tag property="somevalue"/>. in this case, this fields contains "somevalues" without the quotes.
- VALUE seems to be not used anyhwere... @deprecated ?
- CONTENT is the content of a tag. (the tag who owns the content will be its father)
*/

string iContent;
//////////////////// methods ////////////////////
 public:
  ///class constructor
  BZK_DOMNode()
   {
     ///by default, the node is well-formed.
     closed=false;
     ///by default , the content is empty
     iContent="";
     ///and we start with a funny name
     iName="nonametag";
     ///the default namespace is XMLDoc. Its not a problem to stick with this.
     iNameSpace="XMLDoc";
     ///and by default we must have at least one tag to have a valid XML Document
     iType=TAG;
     ///and we set all links to NULL
     iNext=NULL;
     iPrev=NULL;
     iSon=NULL;
     iFather=NULL;
   }


  ////// getters /////////////////////////
  BZK_DOMNode *GetNext(){return iNext;}
  BZK_DOMNode *GetPrev(){return iPrev;}
  BZK_DOMNode *GetSon(){return iSon;}
  BZK_DOMNode *GetFather(){return iFather;}
  int GetType(){return iType;}
  string GetName(){return iName;}
  string GetNameSpace(){return iNameSpace;}
  string GetContent(){return iContent;}
  ///////////////////////////////////////

  ///////////////// setters ////////////////////////////
  void SetContent(string  aContent){iContent=aContent;}
  void SetNameSpace(string  aNameSpace){iNameSpace=aNameSpace;}
  void SetName(string  aName){iName=aName;}
  void SetType(int  aType){iType=aType;}
  void SetNext(BZK_DOMNode * aNext){iNext=aNext;}
  void SetPrev(BZK_DOMNode *aPrev){iPrev=aPrev;}
  void SetSon(BZK_DOMNode * aSon){iSon=aSon;}
  void SetFather(BZK_DOMNode *aFather){iFather=aFather;}

  ///@brief append a son. to the son's list.
  void Append(BZK_DOMNode * aSon)
	      {
		BZK_DOMNode * current=iSon;
		if (iSon==NULL) //if we have no son, this is the first
		  iSon=aSon;
		else
		  {
		    while (current->GetNext()!=NULL) //otherwise, look for the last and append it to the list
		      current=current->GetNext();
		    current->SetNext(aSon);
		  }

	      }
};
#endif
