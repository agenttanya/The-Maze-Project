
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
    coor *base;  //��ָ��
    coor *top;   //��ָ��
    int length;   //ջ����
};
