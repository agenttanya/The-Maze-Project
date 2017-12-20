#include <cmath>
#include "maze.h"
#include "../Graph_lib/GUI.h"
#include "../Graph_lib/Graph.h"
#include "../Graph_lib/Window.h"
#include "../Graph_lib/Point.h"
#include "../Graph_lib/Vector_ref.h"
#include "../Graph_lib/fltk.h"

using namespace std;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Color;

using namespace std;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Color;


class My_window : public Graph_lib::Window {

public:

  My_window(Point xy, int w, int h, const maze& firstmaze, const string& title);

private:

  Graph_lib::Button quit_button;
  int x;
  int y;
  vector<vector<block>> blockset;
  int width;
  int height;
  Graph_lib::Circle ball;

  // callback for quit_button
  static void cb_quit(void*, void* pw) {
    static_cast<My_window*>(pw)->quit();
  }

  void quit() { hide(); }

  bool handle_keydown(int key);

  int handle(int event);

};





/*class My_window : public Graph_lib::Window {

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
*/
