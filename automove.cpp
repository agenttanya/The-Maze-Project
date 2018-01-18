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

void AM_Stack::get_path(int currentx, int currenty, maze m)
{
    coor end_p {m.width-1,m.height-1};
    for (int i=0;i<=end_p.x;++i)
    for (int j=0;j<=end_p.y;++j){
      m.block_list[i][j].footprint=true;
    }
    coor cp {currentx,currenty};    //记录当前坐标
    push(cp);
    m.block_list[cp.x][cp.y].footprint=false;

    while (true){
        bool footprint=false;
        if (cp.x == end_p.x && cp.y == end_p.y)
            break;
        if (m.block_list[cp.x][cp.y].north==0 && m.block_list[cp.x][cp.y+1].footprint==true)  //向下
        {
            push(coor{cp.x, cp.y+1});
            cp.y +=1 ;
            m.block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
       if (m.block_list[cp.x][cp.y].east==0 && m.block_list[cp.x+1][cp.y].footprint==true)  //向右
        {
            push(coor{cp.x+1, cp.y});
            cp.x +=1 ;
            m.block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
        if (cp.y!=0 && m.block_list[cp.x][cp.y-1].north==0 && m.block_list[cp.x][cp.y-1].footprint==true)  //向上
        {
            push(coor{cp.x, cp.y-1});
            cp.y -=1 ;
            m.block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
       if (cp.x!=0 && m.block_list[cp.x-1][cp.y].east==0 && m.block_list[cp.x-1][cp.y].footprint==true)  //向左
       {
            push(coor{cp.x-1, cp.y});
            cp.x -=1 ;
            m.block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
        if (footprint==false){
          pop();
          cp=get_top();
        }
    }
}
