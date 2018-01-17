
#include "gamewindow.h"
#include"gamearea.h"
#include<iostream>
using namespace Graph_lib;



GameWindow::GameWindow():Window {P,WindowWidth,WindowHeight,Title}
{
    //在窗口的构造函数里面定义这些按钮，因为所有界面都属于同一个类

    //初始界面
    Button* quit_button=new Button {Point{x_max()-90, 0}, 90, 20, "Quit", cb_quit};//退出游戏
    Button* classical_button=new Button {Point{x_max()-90, 20}, 90, 20, "Classical", cb_Classical};//进入经典游戏准备
    Button* transmission_button=new Button {Point{x_max()-90, 40}, 90, 20, "Transmission", cb_Transmission};//进入传送门游戏准备
    MainUI.Buttons.push_back(quit_button);
    MainUI.Buttons.push_back(classical_button);
    MainUI.Buttons.push_back(transmission_button);

    //准备进入经典游戏界面
    Button* PreClstart_button=new Button {Point{x_max()-90, 20}, 90, 20, "Start", cb_Clstart};//开始经典游戏
    Button* PreClback_button=new Button {Point{x_max()-90, 0}, 90, 20, "Back", cb_back};//返回初始界面
    PreClUI.Buttons.push_back(PreClstart_button);
    PreClUI.Buttons.push_back(PreClback_button);

    //经典游戏界面
    Button* Clback_button=new Button {Point{x_max()-90, 20}, 90, 20, "Back", cb_back};//返回初始界面
    ClGameUI.Buttons.push_back(Clback_button);

    //准备进入传送门游戏界面
    Button* PreTrstart_button=new Button {Point{x_max()-90, 20}, 90, 20, "Start", cb_Trstart};//开始传送门游戏
    Button* PreTrback_button=new Button {Point{x_max()-90, 0}, 90, 20, "Back", cb_back};//返回初始界面
    PreTrUI.Buttons.push_back(PreTrstart_button);
    PreTrUI.Buttons.push_back(PreTrback_button);

    //传送门游戏界面
    Button* Trback_button=new Button {Point{x_max()-90, 20}, 90, 20, "Back", cb_back};//返回初始界面
    TrGameUI.Buttons.push_back(Trback_button);

    //当前界面为“空”
    CurrUI=nullptr;
    SwitchTo(MainUI);
}


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
    Clmanage_timeout();
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
    detach(ClGA.e);
    for (int i=0;i<ClGA.l1.size();++i){
        detach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        detach(ClGA.l2[i]);
    }
}

//显示传送门游戏区域
GameWindow::ShowTrGA(){
    Tr = true;
    attach(TrGA.ball);
    attach(TrGA.e);
    Trmanage_timeout();
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

//隐藏传送门游戏区域
GameWindow::HideTrGA(){
    Tr = false;
    detach(TrGA.ball);
    detach(TrGA.e);
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


//show part的简写，这里就是让线段集自己擦掉自己，然后再自己更新，显示小球附近5*5格子的区域，因为小球在移动到四个边界位置的时候，
//区域必须有所不同，所以这里把整个迷宫分成10个区域，不同的区域显示不同的部分。走到最后一个格子（19,19）的时候，显示全部区域以及文字“you make it”。
void GameWindow::Clspar()
{
    for (int i=0;i<ClGA.l1.size();++i){
        detach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        detach(ClGA.l2[i]);
    }
    ClGA.l1.erase();
    ClGA.l2.erase();
    ClGA.renewal();
    for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);}
    if(ClGA.corrx==width-1&&ClGA.corry==height-1)attach(ClGA.t);
}

void GameWindow::Trspar()
{
    for (int i=0;i<TrGA.l1.size();++i){
        detach(TrGA.l1[i]);
    }
    for (int i=0;i<TrGA.l2.size();++i){
        detach(TrGA.l2[i]);
    }
    TrGA.l1.erase();
    TrGA.l2.erase();
    for (int i=0;i<TrGA.circin.size();++i){
        detach(TrGA.circin[i]);
    }
    for (int i=0;i<TrGA.circout.size();++i){
        detach(TrGA.circout[i]);
    }
    TrGA.circin.erase();
    TrGA.circout.erase();

    TrGA.renewal();

    for (int i=0;i<TrGA.l1.size();++i){
        attach(TrGA.l1[i]);
    }
    for (int i=0;i<TrGA.l2.size();++i){
        attach(TrGA.l2[i]);}
    if(TrGA.corrx==width-1&&TrGA.corry==height-1)attach(TrGA.t);
    for (int i=0;i<TrGA.circin.size();++i){
        attach(TrGA.circin[i]);
    }
    for (int i=0;i<TrGA.circout.size();++i){
        attach(TrGA.circout[i]);
    }
}

