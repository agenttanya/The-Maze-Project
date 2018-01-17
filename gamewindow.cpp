
#include "gamewindow.h"
#include"gamearea.h"
#include<iostream>
using namespace Graph_lib;


/*
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
    for (int i=0;i<ClGA.circin.size();++i){
        detach(ClGA.circin[i]);
    }
    for (int i=0;i<ClGA.circout.size();++i){
        detach(ClGA.circout[i]);
    }
    ClGA.l1.erase();
    ClGA.l2.erase();
    ClGA.circin.erase();
    ClGA.circout.erase();
    ClGA.renewal(0,0,20);
     for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
     for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);
    }
     for (int i=0;i<ClGA.circin.size();++i){
        attach(ClGA.circin[i]);
    }
     for (int i=0;i<ClGA.circout.size();++i){
        attach(ClGA.circout[i]);
    }
     Fl::redraw();
}
*/

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
    Cl = true;
    attach(ClGA.ball);
    attach(ClGA.e);
    manage_timeout();
    for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);
    }
}

//隐藏经典游戏区域
GameWindow::HideClGA(){
    Cl = false;
    detach(ClGA.ball);
    for (int i=0;i<ClGA.l1.size();++i){
        detach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        detach(ClGA.l2[i]);
    }
}

GameWindow::ShowTrGA(){
    Tr = true;
    attach(TrGA.ball);
    attach(TrGA.e);
    manage_timeout();
    for (int i=0;i<TrGA.l1.size();++i){
        attach(TrGA.l1[i]);
    }
    for (int i=0;i<TrGA.l2.size();++i){
        attach(TrGA.l2[i]);
    }
    for (int i=0;i<TrGA.circin.size();++i){
        attach(TrGA.circin[i]);
    }
    for (int i=0;i<TrGA.circout.size();++i){
        attach(TrGA.circout[i]);
    }
}

//隐藏经典游戏区域
GameWindow::HideTrGA(){
    Tr = false;
    detach(TrGA.ball);
    for (int i=0;i<TrGA.l1.size();++i){
        detach(TrGA.l1[i]);
    }
    for (int i=0;i<TrGA.l2.size();++i){
        detach(TrGA.l2[i]);
    }
        for (int i=0;i<TrGA.circin.size();++i){
        detach(TrGA.circin[i]);
    }
    for (int i=0;i<TrGA.circout.size();++i){
        detach(TrGA.circout[i]);
    }
}


GameWindow::GameWindow():Window {P,WindowWidth,WindowHeight,Title}
{
    //在窗口的构造函数里面定义这些按钮，因为所有界面都属于同一个类
    Button* quit_button1=new Button {Point{x_max()-90, 0}, 90, 20, "Quit", cb_quit};
    Button* classical_button=new Button {Point{x_max()-90, 20}, 90, 20, "Classical", cb_Classical};
    Button* transmission_button=new Button {Point{x_max()-90, 40}, 90, 20, "Transmission", cb_Transmission};
    MainUI.Buttons.push_back(quit_button1);
    MainUI.Buttons.push_back(classical_button);
    MainUI.Buttons.push_back(transmission_button);

    Button* quit_button2=new Button {Point{x_max()-90, 0}, 90, 20, "Quit", cb_quit};
    Button* back_button=new Button {Point{x_max()-90, 20}, 90, 20, "Back", cb_back};
    //Button* solution_button=new Button {Point{x_max()-70,40}, 70, 20, "solution", cb_solution};
    GameUI.Buttons.push_back(quit_button2);
    GameUI.Buttons.push_back(back_button);
    //GameUI.Buttons.push_back(solution_button);
    //当前界面为“空”
    CurrUI=nullptr;
    SwitchTo(MainUI);
}




