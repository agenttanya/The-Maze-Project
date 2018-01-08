#include "Interface.h"
#include<iostream>
using Graph_lib::Point;
using Graph_lib::Window;

const int WindowWidth {350};
const int WindowHeight{350};
const std::string Title {"The Maze Game"};
const Point P {0,0};

const int x0 {60};
const int y0 {80};
const int d {10};
int corrx{0};
int corry{0};

const int ball_d {5};
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
{
     for (int i=rcox;i<rcox+z;++i){
        for (int j=rcoy;j<rcoy+z;++j) {
            if (M.block_list[i][j].east==1 && (i!=rcox+z-1||j!=rcoy+z-1)){
          l1.push_back(new Graph_lib::Line{Point{x0+(i+1)*d,y0+d*j},Point{x0+d*(i+1),y0+d*(j+1)}});
              l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
            if (M.block_list[i][j].north==1){
              l2.push_back(new Graph_lib::Line{Point{x0+(i+1)*d,y0+(j+1)*d},Point{x0+d*i,y0+d*(j+1)}});
              l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
        }}
}
//我想要用这个Button去显示全图、用户之前的轨迹和正确的走法。目前只实现了全图。（by KYA)
void GameWindow::solution(){
    ClGA.tracing();
    for (int i=0;i<ClGA.l3.size();++i){
        attach(ClGA.l3[i]);
    }
    for (int i=0;i<ClGA.arrow.size();++i){
        attach(ClGA.arrow[i]);
    }
    attach(ClGA.b1);
    attach(ClGA.b2);
    for (int i=0;i<ClGA.l1.size();++i){
        detach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        detach(ClGA.l2[i]);
    }
    ClGA.l1.erase();
    ClGA.l2.erase();
    ClGA.ren(ClGA.l1,ClGA.l2,0,0,20);
     for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
     for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);
    }   Fl::redraw();}
//在不同UI间切换
GameWindow::SwitchTo(UI& Next){
    if (CurrUI!=nullptr){
        for (int i=0;i< CurrUI->Buttons.size();++i) {
            detach(CurrUI->Buttons[i]);
        }
    }
    CurrUI=&Next;
    for (int i=0;i< CurrUI->Buttons.size();++i) {
        attach(CurrUI->Buttons[i]);
    }
}

//显示经典游戏区域
GameWindow::ShowClGA(){
    attach(ClGA.ball);
   // attach(ClGA.b1);
    //attach(ClGA.b2);
    for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);
    }
}

//隐藏经典游戏区域
GameWindow::HideClGA(){
    detach(ClGA.ball);
    //detach(ClGA.b1);
    //detach(ClGA.b2);
    for (int i=0;i<ClGA.l1.size();++i){
        detach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        detach(ClGA.l2[i]);
    }
}

