#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../Graph_lib/GUI.h"
#include "Vector_ref.h"
#include<string>
#include<iostream>
#include<vector>
#include"maze.h"
#include"gamearea.h"
using namespace Graph_lib;

const int WindowWidth {400};
const int WindowHeight{400};
const std::string Title {"The Maze Game"};
const Point P {0,0};

const int CenterX {200};//小球的位置
const int CenterY {200};
const int WallWidth {20};//墙宽度
const int VisibleRadius {5};//显示的半径
const int BallWidth {5};//球半径


//界面（User Interface的缩写），包含了按钮等
struct UI{
    Vector_ref<Button> Buttons;
};

//窗口
struct GameWindow:public Graph_lib::Window{

    int corrx{0};
    int corry{0};



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

    void timeout();
    void manage_timeout();
    static void cb_timeout(void* pw) {
    static_cast<GameWindow*>(pw)->timeout();
  }


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
/*
     static void cb_solution(void*, void* pw) {
        static_cast<GameWindow*>(pw)->solution();
    }
    void solution();
*/
    //小球的移动
    bool handle_keydown(int key);
    int handle(int event);
    void spar();

};

#endif
