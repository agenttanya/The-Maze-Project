#ifndef GAMEAREA_H
#define GAMEAREA_H

#include "../Graph_lib/GUI.h"
#include "Vector_ref.h"
#include<string>
#include<iostream>
#include<vector>
#include"maze.h"
using namespace Graph_lib;

const int h {20};
const int w {20};
const char diff {'N'};
const int pgpairs {1};

struct Track
{
  int x{0};
  int y{0};
  string dir{"no direction"};
  Track();
  Track(int xx,int yy, string t):x{xx},y{yy},dir{t}{};
};


//��Ϸ����Game Area����д��
//��������ʵ����Ϸ���ܵģ�Ŀǰ����ʵ�Ǿ���ģʽ����Ϸ����
struct GA {
    Circle ball;
    maze M{w,h,diff,pgpairs};
    Line b1;
    Line b2;
    Vector_ref<Line> l1;
    Vector_ref<Line> l2;
    Vector_ref<Line> l3;
    Vector_ref<Circle> circin;
    Vector_ref<Circle> circout;
    Vector_ref<Text> arrow;
    Text t{Point{100,100},"You make it!"};
    GA();
    vector<Track> trace;
    void ren(int rcox,int rcoy,int z);
    void tracing();
};

#endif
