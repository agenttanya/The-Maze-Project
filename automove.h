#include <iostream>
#include "maze.h"

using namespace std;

struct AM_Stack
{
<<<<<<< HEAD
    AM_Stack();  //构造函数
    int push(coor point);  //入栈
    coor pop();  //出栈
    int getLength();  //长度
    coor get_top();  //栈顶
=======
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
>>>>>>> parent of cab5276... Revert "Revert "emm""
    coor *base;  //基指针
    coor *top;   //顶指针
    int length;   //栈长度
};
