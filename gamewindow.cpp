
#include "gamewindow.h"
#include"gamearea.h"
#include<iostream>
#include"automove.h"
#include<sstream>
using namespace Graph_lib;



GameWindow::GameWindow():Window {P,WindowWidth,WindowHeight,Title}
{
    //在窗口的构造函数里面定义这些按钮，因为所有界面都属于同一个类

    //初始界面
    Button* classical_button=new Button {Point{120, 120}, 160, 40, "Classical Mode", cb_Classical};//进入经典游戏准备
    Button* transmission_button=new Button {Point{120,180}, 160, 40, "Portal Mode", cb_Transmission};//进入传送门游戏准备
    Button* quit_button=new Button {Point{120, 240}, 160, 40, "Quit", cb_quit};//退出游戏
    Text* TheTitle=new Text {Point{90,70},Title};
    TheTitle->set_font_size(30);
    MainUI.Buttons.push_back(quit_button);
    MainUI.Buttons.push_back(classical_button);
    MainUI.Buttons.push_back(transmission_button);
    MainUI.Texts.push_back(TheTitle);

    //准备进入经典游戏界面
    Button* PreClstart_button=new Button {Point{120, 260}, 160, 30, "Start", cb_Clstart};//开始经典游戏
    Button* PreClback_button=new Button {Point{120, 300}, 160, 30, "Back", cb_back};//返回初始界面
    In_box* ClWidthBox=new In_box {Point{200,120},40,20,"Width is"};
    In_box* ClHeightBox=new In_box {Point{200,170},40,20,"Height is"};
    In_box* ClDiffBox=new In_box {Point{205,220},40,20,"Difficulty is"};
    PreClUI.Buttons.push_back(PreClstart_button);
    PreClUI.Buttons.push_back(PreClback_button);
    PreClUI.Inboxes.push_back(ClWidthBox);
    PreClUI.Inboxes.push_back(ClHeightBox);
    PreClUI.Inboxes.push_back(ClDiffBox);
    Text*Clreference1=new Text{Point{20,20},"Please put positive integer into height and width box."};
    Text*Clreference2=new Text{Point{20,40},"There is 'E','N'and 'H' three ranks of difficulty."};
    Text*Clreference3=new Text{Point{20,60},"Use the direction key to move and you have 3 hints"};
    Text*Clreference4=new Text{Point{20,80},"Be sure to get out before the countdown ends."};
    Text*Clreference5=new Text{Point{20,100},"The faster, the better score you will get."};
    PreClUI.Texts.push_back(Clreference1);
    PreClUI.Texts.push_back(Clreference2);
    PreClUI.Texts.push_back(Clreference3);
    PreClUI.Texts.push_back(Clreference4);
    PreClUI.Texts.push_back(Clreference5);






    //经典游戏界面
    Button* Clback_button=new Button {Point{x_max()-90, 20}, 90, 20, "Back", cb_back};//返回初始界面
    ClGameUI.Buttons.push_back(Clback_button);
     Text* Clcoordinate=new Text {Point{200,60},""};
     ClGameUI.Texts.push_back(Clcoordinate);
     Text* ClCount=new Text {Point{30,40},""};
     ClGameUI.Texts.push_back(ClCount);
     Text *hints=new Text {Point{100,80},"Press 'h' for hints"};
     ClGameUI.Texts.push_back(hints);

    //准备进入传送门游戏界面
    Button* PreTrstart_button=new Button {Point{120, 280}, 160, 30, "Start", cb_Trstart};//开始传送门游戏
    Button* PreTrback_button=new Button {Point{120, 320}, 160, 30, "Back", cb_back};//返回初始界面
    In_box* TrWidthBox=new In_box {Point{200,150},40,20,"Width is"};
    In_box* TrHeightBox=new In_box {Point{200,180},40,20,"Height is"};
    In_box* TrDiffBox=new In_box {Point{205,210},40,20,"Difficulty is"};
    PreTrUI.Buttons.push_back(PreTrstart_button);
    PreTrUI.Buttons.push_back(PreTrback_button);
    PreTrUI.Inboxes.push_back(TrWidthBox);
    PreTrUI.Inboxes.push_back(TrHeightBox);
    PreTrUI.Inboxes.push_back(TrDiffBox);
    Text*Trreference1=new Text{Point{20,20},"ONlY POSITIVE integer into height, width."};
    Text*Trreference2=new Text{Point{20,40},"Maze which is too large may cause unexpected error."};
    Text*Trreference3=new Text{Point{20,60},"There is 'E','N'and 'H' three ranks of difficulty."};
    Text*Trreference4=new Text{Point{20,80},"Use the direction key to move and 'enter' to use portal."};
    Text*Trreference5=new Text{Point{20,100},"Be sure to get out before the countdown ends."};
    Text*Trreference6=new Text{Point{20,120},"The faster, the better score you will get."};
    PreTrUI.Texts.push_back(Trreference1);
    PreTrUI.Texts.push_back(Trreference2);
    PreTrUI.Texts.push_back(Trreference3);
    PreTrUI.Texts.push_back(Trreference4);
    PreTrUI.Texts.push_back(Trreference5);
    PreTrUI.Texts.push_back(Trreference6);



    //传送门游戏界面
    Button* Trback_button=new Button {Point{x_max()-90, 20}, 90, 20, "Back", cb_back};//返回初始界面
    TrGameUI.Buttons.push_back(Trback_button);
    Text* Trcoordinate=new Text {Point{200,60},""};
     TrGameUI.Texts.push_back(Trcoordinate);
     Text* TrCount=new Text {Point{30,40},""};
    TrGameUI.Texts.push_back(TrCount);

    //结束界面
    Button*Endback_button=new Button {Point{x_max()-90, 0}, 90, 20, "Back", cb_back};
    EndUI.Buttons.push_back(Endback_button);
    Text* Ending=new Text {Point{20,20},""};
    EndUI.Texts.push_back(Ending);
    Text* final_score=new Text {Point{180,40},""};
    EndUI.Texts.push_back(final_score);

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
        for (int i=0; i < CurrUI -> Inboxes.size(); ++i) {
            detach( CurrUI -> Inboxes[i]);
        }
        for (int i=0; i < CurrUI -> Texts.size(); ++i) {
            detach( CurrUI -> Texts[i]);
        }
    }
    CurrUI=&Next;
    for (int i=0;i< CurrUI->Buttons.size();++i) {
        attach(CurrUI->Buttons[i]);
    }
    for (int i=0; i < CurrUI -> Inboxes.size(); ++i) {
            attach( CurrUI -> Inboxes[i]);
        }
        for (int i=0; i < CurrUI -> Texts.size(); ++i) {
            attach( CurrUI -> Texts[i]);
        }
}

