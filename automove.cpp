#include <iostream>
#include "automove.h"
#include "maze.h"

using namespace std;

AM_Stack::AM_Stack()
{
    length = 0;
    base = NULL;
    top = NULL;
}

int AM_Stack::push(coor point)
{
    coor *mpNode = new coor();
    *mpNode = point;
    if (length == 0)
        top = base = mpNode;
    else
    {
        top->next = mpNode;
        top = mpNode;
    }
    return ++length;
}

coor AM_Stack::get_top()
{
    return *top;
}

coor AM_Stack::pop()
{
    coor retPoint = *top;
    top = base;
    while (top->next != NULL)
    {
        if (top->next->next == NULL)
        {
            delete(top->next);
            top->next = NULL;
            break;
        }
        top = top->next;
    }
    if (length == 1)
    {
        delete(base);
        base = top = NULL;
    }
    length--;
    return retPoint;
}

int AM_Stack::getLength()
{
    return length;
}

