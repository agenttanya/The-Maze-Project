#include "gamewindow.h"
#include<iostream>
using Graph_lib::Point;
using Graph_lib::Window;


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
    ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,0,0,20);
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
     Fl::redraw();}


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
    attach(ClGA.ball);
   // attach(ClGA.b1);
    //attach(ClGA.b2);
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
}

//���ؾ�����Ϸ����
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
        for (int i=0;i<ClGA.circin.size();++i){
        detach(ClGA.circin[i]);
    }
    for (int i=0;i<ClGA.circout.size();++i){
        detach(ClGA.circout[i]);
    }
}


GameWindow::GameWindow():Window {P,WindowWidth,WindowHeight,Title}
{
    //�ڴ��ڵĹ��캯�����涨����Щ��ť����Ϊ���н��涼����ͬһ����
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
    //��ǰ����Ϊ���ա�
    CurrUI=nullptr;
    SwitchTo(MainUI);
}




//show part�ļ�д������������߶μ��Լ������Լ���Ȼ�����Լ����£���ʾС�򸽽�5*5���ӵ�������ΪС�����ƶ����ĸ��߽�λ�õ�ʱ��
//�������������ͬ����������������Թ��ֳ�10�����򣬲�ͬ��������ʾ��ͬ�Ĳ��֡��ߵ����һ�����ӣ�19,19����ʱ����ʾȫ�������Լ����֡�you make it����
void GameWindow::spar()
{   for (int i=0;i<ClGA.l1.size();++i){
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
    if(corrx<2||corry<2)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx,corry,5);
    else if(corry==0&&corrx>=2&&corrx<18)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-2,corry,5);
    else if(corry==1&&corrx>=2&&corrx<18)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-2,corry-1,5);//�Ϸ�����
     else if(corrx==0&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx,corry-2,5);
     else if(corrx==1&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-1,corry-2,5);//��߳���
        else if(corrx==18&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-3,corry-2,5);
        else if(corrx==19&&corry>=2&&corry<18)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-4,corry-2,5);//�ұ߳���
          else if(corrx>=2&&corrx<18&&corry==18)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-2,corry-3,5);
          else if(corrx>=2&&corrx<18&&corry==19)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-2,corry-4,5);//�±߳���
             else if(corrx<2&&corry<2)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,0,0,5);//���Ϸ���
               else if(corrx<2&&corry>17)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,0,15,5);//���·���
                   else if(corrx>17&&corry>17&&(corrx!=19||corry!=19))ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,15,15,5);//���·���
                      else if(corrx>17&&corry<2)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,15,0,5);//���Ϸ���
                         else if(corrx==19&&corry==19)ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,0,0,20);//�յ�
                            else ClGA.ren(ClGA.l1,ClGA.l2,ClGA.circin,ClGA.circout,corrx-2,corry-2,5);//�м䷽��
        for (int i=0;i<ClGA.l1.size();++i){
        attach(ClGA.l1[i]);
    }
    for (int i=0;i<ClGA.l2.size();++i){
        attach(ClGA.l2[i]);}
        for (int i=0;i<ClGA.circin.size();++i){
            attach(ClGA.circin[i]);
        }
        for (int i=0;i<ClGA.circout.size();++i){
            attach(ClGA.circout[i]);
        }
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
  case FL_Enter:
    for(int i=0; i<ClGA.M.PG_list.size();++i){
    PG pg;
    pg = ClGA.M.PG_list[i];
    cout<<pg.pg1corx;
    cout<<pg.pg2corx;
    if ((pg.pg1corx == corrx && pg.pg1cory == corry) || (pg.pg2corx == corrx && pg.pg2cory == corry)){
    if  (pg.pg1corx == corrx && pg.pg1cory == corry){
        ClGA.ball.move((pg.pg2corx-pg.pg1corx)*d,(pg.pg2cory-pg.pg1cory)*d);
        corrx = pg.pg2corx;
        corry = pg.pg2cory;
        ret = true;
    }
    else
    {   ClGA.ball.move((pg.pg1corx-pg.pg2corx)*d,(pg.pg1cory-pg.pg2cory)*d);
        corrx = pg.pg1corx;
        corry = pg.pg1cory;
        ret = true;
    }
    }
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