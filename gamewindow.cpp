
#include "gamewindow.h"
#include"gamearea.h"
#include<iostream>
using namespace Graph_lib;


/*
//����Ҫ�����Buttonȥ��ʾȫͼ���û�֮ǰ�Ĺ켣����ȷ���߷���Ŀǰֻʵ����ȫͼ����by KYA)
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

//�ڲ�ͬUI���л�
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

//��ʾ������Ϸ����
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

//���ؾ�����Ϸ����
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

GameWindow::ShowTrGA(){
    std::cout<<"ShowTrGA";
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

//���ؾ�����Ϸ����
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


GameWindow::GameWindow():Window {P,WindowWidth,WindowHeight,Title}
{
    //�ڴ��ڵĹ��캯�����涨����Щ��ť����Ϊ���н��涼����ͬһ����
    std::cin.get();
    std::cout<<"construct gamewindow"<<endl;
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
    //��ǰ����Ϊ���ա�
    CurrUI=nullptr;
    SwitchTo(MainUI);
}




//show part�ļ�д������������߶μ��Լ������Լ���Ȼ�����Լ����£���ʾС�򸽽�5*5���ӵ�������ΪС�����ƶ����ĸ��߽�λ�õ�ʱ��
//�������������ͬ����������������Թ��ֳ�10�����򣬲�ͬ��������ʾ��ͬ�Ĳ��֡��ߵ����һ�����ӣ�19,19����ʱ����ʾȫ�������Լ����֡�you make it����
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

