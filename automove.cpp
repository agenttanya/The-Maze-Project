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
    for (int i = 0; i<m.width; i++)
        for (int j = 0; j<m.height; j++)
        {
          m.block_list[i][j].moved = true;
        }

    coor start_p{currentx,currenty};  //��ʼ���꣨��ڣ�
    coor end_p{m.width-1, m.height-1};    //�������꣨���ڣ�

    AM_Stack AM_Path;
    AM_Path.push(start_p);

    coor cp=start_p;    //��¼��ǰ����
    while (true)
    {
        if (cp.x == end_p.x && cp.y == end_p.y)
            break;
        if (m.block_list[cp.x][cp.y].north==0 && m.block_list[cp.x][cp.y+1].moved)  //����
        {
            m.block_list[cp.x][cp.y+1].moved = false;
            AM_Path.push(coor{cp.x, cp.y+1});
            cp.y +=1 ;
            continue;
        }
       if (m.block_list[cp.x][cp.y].east==0 && m.block_list[cp.x+1][cp.y].moved)  //����
        {
            m.block_list[cp.x+1][cp.y].moved = false;
            AM_Path.push(coor{cp.x+1, cp.y});
            cp.x +=1 ;
            continue;
        }
        if (m.block_list[cp.x][cp.y-1].north==0 && m.block_list[cp.x][cp.y-1].moved)  //����
        {
            m.block_list[cp.x][cp.y-1].moved = false;
            AM_Path.push(coor{cp.x, cp.y-1});
            cp.y -=1 ;
            continue;
        }
       if (m.block_list[cp.x-1][cp.y].east==0 && m.block_list[cp.x-1][cp.y].moved)  //����
        {
            m.block_list[cp.x-1][cp.y].moved = false;
            AM_Path.push(coor{cp.x-1, cp.y});
            cp.x -=1 ;
            continue;
        }
        AM_Path.pop();
        cp = AM_Path.getTop();
    }
}

void AM_Stack::print_full()
{

    coor *p = base;
    while (p != NULL)
    {
        cout << "(" << p->x << "," << p->y << ")" << endl;
        p = p->next;
    }

}

coor AM_Stack::get_base(int currentx, int currenty, maze m)
{
   get_path(currentx, currenty, m);
   coor *p = base;
   return *p;
}

coor AM_Stack::get_first(int currentx, int currenty, maze m)
{
   get_path(currentx, currenty, m);
   coor *p1 = base;
   coor *p2 =NULL;
   p2 = p1->next;
   return *p2;
}
