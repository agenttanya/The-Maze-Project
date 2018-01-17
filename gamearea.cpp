#include "gamearea.h"
#include"gamewindow.h"
#include<iostream>
#include<algorithm>
using namespace Graph_lib;


//根据墙的抽象位置和方向构造合适的line
Line* LineCalc (int i,int j,int x ,int y,bool vertical){
    if (vertical) {
        return new Line { Point { CenterX + ( i - x + 0.5 ) * WallWidth , CenterY + (j - y - 0.5) * WallWidth } , Point { CenterX + ( i - x + 0.5 ) * WallWidth , CenterY + ( j - y + 0.5) * WallWidth } };
    } else {
        return new Line { Point { CenterX + ( i - x - 0.5 ) * WallWidth , CenterY + (j - y + 0.5) * WallWidth } , Point { CenterX + ( i - x + 0.5 ) * WallWidth , CenterY + ( j - y + 0.5) * WallWidth } };
    }
}

//ren 就是renewal，这个函数用来实现线段集的更新，在构造函数，和显示部分区域的函数spar中都用到了。（by KYA)
void GC::renewal()

  {
     for (int i = max( corrx - VisibleRadius , 0 ) ; i <= min( corrx + VisibleRadius , M->width-1 ) ; ++i ){
        for (int j = max( corry - VisibleRadius , 0 ) ; j <= min( corry + VisibleRadius , M->height-1 ) ; ++j ) {
            if ( M->block_list[i][j].east == 1 ){
              l1.push_back( LineCalc( i , j , corrx , corry , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
              }

            if (M->block_list[i][j].north==1){
              l2.push_back( LineCalc( i , j , corrx , corry , 0) );
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }

            if ( i == 0 ) {
              l1.push_back( LineCalc( i - 1 , j , corrx , corry , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
            if ( j == 0 ) {
                l2.push_back( LineCalc( i , j - 1 , corrx , corry , 0) );
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
        }
}
}

GC::GC():
    ball{ Point { CenterX , CenterY } , BallWidth }
{
    ball.set_style(Line_style{Line_style::solid, 1});
    ball.set_fill_color(Color::red);
    ball.set_color(Color::red);
}

GC::Initialize(int w, int h, char diff) {
    t0=Time(w*h/5);
    e.set_label(t0.timeline);
    l1.erase();
    l2.erase();
    corrx=0;
    corry=0;
    if (M!=nullptr) {
        delete M;
        M=nullptr;
    }
    M=new maze(w,h,diff);
}

void GT::renewal()

  {
     for (int i = max( corrx - VisibleRadius , 0 ) ; i <= min( corrx + VisibleRadius , M->width-1 ) ; ++i ){
        for (int j = max( corry - VisibleRadius , 0 ) ; j <= min( corry + VisibleRadius , M->height-1 ) ; ++j ) {
            if ( M->block_list[i][j].east == 1 ){
              l1.push_back( LineCalc( i , j , corrx , corry , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
              }

            if (M->block_list[i][j].north==1){
              l2.push_back( LineCalc( i , j , corrx , corry , 0) );
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }

            if ( i == 0 ) {
              l1.push_back( LineCalc( i - 1 , j , corrx , corry , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
            if ( j == 0 ) {
                l2.push_back( LineCalc( i , j - 1 , corrx , corry , 0) );
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
           for (int k=0; k<M->PG_list.size(); ++k){
           if((M->PG_list[k].pg1corx == i && M->PG_list[k].pg1cory == j) || (M->PG_list[k].pg2corx == i && M->PG_list[k].pg2cory == j)){
                circin.push_back(new Circle { Point { CenterX + ( i - corrx ) * WallWidth , CenterY + ( j - corry ) * WallWidth} , pgradius1 } );
                circin[circin.size()-1].set_color(Color::blue);//因为实心圆会挡住小球所以用了空心圆
                circout.push_back(new  Circle { Point { CenterX + ( i - corrx ) * WallWidth , CenterY + ( j - corry ) * WallWidth} , pgradius2 } );
                circout[circout.size()-1].set_color(Color::blue);
                }
           }
        }
}
}

GT::Initialize(int w, int h, char diff, int pgpairs) {
    t0=Time((pgpairs+1)*w*h/5);
    e.set_label(t0.timeline);
    l1.erase();
    l2.erase();
    circin.erase();
    circout.erase();
    corrx=0;
    corry=0;
    if (M!=nullptr) {
        delete M;
        M=nullptr;
    }
    M=new maze(w,h,diff,pgpairs);
}

GT::GT():
    ball{ Point { CenterX , CenterY } , BallWidth }
{
    ball.set_style(Line_style{Line_style::solid, 1});
    ball.set_fill_color(Color::red);
    ball.set_color(Color::red);
}
