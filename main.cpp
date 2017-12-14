#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Vector_ref.h"
#include "Window.h"
#include <string>

using namespace std;


int main ()
{
 Simple_window win {Graph_lib::Point{100,100}, 600, 400, "Some shapes"};
// ⽣生成⼀一个矩形
Graph_lib::Rectangle rect {Gragh_lib::Point {200,200}, 100, 50};
// 将矩形交给窗⼝口管理理
win.attach(rect);
// 把控制权交给系统
return Graph_lib::gui_main();
}
