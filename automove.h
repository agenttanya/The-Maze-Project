
#include <iostream>
#include "maze.h"

using namespace std;

struct AM_Stack
{
    AM_Stack();  //构造函数
    int push(coor point);  //入栈
    coor pop();  //出栈
    int getLength();  //长度
    coor get_top();  //栈顶
    void get_path(int currentx, int currenty, maze m);
    coor *base;  //基指针
    coor *top;   //顶指针
    int length;   //栈长度
};