//显示经典游戏区域
GameWindow::ShowClGA(){
    Cl = true;
    attach(ClGA.ball);
    Clmanage_timeout();
    for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);
    }
    ClGameUI.Texts[0].set_label(ClGA.get_coor());
    ClGameUI.Texts[1].set_label(ClGA.t0.timeline);
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
    for (int i=0;i<ClGA.arrow.size();++i){
        detach(ClGA.arrow[i]);
    }
}

//显示传送门游戏区域
GameWindow::ShowTrGA(){
    Tr = true;
    attach(TrGA.ball);
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
    TrGameUI.Texts[0].set_label(TrGA.get_coor());
    TrGameUI.Texts[1].set_label(TrGA.t0.timeline);
}

//隐藏传送门游戏区域
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
    for (int i=0;i<ClGA.arrow.size();++i){
        detach(ClGA.arrow[i]);
    }
    ClGA.arrow.erase();
    ClGA.renewal();
    for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);}
    ClGameUI.Texts[0].set_label(ClGA.get_coor());
    if(ClGA.corrx==ClGA.M->width-1&&ClGA.corry==ClGA.M->height-1){//胜利条件判断
            HideClGA();
            SwitchTo(EndUI);
            EndUI.Texts[0].set_label(Vict);
            EndUI.Texts[1].set_label(fisco1());
    }
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
    for (int i=0;i<TrGA.circin.size();++i){
        attach(TrGA.circin[i]);
    }
    for (int i=0;i<TrGA.circout.size();++i){
        attach(TrGA.circout[i]);
    }
    TrGameUI.Texts[0].set_label(TrGA.get_coor());
    if(TrGA.corrx==TrGA.M->width-1&&TrGA.corry==TrGA.M->height-1) {
            HideTrGA();
            SwitchTo(EndUI);
            EndUI.Texts[0].set_label(Vict);
            EndUI.Texts[1].set_label(fisco2());
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
case 'h':
        Hint();
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
    if(ClGA.t0.sec==0&&ClGA.t0.min==0&&ClGA.t0.hour==0) {
            if (Cl) {
                    HideClGA();
                    SwitchTo(EndUI);
                    EndUI.Texts[0].set_label(Lost);
                    EndUI.Texts[1].set_label("");
            }
            return;
    }
    ClGA.t0.run();
    ClGameUI.Texts[1].set_label(ClGA.t0.timeline);
    Fl::redraw();
    Fl::repeat_timeout(1, cb_Cltimeout, this);
  }

  void  GameWindow::Trtimeout() {
    if(TrGA.t0.sec==0&&TrGA.t0.min==0&&TrGA.t0.hour==0){
            if (Tr) {
                    HideTrGA();
                    SwitchTo(EndUI);
                    EndUI.Texts[0].set_label(Lost);
                    EndUI.Texts[1].set_label("");
            }
            return;
    }
    TrGA.t0.run();
    TrGameUI.Texts[1].set_label(TrGA.t0.timeline);
    Fl::redraw();
    Fl::repeat_timeout(1, cb_Trtimeout, this);
  }

