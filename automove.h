#include <iostream>
#include "maze.h"

using namespace std;

struct AM_Stack
{
<<<<<<< HEAD
    AM_Stack();  //���캯��
    int push(coor point);  //��ջ
    coor pop();  //��ջ
    int getLength();  //����
    coor get_top();  //ջ��
=======
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
>>>>>>> parent of cab5276... Revert "Revert "emm""
    coor *base;  //��ָ��
    coor *top;   //��ָ��
    int length;   //ջ����
};
