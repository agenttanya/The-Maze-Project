#include "Interface.h"
#include<iostream>
using Graph_lib::Point;
using Graph_lib::Window;

const int WindowWidth {350};
const int WindowHeight {350};
const std::string Title {"The Maze Game"};
const Point P {0,0};

const int x0 {60};
const int y0 {80};
const int d {10};
int corrx{0};
int corry{0};
const int ball_d {5};

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
    attach(ClGA.b1);
    attach(ClGA.b2);
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
    detach(ClGA.b1);
    detach(ClGA.b2);
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
    GameUI.Buttons.push_back(quit_button2);
    GameUI.Buttons.push_back(back_button);

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
    for (int i=0;i<M.width;++i){
        for (int j=0;j<M.height;++j) {
            if (M.block_list[i][j].east==1 && (i!=M.width-1||j!=M.height-1)){
                l1.push_back(new Graph_lib::Line{Point{x0+(i+1)*d,y0+d*j},Point{x0+d*(i+1),y0+d*(j+1)}});
                l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
            if (M.block_list[i][j].north==1){
                l2.push_back(new Graph_lib::Line{Point{x0+(i+1)*d,y0+(j+1)*d},Point{x0+d*i,y0+d*(j+1)}});
                l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            }
        }
    }
}

bool GameWindow::handle_keydown(int key)
{
  bool ret = false;
  switch (key) {
  case FL_Up:
    if (ClGA.M.block_list[corrx][corry-1].north == 0 && corry != 0){
        ClGA.ball.move(0, -d);
        ret = true;
        corry -= 1;
    }
    break;
  case FL_Down:
    if (ClGA.M.block_list[corrx][corry].north == 0 && corry !=ClGA.M.height-1)
    {ClGA.ball.move(0, d); ret = true;corry += 1;}
    break;
  case FL_Left:
    if (ClGA.M.block_list[corrx-1][corry].east == 0 && corrx != 0)
    {ClGA.ball.move(-d, 0); ret = true;corrx -= 1;}
    break;
  case FL_Right:
    if (ClGA.M.block_list[corrx][corry].east == 0 && corrx != ClGA.M.width-1)
    {ClGA.ball.move(d, 0); ret = true;corrx += 1;}
    break;
  }
  if (ret) Fl::redraw();
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