GameWindow::GameWindow():Window {P,WindowWidth,WindowHeight,Title}
{
    //在窗口的构造函数里面定义这些按钮，因为所有界面都属于同一个类
    Button* quit_button1=new Button {Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit};
    Button* start_button=new Button {Point{x_max()-70,20}, 70, 20, "Start", cb_start};
    MainUI.Buttons.push_back(quit_button1);
    MainUI.Buttons.push_back(start_button);

    Button* quit_button2=new Button {Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit};
    Button* back_button=new Button {Point{x_max()-70,20}, 70, 20, "Back", cb_back};
    Button* solution_button=new Button {Point{x_max()-70,40}, 70, 20, "solution", cb_solution};
    GameUI.Buttons.push_back(quit_button2);
    GameUI.Buttons.push_back(back_button);
    GameUI.Buttons.push_back(solution_button);
    //当前界面为“空”
    CurrUI=nullptr;
    SwitchTo(MainUI);
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
//show part的简写，这里就是让线段集自己擦掉自己，然后再自己更新，显示小球附近5*5格子的区域，因为小球在移动到四个边界位置的时候，
//区域必须有所不同，所以这里把整个迷宫分成10个区域，不同的区域显示不同的部分。走到最后一个格子（19,19）的时候，显示全部区域以及文字“you make it”。
void GameWindow::spar()
{   for (int i=0;i<ClGA.l1.size();++i){
        detach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        detach(ClGA.l2[i]);
    }
    ClGA.l1.erase();
    ClGA.l2.erase();
    if(corrx<2||corry<2)ClGA.ren(ClGA.l1,ClGA.l2,corrx,corry,5);
    else if(corry==0&&corrx>=2&&corrx<18)ClGA.ren(ClGA.l1,ClGA.l2,corrx-2,corry,5);
    else if(corry==1&&corrx>=2&&corrx<18)ClGA.ren(ClGA.l1,ClGA.l2,corrx-2,corry-1,5);//上方长条
     else if(corrx==0&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,corrx,corry-2,5);
     else if(corrx==1&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,corrx-1,corry-2,5);//左边长条
        else if(corrx==18&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,corrx-3,corry-2,5);
        else if(corrx==19&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,corrx-4,corry-2,5);//右边长条
          else if(corrx>=2&&corrx<18&&corry==18)ClGA.ren(ClGA.l1,ClGA.l2,corrx-2,corry-3,5);
          else if(corrx>=2&&corrx<18&&corry==19)ClGA.ren(ClGA.l1,ClGA.l2,corrx-2,corry-4,5);//下边长条
             else if(corrx<2&&corry<2)ClGA.ren(ClGA.l1,ClGA.l2,0,0,5);//左上方块
               else if(corrx<2&&corry>17)ClGA.ren(ClGA.l1,ClGA.l2,0,15,5);//左下方块
                   else if(corrx>17&&corry>17&&(corrx!=19||corry!=19))ClGA.ren(ClGA.l1,ClGA.l2,15,15,5);//右下方块
                      else if(corrx>17&&corry<2)ClGA.ren(ClGA.l1,ClGA.l2,15,0,5);//右上方块
                         else if(corrx==19&&corry==19)ClGA.ren(ClGA.l1,ClGA.l2,0,0,20);//终点
                            else ClGA.ren(ClGA.l1,ClGA.l2,corrx-2,corry-2,5);//中间方块
        for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);}
        if(corrx==19&&corry==19)attach(ClGA.t);

    }

bool GameWindow::handle_keydown(int key)
{
  bool ret = false;
  string dir="no direction";
  switch (key) {
  case FL_Up:
    if (ClGA.M.block_list[corrx][corry-1].north == 0 && corry != 0){
        ClGA.ball.move(0, -d);
        ret = true;
        corry -= 1;
        dir="up";
    }
    break;
  case FL_Down:
    if (ClGA.M.block_list[corrx][corry].north == 0 && corry !=ClGA.M.height-1)
    {ClGA.ball.move(0, d); ret = true;corry += 1;
    dir="down";}
    break;
  case FL_Left:
    if (ClGA.M.block_list[corrx-1][corry].east == 0 && corrx != 0)
    {ClGA.ball.move(-d, 0); ret = true;corrx -= 1;dir="left";
    }
    break;
  case FL_Right:
    if (ClGA.M.block_list[corrx][corry].east == 0 && corrx != ClGA.M.width-1)
    {ClGA.ball.move(d, 0); ret = true;corrx += 1;dir="right";
    }
    break;
  }
  if (ret) {
     ClGA.trace.push_back(Track{corrx,corry,dir});
      spar();
  Fl::redraw();}
  return ret;
}

int GameWindow::handle(int event)
{
  int ret = Fl_Window::handle(event);
  if (ret == 1) return ret;
  switch (event) {
  case FL_FOCUS:
  case FL_UNFOCUS:
    ret = 1;
    break;
  case FL_KEYDOWN:
    if (handle_keydown(Fl::event_key()))ret = 1;
    break;
  }
  return ret;
}
