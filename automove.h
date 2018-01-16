#include <iostream>
#include "maze.h"

using namespace std;

class AM_Stack
{
  public:
    AM_Stack();
    int push(coor point);  //入栈
    coor pop();  //出栈
    int getLength();  //长度
    coor getTop();  //栈顶
    void get_path();
    void print_full();
    void print_first();
private:
    coor *base;  //基指针
    coor *top;   //顶指针
    int length;   //栈长度
};
