
#include "gamewindow.h"
#include"gamearea.h"
#include<iostream>
#include"automove.h"
#include<sstream>
using namespace Graph_lib;



GameWindow::GameWindow():Window {P,WindowWidth,WindowHeight,Title}
{
    //�ڴ��ڵĹ��캯�����涨����Щ��ť����Ϊ���н��涼����ͬһ����

    //��ʼ����
    Button* classical_button=new Button {Point{120, 120}, 160, 40, "Classical Mode", cb_Classical};//���뾭����Ϸ׼��
    Button* transmission_button=new Button {Point{120,180}, 160, 40, "Portal Mode", cb_Transmission};//���봫������Ϸ׼��
    Button* quit_button=new Button {Point{120, 240}, 160, 40, "Quit", cb_quit};//�˳���Ϸ
    Text* TheTitle=new Text {Point{90,70},Title};
    TheTitle->set_font_size(30);
    MainUI.Buttons.push_back(quit_button);
    MainUI.Buttons.push_back(classical_button);
    MainUI.Buttons.push_back(transmission_button);
    MainUI.Texts.push_back(TheTitle);

    //׼�����뾭����Ϸ����
    Button* PreClstart_button=new Button {Point{120, 260}, 160, 30, "Start", cb_Clstart};//��ʼ������Ϸ
    Button* PreClback_button=new Button {Point{120, 300}, 160, 30, "Back", cb_back};//���س�ʼ����
    In_box* ClWidthBox=new In_box {Point{200,120},40,20,"Width is"};
    In_box* ClHeightBox=new In_box {Point{200,170},40,20,"Height is"};
    In_box* ClDiffBox=new In_box {Point{205,220},40,20,"Difficulty is"};
    PreClUI.Buttons.push_back(PreClstart_button);
    PreClUI.Buttons.push_back(PreClback_button);
    PreClUI.Inboxes.push_back(ClWidthBox);
    PreClUI.Inboxes.push_back(ClHeightBox);
    PreClUI.Inboxes.push_back(ClDiffBox);

    //������Ϸ����
    Button* Clback_button=new Button {Point{x_max()-90, 20}, 90, 20, "Back", cb_back};//���س�ʼ����
    ClGameUI.Buttons.push_back(Clback_button);
     Text* Clcoordinate=new Text {Point{200,60},""};
     ClGameUI.Texts.push_back(Clcoordinate);
     Text* ClCount=new Text {Point{30,40},""};
     ClGameUI.Texts.push_back(ClCount);
     Text *hints=new Text {Point{100,80},"Press 'h' for hints"};
     ClGameUI.Texts.push_back(hints);

    //׼�����봫������Ϸ����
    Button* PreTrstart_button=new Button {Point{120, 280}, 160, 30, "Start", cb_Trstart};//��ʼ��������Ϸ
    Button* PreTrback_button=new Button {Point{120, 320}, 160, 30, "Back", cb_back};//���س�ʼ����
    In_box* TrWidthBox=new In_box {Point{200,90},40,20,"Width is"};
    In_box* TrHeightBox=new In_box {Point{200,140},40,20,"Height is"};
    In_box* TrDiffBox=new In_box {Point{205,190},40,20,"Difficulty is"};
    In_box* TrPgprBox=new In_box {Point{220,240},40,20,"Number of gate pair is"};
    PreTrUI.Buttons.push_back(PreTrstart_button);
    PreTrUI.Buttons.push_back(PreTrback_button);
    PreTrUI.Inboxes.push_back(TrWidthBox);
    PreTrUI.Inboxes.push_back(TrHeightBox);
    PreTrUI.Inboxes.push_back(TrDiffBox);
    PreTrUI.Inboxes.push_back(TrPgprBox);

    //��������Ϸ����
    Button* Trback_button=new Button {Point{x_max()-90, 20}, 90, 20, "Back", cb_back};//���س�ʼ����
    TrGameUI.Buttons.push_back(Trback_button);
    Text* Trcoordinate=new Text {Point{200,60},""};
     TrGameUI.Texts.push_back(Trcoordinate);
     Text* TrCount=new Text {Point{30,40},""};
    TrGameUI.Texts.push_back(TrCount);

    //��������
    Button*Endback_button=new Button {Point{x_max()-90, 0}, 90, 20, "Back", cb_back};
    EndUI.Buttons.push_back(Endback_button);
    Text* Ending=new Text {Point{200,20},""};
    EndUI.Texts.push_back(Ending);
    Text* final_score=new Text {Point{200,40},""};
    EndUI.Texts.push_back(final_score);

    //��ǰ����Ϊ���ա�
    CurrUI=nullptr;
    SwitchTo(MainUI);
}


