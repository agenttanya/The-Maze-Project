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

coor AM_Stack::getTop()
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

<<<<<<< HEAD
=======
void AM_Stack::print_full()
{
    coor *p = base;
    while (p != NULL)
    {
        cout << "(" << p->x << "," << p->y << ")" << endl;
        p = p->next;
    }

}

void AM_Stack::print_first()
{
   coor*p = base;
   cout << "(" << p->x << "," << p->y << ")" << endl;
}

////////////////////////////////////////////////////////////////////

int main()
{
    maze tm(10,10,'E',0);
    for (int i = 0; i<10; i++)
        for (int j = 0; j<10; j++)
        {
          tm.block_list[i][j].moved = true;
        }

    coor start_p{0,0};  //初始坐标（入口）
    coor end_p{9,9};    //结束坐标（出口）

    AM_Stack AM_Path;
    AM_Path.push(start_p);

    coor cp=start_p;    //记录当前坐标
    while (true)
    {
        if (cp.x == end_p.x && cp.y == end_p.y)
            break;
        if (tm.block_list[cp.x][cp.y].north==0 && tm.block_list[cp.x][cp.y+1].moved)  //向下
        {
            tm.block_list[cp.x][cp.y+1].moved = false;
            AM_Path.push(coor{cp.x, cp.y+1});
            cp.y +=1 ;
            continue;
        }
       if (tm.block_list[cp.x][cp.y].east==0 && tm.block_list[cp.x+1][cp.y].moved)  //向右
        {
            tm.block_list[cp.x+1][cp.y].moved = false;
            AM_Path.push(coor{cp.x+1, cp.y});
            cp.x +=1 ;
            continue;
        }
        if (tm.block_list[cp.x][cp.y-1].north==0 && tm.block_list[cp.x][cp.y-1].moved)  //向上
        {
            tm.block_list[cp.x][cp.y-1].moved = false;
            AM_Path.push(coor{cp.x, cp.y-1});
            cp.y -=1 ;
            continue;
        }
       if (tm.block_list[cp.x-1][cp.y].east==0 && tm.block_list[cp.x-1][cp.y].moved)  //向左
        {
            tm.block_list[cp.x-1][cp.y].moved = false;
            AM_Path.push(coor{cp.x-1, cp.y});
            cp.x -=1 ;
            continue;
        }
        AM_Path.pop();
        cp = AM_Path.getTop();
    }
  AM_Path.print_full();
  return 0;
}
>>>>>>> parent of cab5276... Revert "Revert "emm""
