#include "gamearea.h"
#include"gamewindow.h"
#include<iostream>
#include<algorithm>
using namespace Graph_lib;

/*
void GA::tracing(){
for(int i=0; i<trace.size();++i)
    { if(trace[i].dir=="right")
          {  l3.push_back(new Line{Point{x0+(trace[i].x)*d,y0+(trace[i].y+0.5)*d},Point{x0+(trace[i].x-1)*d,y0+(trace[i].y+0.5)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Text{Point{x0+(trace[i].x-0.5)*d,y0+(trace[i].y+0.5)*d},">"});
             arrow[arrow.size()-1].set_color(Color::dark_blue); }
      else if(trace[i].dir=="left")
          {  l3.push_back(new Line{Point{x0+(trace[i].x+1)*d,y0+(trace[i].y+0.5)*d},Point{x0+(trace[i].x+2)*d,y0+(trace[i].y+0.5)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Text{Point{x0+(trace[i].x+1.5)*d,y0+(trace[i].y+0.5)*d},"<"});
             arrow[arrow.size()-1].set_color(Color::dark_blue); }
      else if(trace[i].dir=="down")
          {  l3.push_back(new Line{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y)*d},Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y-1)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Text{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y-0.5)*d},"v"});
             arrow[arrow.size()-1].set_color(Color::dark_blue); }
      else if(trace[i].dir=="up")
          {  l3.push_back(new Line{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y+1)*d},Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y+2)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Text{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y+1.5*d)*d},"^"});
             arrow[arrow.size()-1].set_color(Color::dark_blue); }
    }
}
*/

//����ǽ�ĳ���λ�úͷ�������ʵ�line
Line* LineCalc (int i,int j,int x ,int y,bool vertical){
    if (vertical) {
        return new Line { Point { CenterX + ( i - x + 0.5 ) * WallWidth , CenterY + (j - y - 0.5) * WallWidth } , Point { CenterX + ( i - x + 0.5 ) * WallWidth , CenterY + ( j - y + 0.5) * WallWidth } };
    } else {
        return new Line { Point { CenterX + ( i - x - 0.5 ) * WallWidth , CenterY + (j - y + 0.5) * WallWidth } , Point { CenterX + ( i - x + 0.5 ) * WallWidth , CenterY + ( j - y + 0.5) * WallWidth } };
    }
}

//ren ����renewal�������������ʵ���߶μ��ĸ��£��ڹ��캯��������ʾ��������ĺ���spar�ж��õ��ˡ���by KYA)
void GC::renewal(int rcox,int rcoy)

  {
     for (int i = max( rcox - VisibleRadius , 0 ) ; i <= min( rcox + VisibleRadius , M.width-1 ) ; ++i ){
        for (int j = max( rcoy - VisibleRadius , 0 ) ; j <= min( rcoy + VisibleRadius , M.height-1 ) ; ++j ) {
            if ( M.block_list[i][j].east == 1 ){
              l1.push_back( LineCalc( i , j , rcox , rcoy , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
              }

            if (M.block_list[i][j].north==1){
              l2.push_back( LineCalc( i , j , rcox , rcoy , 0) );
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }

            if ( i == 0 ) {
              l1.push_back( LineCalc( i - 1 , j , rcox , rcoy , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
            if ( j == 0 ) {
                l2.push_back( LineCalc( i , j - 1 , rcox , rcoy , 0) );
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
    renewal(0,0);
}

void GT::renewal(int rcox,int rcoy)

  {
     for (int i = max( rcox - VisibleRadius , 0 ) ; i <= min( rcox + VisibleRadius , M.width-1 ) ; ++i ){
        for (int j = max( rcoy - VisibleRadius , 0 ) ; j <= min( rcoy + VisibleRadius , M.height-1 ) ; ++j ) {
            if ( M.block_list[i][j].east == 1 ){
              l1.push_back( LineCalc( i , j , rcox , rcoy , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
              }

            if (M.block_list[i][j].north==1){
              l2.push_back( LineCalc( i , j , rcox , rcoy , 0) );
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }

            if ( i == 0 ) {
              l1.push_back( LineCalc( i - 1 , j , rcox , rcoy , 1) );
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
            if ( j == 0 ) {
                l2.push_back( LineCalc( i , j - 1 , rcox , rcoy , 0) );
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
           for (int k=0; k<M.PG_list.size(); ++k){
           if((M.PG_list[k].pg1corx == i && M.PG_list[k].pg1cory == j) || (M.PG_list[k].pg2corx == i && M.PG_list[k].pg2cory == j)){
                circin.push_back(new Circle { Point { CenterX + ( i - rcox ) * WallWidth , CenterY + ( j - rcoy ) * WallWidth} , pgradius1 } );
                circin[circin.size()-1].set_color(Color::blue);//��Ϊʵ��Բ�ᵲסС���������˿���Բ
                circout.push_back(new  Circle { Point { CenterX + ( i - rcox ) * WallWidth , CenterY + ( j - rcoy ) * WallWidth} , pgradius2 } );
                circout[circout.size()-1].set_color(Color::blue);
                }
           }
        }
}
}

GT::GT():
    ball{ Point { CenterX , CenterY } , BallWidth }
{
    ball.set_style(Line_style{Line_style::solid, 1});
    ball.set_fill_color(Color::red);
    ball.set_color(Color::red);
    renewal(0,0);
}
