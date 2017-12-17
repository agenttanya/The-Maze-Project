#include <cmath>

#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace std;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Color;
constexpr int x0 {60};
constexpr int y0 {80};
constexpr int dx {10};
constexpr int dy {10};



class My_window : public Graph_lib::Window {

public:

  My_window(Point xy, int w, int h, const string& title);

private:

  Graph_lib::Button up_button;
  Graph_lib::Button down_button;
  Graph_lib::Button left_button;
  Graph_lib::Button right_button;

  double x{75};
  double y{85};
  Graph_lib::Circle ball;


  // callback for quit_button
  static void cb_up(void*, void* pw) {
    static_cast<My_window*>(pw)->up();
  }

  void up();

  // callback for next_button
  static void cb_down(void*, void* pw) {
    static_cast<My_window*>(pw)->down();
  }

  void down();

   static void cb_left(void*, void* pw) {
    static_cast<My_window*>(pw)->left();
  }

  void left();

   static void cb_right(void*, void* pw) {
    static_cast<My_window*>(pw)->right();
  }

  void right();
};
