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

struct Track
{
  int x{0};
  int y{0};
  string dir{"no direction"};
  Track();
  Track(int xx,int yy, string t):x{xx},y{yy},dir{t}{};
};


//游戏区域（Game Area的缩写）
//它是用于实现游戏功能的，目前它其实是经典模式的游戏区域
struct GA {
    Graph_lib::Circle ball;
    maze M{w,h,diff};
    Graph_lib::Line b1;
    Graph_lib::Line b2;
    Graph_lib::Vector_ref<Graph_lib::Line> l1;
    Graph_lib::Vector_ref<Graph_lib::Line> l2;
    Graph_lib::Vector_ref<Graph_lib::Line> l3;
    Graph_lib::Vector_ref<Graph_lib::Text> arrow;
    Graph_lib::Text t{Point{100,100},"You make it!"};
    GA();
    vector<Track> trace;
    void ren(Graph_lib::Vector_ref<Graph_lib::Line>&l1,Graph_lib::Vector_ref<Graph_lib::Line>&l2, int rcox,int rcoy,int z);
    void tracing();
};

#endif
