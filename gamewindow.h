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


    bool Cl{false};
    bool Tr{false};


    GameWindow();

    UI MainUI;//初始界面
    UI PreClUI;//准备进入经典游戏界面
    UI ClGameUI;//经典游戏界面
    UI PreTrUI;//准备进入传送门游戏界面
    UI TrGameUI;//传送门游戏界面
    UI* CurrUI;//这个指针指向了“当前”界面
    SwitchTo(UI& Next);


    //“经典”模式游戏的区域，Cl是Classical的缩写
    GC ClGA;
    ShowClGA();
    HideClGA();
    void Cltimeout();
    void Clmanage_timeout();
    static void cb_Cltimeout(void* pw) {static_cast<GameWindow*>(pw)->Cltimeout();}

    //传送门游戏的区域，Tr是transmission的缩写
    GT TrGA;
    ShowTrGA();
    HideTrGA();
    void Trtimeout();
    void Trmanage_timeout();
    static void cb_Trtimeout(void* pw) {static_cast<GameWindow*>(pw)->Trtimeout();}

    //初始界面的quit
    static void cb_quit(void*, void* pw) {
        static_cast<GameWindow*>(pw)->quit();
    }
    void quit() { hide(); }


    //初始界面进入经典游戏准备
    static void cb_Classical(void*, void* pw) {
        static_cast<GameWindow*>(pw)->PreClassical();
    }
        void PreClassical(){
        SwitchTo(PreClUI);
    }


    //初始界面进入传送门游戏
    static void cb_Transmission(void*, void* pw) {
        static_cast<GameWindow*>(pw)->PreTransmission();
    }
    void PreTransmission(){
        SwitchTo(PreTrUI);
    }

        //经典游戏准备进入经典游戏
    static void cb_Clstart(void*, void* pw) {
        static_cast<GameWindow*>(pw)->Classical();
    }
        void Classical(){
        SwitchTo(ClGameUI);
        ShowClGA();
    }


    //传送门游戏准备进入传送门游戏
    static void cb_Trstart(void*, void* pw) {
        static_cast<GameWindow*>(pw)->Transmission();
    }
    void Transmission(){
        SwitchTo(TrGameUI);
        ShowTrGA();
    }

    //两种模式中返回初始界面
    static void cb_back(void*, void* pw) {
        static_cast<GameWindow*>(pw)->back();
    }
    void back() {
        SwitchTo(MainUI);
        if(Cl == true){
        HideClGA();
        }
        else if(Tr==true){
        HideTrGA();
        }
    }

    //小球的移动
    bool Clhandle_keydown(int key);
    bool Trhandle_keydown(int key);
    int handle(int event);

    void Clspar();
    void Trspar();

};

#endif
