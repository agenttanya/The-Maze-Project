#ifndef GAMEAREA_H
#define GAMEAREA_H

#include "../Graph_lib/GUI.h"
#include "Vector_ref.h"
#include<string>
#include<iostream>
#include<vector>
#include"maze.h"
#include "time.h"
using namespace Graph_lib;

const int height {10};
const int width {10};
const char diff {'E'};
const int pgpairs {20};

const int pgradius1 {5};//�ڰ뾶
const int pgradius2 {7};//��뾶

const std::string hint {"Hints run out!"};

/*
struct Track
{
  int x{0};
  int y{0};
  string dir{"no direction"};
  Track();
  Track(int xx,int yy, string t):x{xx},y{yy},dir{t}{};
};
*/

//��Ϸ����Game Area����д��
//��������ʵ����Ϸ���ܵģ�Ŀǰ����ʵ�Ǿ���ģʽ����Ϸ����
struct GC {
    Circle ball;
    int corrx{0};
    int corry{0};
    int chances {0};
    maze* M {nullptr};
    Initialize(int w,int d,char diff);
    Time t0 {0};
    Vector_ref<Line> l1;
    Vector_ref<Line> l2;
    //Vector_ref<Line> l3;
    Vector_ref<Text> arrow;
    GC();
    ~GC(){delete M;}
    //vector<Track> trace;
    void renewal();
    //void tracing();
    std::string get_coor ();
};

//Game Transfer
struct GT {
    Circle ball;
    int corrx{0};
    int corry{0};
    maze* M {nullptr};
    Time t0 {0};
    Vector_ref<Line> l1;
    Vector_ref<Line> l2;
    //Vector_ref<Line> l3;
    Vector_ref<Circle> circin;
    Vector_ref<Circle> circout;
    //Vector_ref<Text> arrow;
    GT();
    ~GT(){delete M;}
    Initialize(int w,int d,char diff, int pgpairs);
    //vector<Track> trace;
    void renewal();
    //void tracing();
    std::string get_coor ();
};


#endif