//�ڲ�ͬUI���л�
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

//��ʾ������Ϸ����
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

//���ؾ�����Ϸ����
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

//��ʾ��������Ϸ����
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

//���ش�������Ϸ����
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
    if(ClGA.corrx==ClGA.M->width-1&&ClGA.corry==ClGA.M->height-1){//ʤ�������ж�
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


   //�ھ����������ʾ
 void GameWindow::Hint()
 {
    if (ClGA.chances>0){
    ClGA.chances-= 1;
    AM_Stack AM_Path;
    coor end_p {ClGA.M->width-1,ClGA.M->height-1};
    for (int i=0;i<=end_p.x;++i)
    for (int j=0;j<=end_p.y;++j){
      ClGA.M->block_list[i][j].footprint=true;
    }
    coor cp {ClGA.corrx,ClGA.corry};    //��¼��ǰ����
    AM_Path.push(cp);
    ClGA.M->block_list[cp.x][cp.y].footprint=false;

    while (true){
        bool footprint=false;
        if (cp.x == end_p.x && cp.y == end_p.y)
            break;
        if (ClGA.M->block_list[cp.x][cp.y].north==0 && ClGA.M->block_list[cp.x][cp.y+1].footprint==true)  //����
        {
            AM_Path.push(coor{cp.x, cp.y+1});
            cp.y +=1 ;
            ClGA.M->block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
       if (ClGA.M->block_list[cp.x][cp.y].east==0 && ClGA.M->block_list[cp.x+1][cp.y].footprint==true)  //����
        {
            AM_Path.push(coor{cp.x+1, cp.y});
            cp.x +=1 ;
            ClGA.M->block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
        if (cp.y!=0 && ClGA.M->block_list[cp.x][cp.y-1].north==0 && ClGA.M->block_list[cp.x][cp.y-1].footprint==true)  //����
        {
            AM_Path.push(coor{cp.x, cp.y-1});
            cp.y -=1 ;
            ClGA.M->block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
       if (cp.x!=0 && ClGA.M->block_list[cp.x-1][cp.y].east==0 && ClGA.M->block_list[cp.x-1][cp.y].footprint==true)  //����
       {
            AM_Path.push(coor{cp.x-1, cp.y});
            cp.x -=1 ;
            ClGA.M->block_list[cp.x][cp.y].footprint=false;
            footprint=true;
        }
        if (footprint==false){
          AM_Path.pop();
          cp=AM_Path.get_top();
        }
    }
    coor *p1 = AM_Path.base;
    coor *p2 = p1->next;

    if(p2->x - p1->x==1) //��ͷ����
    {
        ClGA.arrow.push_back(new Text{Point{CenterX+(p2->x-ClGA.corrx)*WallWidth,CenterY+(p2->y-ClGA.corry)*WallWidth},">"});
        ClGA.arrow[ClGA.arrow.size()-1].set_color(Color::dark_red);
    }
    if(p2->x - p1->x==-1) //��ͷ����
    {
        ClGA.arrow.push_back(new Text{Point{CenterX+(p2->x-ClGA.corrx)*WallWidth,CenterY+(p2->y-ClGA.corry)*WallWidth},"<"});
        ClGA.arrow[ClGA.arrow.size()-1].set_color(Color::dark_red);
    }
    if(p2->y - p1->y==1) //��ͷ����
    {
        ClGA.arrow.push_back(new Text{Point{CenterX+(p2->x-ClGA.corrx)*WallWidth,CenterY+(p2->y-ClGA.corry)*WallWidth},"v"});
        ClGA.arrow[ClGA.arrow.size()-1].set_color(Color::dark_red);
    }
    if(p2->y - p1->y==-1) //��ͷ����
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
    //text���ʣ�����
  }
  else{
    ClGameUI.Texts[2].set_label(hint);
  }
 }