//show part的简写，这里就是让线段集自己擦掉自己，然后再自己更新，显示小球附近5*5格子的区域，因为小球在移动到四个边界位置的时候，
//区域必须有所不同，所以这里把整个迷宫分成10个区域，不同的区域显示不同的部分。走到最后一个格子（19,19）的时候，显示全部区域以及文字“you make it”。
void GameWindow::spar()
{
    GT &GA = TrGA;
  if(Cl == true){
    GC &GA = ClGA;
  }
    for (int i=0;i<GA.l1.size();++i){
        detach(GA.l1[i]);
    }
    for (int i=0;i<GA.l2.size();++i){
        detach(GA.l2[i]);
    }
    GA.l1.erase();
    GA.l2.erase();
    GA.renewal(corrx , corry);
    for (int i=0;i<GA.l1.size();++i){
        attach(GA.l1[i]);
    }
    for (int i=0;i<GA.l2.size();++i){
        attach(GA.l2[i]);}
    if(corrx==width-1&&corry==height-1)attach(ClGA.t);
    if(Tr == true){
    for (int i=0;i<GA.circin.size();++i){
        detach(GA.circin[i]);
    }
    for (int i=0;i<GA.circout.size();++i){
        detach(GA.circout[i]);
    }
    GA.circin.erase();
    GA.circout.erase();
    for (int i=0;i<GA.circin.size();++i){
        attach(GA.circin[i]);
    }
    for (int i=0;i<GA.circout.size();++i){
        attach(GA.circout[i]);
    }
    }
}

bool GameWindow::handle_keydown(int key)
{
  GT &GA = TrGA;
  if(Cl == true){
    GC &GA = ClGA;
  }
  bool ret = false;
  string dir="no direction";
  switch (key) {
  case FL_Up:
    if (GA.M.block_list[corrx][corry-1].north == 0 && corry != 0){
        ret = true;
        corry -= 1;
        dir="up";
    }
    break;
  case FL_Down:
    if (GA.M.block_list[corrx][corry].north == 0 && corry !=GA.M.height-1)
    {
        ret = true;
        corry += 1;
        dir="down";
    }
    break;
  case FL_Left:
    if (corrx != 0&&GA.M.block_list[corrx-1][corry].east == 0  )
    {
        ret = true;
        corrx -= 1;
        dir="left";
    }
    break;
  case FL_Right:
    if (GA.M.block_list[corrx][corry].east == 0 && corrx != GA.M.width-1)
    {
        ret = true;
        corrx += 1;
        dir="right";
    }
    break;
  case FL_Enter:
    if(Tr==true){
        for(int i=0; i<GA.M.PG_list.size();++i){
        PG pg;
        pg = GA.M.PG_list[i];
        if ((pg.pg1corx == corrx && pg.pg1cory == corry) || (pg.pg2corx == corrx && pg.pg2cory == corry)){
            if  (pg.pg1corx == corrx && pg.pg1cory == corry){
            corrx = pg.pg2corx;
            corry = pg.pg2cory;
            ret = true;
            }
            else{
            corrx = pg.pg1corx;
            corry = pg.pg1cory;
            ret = true;
            }
        }
    }
    }
    break;
}
  if (ret) {
     //ClGA.trace.push_back(Track{corrx,corry,dir});
      spar();
  Fl::redraw();}
  return ret;
}

/*
void GameWindow::clock()
{
      long t=time(NULL);
      while(time(NULL)==t);
      for(;;){detach(ClGA.e);
      if(ClGA.t0.sec==0&&ClGA.t0.min==0&&ClGA.t0.hour==0)return;
      ClGA.t0.run();
      attach(ClGA.e);
      Fl::redraw();}

}*/

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


void  GameWindow::timeout() {
  GT &GA = TrGA;
  if(Cl == true){
    GC &GA = ClGA;
  }
    if(GA.t0.sec==0&&GA.t0.min==0&&GA.t0.hour==0)return;
    GA.t0.run();
    GA.e.set_label(GA.t0.timeline);
    Fl::redraw();
    Fl::repeat_timeout(1, cb_timeout, this);
  }

void  GameWindow::manage_timeout() {
      Fl::add_timeout(1, cb_timeout, this);
  }
