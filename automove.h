
#include <iostream>
#include "maze.h"

using namespace std;

struct AM_Stack
{
    AM_Stack();  //���캯��
    int push(coor point);  //��ջ
    coor pop();  //��ջ
    int getLength();  //����
    coor get_top();  //ջ��
    void get_path(int currentx, int currenty, maze m);
    coor *base;  //��ָ��
    coor *top;   //��ָ��
    int length;   //ջ����
};
