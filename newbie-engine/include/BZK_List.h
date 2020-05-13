#ifndef __BZK_LIST__
#define __BZK_LIST__


#include <windows.h>


#include <vector>
#include <SDL.h>
template <class T>
class BZK_List
{
  std::vector<T> *_list;
 public:
  BZK_List()
    {
      _list=new std::vector<T>;
    }
  T& operator[](Uint32 aIndex)
    {
      return (*_list)[aIndex % TotalItems() ];
    }
  Uint32 Add(T aItem)
    {
      _list->push_back(aItem);
      return _list->size();
    }

  void EraseAll()
    {
      _list->clear();

    }
  long TotalItems()
    {
      return _list->size();
    }

  ~BZK_List()
    {
      delete _list;
    }


};
#endif
