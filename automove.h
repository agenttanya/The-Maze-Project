
#include <iostream>
#include "maze.h"

using namespace std;

class AM_Stack
{
  public:
    AM_Stack();  //���캯��
    int push(coor point);  //��ջ
    coor pop();  //��ջ
    int getLength();  //����
    coor get_top();  //ջ��
    void get_path(int currentx, int currenty, maze m);
    coor get_base(int currentx, int currenty, maze m);
    coor get_first(int currentx, int currenty, maze m);
private:
    coor *base;  //��ָ��
    coor *top;   //��ָ��
    int length;   //ջ����
};
