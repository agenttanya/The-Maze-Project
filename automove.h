#include <iostream>
#include "maze.h"

using namespace std;

class AM_Stack
{
  public:
    AM_Stack();
    int push(coor point);  //��ջ
    coor pop();  //��ջ
    int getLength();  //����
    coor getTop();  //ջ��
    void get_path();
    void print_full();
    void print_first();
private:
    coor *base;  //��ָ��
    coor *top;   //��ָ��
    int length;   //ջ����
};
