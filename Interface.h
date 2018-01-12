#ifndef INTERFACE_H
#define INTERFACE_H

#include "../Graph_lib/Window.h"
#include "../Graph_lib/Point.h"
#include "../Graph_lib/GUI.h"
#include "../Graph_lib/fltk.h"
#include "../Graph_lib/Vector_ref.h"
#include<string>
#include<iostream>
#include<vector>
#include"maze.h"
using namespace Graph_lib;

const int h {20};
const int w {20};
const char diff {'H'};

struct Track
{
  int x{0};
  int y{0};
  string dir{"no direction"};
  Track();
  Track(int xx,int yy, string t):x{xx},y{yy},dir{t}{};
};


//游戏区域（Game Area的缩写）
//它是用于实现游戏功能的，目前它其实是经典模式的游戏区域
struct GA {
    Graph_lib::Circle ball;
    maze M {w,h,diff};
    Graph_lib::Line b1;
    Graph_lib::Line b2;
    Graph_lib::Vector_ref<Graph_lib::Line> l1;
    Graph_lib::Vector_ref<Graph_lib::Line> l2;
    Graph_lib::Vector_ref<Graph_lib::Line> l3;
    Graph_lib::Vector_ref<Graph_lib::Text> arrow;
    Graph_lib::Text t{Point{100,100},"You make it!"};
    GA();
    vector<Track> trace;
    void ren(Graph_lib::Vector_ref<Graph_lib::Line>&l1,Graph_lib::Vector_ref<Graph_lib::Line>&l2, int rcox,int rcoy,int z);
    void tracing();
};

//界面（User Interface的缩写），包含了按钮等
struct UI{
    Vector_ref<Button> Buttons;
};

//窗口
struct GameWindow:public Graph_lib::Window{
    GameWindow();

    //主界面和游戏界面，以及一个切换的函数
    //每个界面都是一个UI类的成员
    UI MainUI;
    UI GameUI;
    UI* CurrUI;//这个指针指向了“当前”界面
    SwitchTo(UI& Next);


    //“经典”模式游戏的区域，Cl是Classical的缩写
    //我希望每种模式的游戏区域是不同的类，这个还没做
    GA ClGA;
    ShowClGA();
    HideClGA();

    //一堆按键的回调函数
    static void cb_quit(void*, void* pw) {
        static_cast<GameWindow*>(pw)->quit();
    }
    void quit() { hide(); }



    static void cb_start(void*, void* pw) {
        static_cast<GameWindow*>(pw)->start();
    }
    void start(){
        SwitchTo(GameUI);
        ShowClGA();
    }

    static void cb_back(void*, void* pw) {
        static_cast<GameWindow*>(pw)->back();
    }
    void back() {
        SwitchTo(MainUI);
        HideClGA();
    }

     static void cb_solution(void*, void* pw) {
        static_cast<GameWindow*>(pw)->solution();
    }
    void solution();

    //小球的移动
    bool handle_keydown(int key);
    int handle(int event);
    void spar();

};

#endif