void  GameWindow::Clmanage_timeout() {
      Fl::add_timeout(1, cb_Cltimeout, this);
  }

  void  GameWindow::Trmanage_timeout() {
      Fl::add_timeout(1, cb_Trtimeout, this);
  }


   //在经典界面获得提示
 void GameWindow::Hint()
 {
    if (ClGA.chances>0){
    ClGA.chances-= 1;

    AM_Stack AM_Path;
    AM_Path.get_path(ClGA.corrx, ClGA.corry, *ClGA.M);

    coor *p1 = AM_Path.base;
    coor *p2 = p1->next;

    if(p2->x - p1->x==1) //箭头向右
    {
        ClGA.arrow.push_back(new Text{Point{CenterX+(p2->x-ClGA.corrx)*WallWidth,CenterY+(p2->y-ClGA.corry)*WallWidth},">"});
        ClGA.arrow[ClGA.arrow.size()-1].set_color(Color::dark_red);
    }
    if(p2->x - p1->x==-1) //箭头向左
    {
        ClGA.arrow.push_back(new Text{Point{CenterX+(p2->x-ClGA.corrx)*WallWidth,CenterY+(p2->y-ClGA.corry)*WallWidth},"<"});
        ClGA.arrow[ClGA.arrow.size()-1].set_color(Color::dark_red);
    }
    if(p2->y - p1->y==1) //箭头向下
    {
        ClGA.arrow.push_back(new Text{Point{CenterX+(p2->x-ClGA.corrx)*WallWidth,CenterY+(p2->y-ClGA.corry)*WallWidth},"v"});
        ClGA.arrow[ClGA.arrow.size()-1].set_color(Color::dark_red);
    }
    if(p2->y - p1->y==-1) //箭头向上
    {
        ClGA.arrow.push_back(new Text{Point{CenterX+(p2->x-ClGA.corrx)*WallWidth,CenterY+(p2->y-ClGA.corry)*WallWidth},"^"});
        ClGA.arrow[ClGA.arrow.size()-1].set_color(Color::dark_red);
    }
    for (int i=0; i<ClGA.arrow.size(); ++i){
        attach(ClGA.arrow[i]);
    }

    std::ostringstream oss;
    oss<<ClGA.chances<<" chances remain.";
    std::string chance{oss.str()};
    ClGameUI.Texts[2].set_label(chance);
    //text输出剩余次数
  }
  else{
    ClGameUI.Texts[2].set_label(hint);
  }
 }
