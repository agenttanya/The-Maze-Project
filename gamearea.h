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

const int height {20};
const int width {20};
const char diff {'E'};
const int pgpairs {1};

const int pgradius1 {5};//�ڰ뾶
const int pgradius2 {7};//��뾶

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
struct GA {
    Circle ball;
    maze M{width,height,diff,pgpairs};
    Time t0{0,width*height/400,0};
    Vector_ref<Line> l1;
    Vector_ref<Line> l2;
    //Vector_ref<Line> l3;
    Vector_ref<Circle> circin;
    Vector_ref<Circle> circout;
    //Vector_ref<Text> arrow;
    Text t{Point{100,100},"You make it!"};
    Text e{Point{30,40},t0.timeline};
    GA();
    //vector<Track> trace;
    void renewal(int rcox,int rcoy);
    //void tracing();
};


#endif