bool GameWindow::Clhandle_keydown(int key)
{
  bool ret = false;
  string dir="no direction";
  switch (key) {
  case FL_Up:
    if (ClGA.M->block_list[ClGA.corrx][ClGA.corry-1].north == 0 && ClGA.corry != 0){
        ret = true;
        ClGA.corry -= 1;
        dir="up";
    }
    break;
  case FL_Down:
    if (ClGA.M->block_list[ClGA.corrx][ClGA.corry].north == 0 && ClGA.corry !=ClGA.M->height-1)
    {
        ret = true;
        ClGA.corry += 1;
        dir="down";
    }
    break;
  case FL_Left:
    if (ClGA.corrx != 0&&ClGA.M->block_list[ClGA.corrx-1][ClGA.corry].east == 0  )
    {
        ret = true;
        ClGA.corrx -= 1;
        dir="left";
    }
    break;
  case FL_Right:
    if (ClGA.M->block_list[ClGA.corrx][ClGA.corry].east == 0 && ClGA.corrx != ClGA.M->width-1)
    {
        ret = true;
        ClGA.corrx += 1;
        dir="right";
    }
    break;
}
  if (ret) {
     //ClGA.trace.push_back(Track{corrx,corry,dir});
      Clspar();
  Fl::redraw();}
  return ret;
}

bool GameWindow::Trhandle_keydown(int key)
{
  bool ret = false;
  string dir="no direction";
  switch (key) {
  case FL_Up:
    if (TrGA.M->block_list[TrGA.corrx][TrGA.corry-1].north == 0 && TrGA.corry != 0){
        ret = true;
        TrGA.corry -= 1;
        dir="up";
    }
    break;
  case FL_Down:
    if (TrGA.M->block_list[TrGA.corrx][TrGA.corry].north == 0 && TrGA.corry !=TrGA.M->height-1)
    {
        ret = true;
        TrGA.corry += 1;
        dir="down";
    }
    break;
  case FL_Left:
    if (TrGA.corrx != 0&&TrGA.M->block_list[TrGA.corrx-1][TrGA.corry].east == 0  )
    {
        ret = true;
        TrGA.corrx -= 1;
        dir="left";
    }
    break;
  case FL_Right:
    if (TrGA.M->block_list[TrGA.corrx][TrGA.corry].east == 0 && TrGA.corrx != TrGA.M->width-1)
    {
        ret = true;
        TrGA.corrx += 1;
        dir="right";
    }
    break;
  case FL_Enter:
        for(int i=0; i<TrGA.M->PG_list.size();++i){
        PG pg;
        pg = TrGA.M->PG_list[i];
        if ((pg.pg1corx == TrGA.corrx && pg.pg1cory == TrGA.corry) || (pg.pg2corx == TrGA.corrx && pg.pg2cory == TrGA.corry)){
            if  (pg.pg1corx == TrGA.corrx && pg.pg1cory == TrGA.corry){
            TrGA.corrx = pg.pg2corx;
            TrGA.corry = pg.pg2cory;
            ret = true;
            }
            else{
            TrGA.corrx = pg.pg1corx;
            TrGA.corry = pg.pg1cory;
            ret = true;
            }
        }
    }
    break;
}
  if (ret) {
     //ClGA.trace.push_back(Track{corrx,corry,dir});
      Trspar();
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
      if (Cl){
        if (Clhandle_keydown( Fl::event_key() ) ) ret = 1;
      }
      if (Tr){
         if (Trhandle_keydown( Fl::event_key() ) ) ret = 1;
      }
      break;
  }
  return ret;
}


void  GameWindow::Cltimeout() {
    if(ClGA.t0.sec==0&&ClGA.t0.min==0&&ClGA.t0.hour==0)return;
    ClGA.t0.run();
    ClGA.e.set_label(ClGA.t0.timeline);
    Fl::redraw();
    Fl::repeat_timeout(1, cb_Cltimeout, this);
  }

  void  GameWindow::Trtimeout() {
    if(TrGA.t0.sec==0&&TrGA.t0.min==0&&TrGA.t0.hour==0)return;
    TrGA.t0.run();
    TrGA.e.set_label(TrGA.t0.timeline);
    Fl::redraw();
    Fl::repeat_timeout(1, cb_Trtimeout, this);
  }

void  GameWindow::Clmanage_timeout() {
      Fl::add_timeout(1, cb_Cltimeout, this);
  }

  void  GameWindow::Trmanage_timeout() {
      Fl::add_timeout(1, cb_Trtimeout, this);
  }

