#include <iostream>
#include "maze.h"

using namespace std;

class AM_Stack
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
  public:
>>>>>>> parent of d414714... 233
    AM_Stack();  //���캯��
    int push(coor point);  //��ջ
    coor pop();  //��ջ
    int getLength();  //����
    coor get_top();  //ջ��
<<<<<<< HEAD
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
=======
    void get_path(int currentx, int currenty, maze m);
    coor get_base(int currentx, int currenty, maze m);
    coor get_first(int currentx, int currenty, maze m);
private:
>>>>>>> parent of d414714... 233
    coor *base;  //��ָ��
    coor *top;   //��ָ��
    int length;   //ջ����
};
