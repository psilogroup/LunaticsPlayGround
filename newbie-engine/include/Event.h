#ifndef __EVENT__
#define __EVENT__

# ifdef WIN32
#  include <windows.h>
# endif
#include <SDL2/SDL.h>
#include "BZK_List.h"

typedef enum EventType {Keyboard,Mouse,Joystick};
typedef enum KeyBoardEventType {KeyUp,KeyDown};
typedef enum MouseEventType {Motion,ButtonClick};

typedef void EventFn (void *p);

class Event
{
public:
    EventType type;
    EventFn *fn;
};


class MouseEvent : public Event
{
    MouseEventType subType;
    int x;
    int y;
    void setMotion(int _x,int _y)
    {
        x = _x;
        y = _y;
    }
};

class KeyBoardEvent: public Event
{
public:
    KeyBoardEventType subType;
    SDL_Keysym key;
    void setKey(SDL_Keysym k)
    {
        key = k;
    };
};




class EventManager
{
public:
    BZK_List<KeyBoardEvent> KeyUpEvents;
    BZK_List<KeyBoardEvent> KeyDownEvents;
    BZK_List<Event> mouseEvents;


    EventManager()
    {

    };

    void addKeyBoadEvent(KeyBoardEvent event)
    {


        switch(event.subType)
        {
            case KeyUp:
                KeyUpEvents.Add(event);
                break;
            case KeyDown:
                KeyDownEvents.Add(event);
                break;
        }

    };

    void processEvents()
    {
        int i = 0;

        for(i = 0;i<KeyUpEvents.TotalItems();i++)
        {
            KeyBoardEvent kb =  KeyUpEvents[i];

//            (*kb.fn) ((void*)kb.key);
        }

        for(i = 0;i<KeyDownEvents.TotalItems();i++)
        {
            KeyBoardEvent kb =  KeyDownEvents[i];

     //       (*kb.fn) ((void*)kb.key);
        }

        KeyDownEvents.EraseAll();
        KeyUpEvents.EraseAll();

    }

};



#endif
