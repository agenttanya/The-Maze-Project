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

const int pgradius1 {5};//内半径
const int pgradius2 {7};//外半径

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

//游戏区域（Game Area的缩写）
//它是用于实现游戏功能的，目前它其实是经典模式的游戏区域
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
