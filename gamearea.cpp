#include "gamearea.h"
#include"gamewindow.h"
#include<iostream>

void GA::tracing(){
for(int i=0; i<trace.size();++i)
    { if(trace[i].dir=="right")
          {  l3.push_back(new Graph_lib::Line{Point{x0+(trace[i].x)*d,y0+(trace[i].y+0.5)*d},Point{x0+(trace[i].x-1)*d,y0+(trace[i].y+0.5)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Graph_lib::Text{Point{x0+(trace[i].x-0.5)*d,y0+(trace[i].y+0.5)*d},">"});
              arrow[arrow.size()-1].set_color(Color::dark_blue); }
      else if(trace[i].dir=="left")
          {  l3.push_back(new Graph_lib::Line{Point{x0+(trace[i].x+1)*d,y0+(trace[i].y+0.5)*d},Point{x0+(trace[i].x+2)*d,y0+(trace[i].y+0.5)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Graph_lib::Text{Point{x0+(trace[i].x+1.5)*d,y0+(trace[i].y+0.5)*d},"<"});
             arrow[arrow.size()-1].set_color(Color::dark_blue); }
      else if(trace[i].dir=="down")
          {  l3.push_back(new Graph_lib::Line{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y)*d},Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y-1)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Graph_lib::Text{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y-0.5)*d},"v"});
             arrow[arrow.size()-1].set_color(Color::dark_blue); }
      else if(trace[i].dir=="up")
          {  l3.push_back(new Graph_lib::Line{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y+1)*d},Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y+2)*d}});
             l3[l3.size()-1].set_style(Line_style{Line_style::solid, 1});
             l3[l3.size()-1].set_color(Color::dark_blue);
             arrow.push_back(new Graph_lib::Text{Point{x0+(trace[i].x+0.5)*d,y0+(trace[i].y+1.5*d)*d},"^"});
             arrow[arrow.size()-1].set_color(Color::dark_blue); }
    }
}


//ren 就是renewal，这个函数用来实现线段集的更新，在构造函数，和显示部分区域的函数spar中都用到了。（by KYA)
void GA::ren(Graph_lib::Vector_ref<Graph_lib::Line>&l1,Graph_lib::Vector_ref<Graph_lib::Line>&l2, int rcox,int rcoy,int z)
{       int wallse{0};
        int wallsn{0};
    // find the coordinates of the walls.
        for (int i=0;i<M.width;++i){
        for (int j=0; j<M.height;++j){
            if (M.block_list[i][j].east==1 && (i!=M.width-1||j!=M.height-1)){
              wallse += 1 ;
              if(M.pass_gate1==wallse-1||M.pass_gate2==wallse-1){
               if (M.pass_gate1 == wallse-1){
                M.pg1east = true;
                M.pg1corx = i;
                M.pg1cory = j;
               }
               else{
                M.pg2east = true;
                M.pg2corx = i;
                M.pg2cory = j;
               }
             }
            }
            if (M.block_list[i][j].north==1){
              wallsn += 1;
              if(M.pass_gate1-M.num_walls0+1==wallsn-1||M.pass_gate2-M.num_walls0+1==wallsn-1){
               if (M.pass_gate1-M.num_walls0+1 == wallsn-1){
                M.pg1corx = i;
                M.pg1cory = j;
               }
               else {
                M.pg2corx = i;
                M.pg2cory = j;
               }
              }
            }
           }
          }
     for (int i=rcox;i<rcox+z;++i){
        for (int j=rcoy;j<rcoy+z;++j) {
            if (M.block_list[i][j].east==1){
              l1.push_back(new Graph_lib::Line{Point{x0+(i+1)*d,y0+d*j},Point{x0+d*(i+1),y0+d*(j+1)}});
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
              if ( (i == M.pg1corx && j == M.pg1cory && M.pg1east )|| (i == M.pg2corx && j == M.pg2cory && M.pg2east)) l1[l1.size()-1].set_color(Color::red);
              }

            if (M.block_list[i][j].north==1){
              l2.push_back(new Graph_lib::Line{Point{x0+(i+1)*d,y0+(j+1)*d},Point{x0+d*i,y0+d*(j+1)}});
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
              if ( (i == M.pg1corx && j == M.pg1cory && !M.pg1east )|| (i == M.pg2corx && j == M.pg2cory && !M.pg2east)) l2[l2.size()-1].set_color(Color::red);
            }
        }
}
}

GA::GA():
    ball{Point{x0+d/2,y0+d/2}, ball_d},
    b1 {Point{x0,y0},Point{d*M.width+x0,y0}},
    b2 {Point{x0,y0+d},Point{x0,d*M.height+y0}}
{
    ball.set_style(Line_style{Line_style::solid, 1});
    ball.set_fill_color(Color::red);
    ball.set_color(Color::red);
    b1.set_style(Line_style{Line_style::solid,2});
    b2.set_style(Line_style{Line_style::solid,2});
    ren(l1,l2,0,0,5);
}
