#include"wetry.h"
using namespace std;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Color;

constexpr int x0 {60};
constexpr int y0 {80};
constexpr int dx {10};
constexpr int dy {10};
int corrx{0};
int corry{0};

/*#include <cmath>

#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace std;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Color;

class My_window : public Graph_lib::Window {

public:

  My_window(Point xy, int w, int h, const string& title);

private:

  Graph_lib::Button quit_button;
  Graph_lib::Button next_button;
  int center_x;
  int center_y;
  int radius;
  double phi;
  double x;
  double y;
  Graph_lib::Circle ball;

  double new_x() const { return center_x + radius*cos(phi); }
  double new_y() const { return center_y + radius*sin(phi); }

  // callback for quit_button
  static void cb_quit(void*, void* pw) {
    static_cast<My_window*>(pw)->quit();
  }

  void quit() { hide(); }

  // callback for next_button
  static void cb_next(void*, void* pw) {
    static_cast<My_window*>(pw)->next();
  }

  void next();

};*/

My_window::My_window(Point xy, int w, int h, const maze& firstmaze, const string& title)
  : Graph_lib::Window{xy, w, h, title},
    quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit},
    x{x_max()/2}, y{y_max()/2}, ball{Point{65,85}, 5}
{
  attach(quit_button);
  ball.set_style(Line_style{Line_style::solid, 1});
  ball.set_fill_color(Color::red);
  ball.set_color(Color::red);
  attach(ball);
  blockset= firstmaze.block_list;
  width = firstmaze.width;
  height = firstmaze.height;
}


bool My_window::handle_keydown(int key)
{
  bool ret = false;
  constexpr int d {10};
  switch (key) {
  case FL_Up:
    if (blockset[corrx][corry-1].north == 0 && corry != 0)
    {ball.move(0, -d); y -= d; ret = true; corry -= 1;}
    break;
  case FL_Down:
    if (blockset[corrx][corry].north == 0 && corry != height-1)
    {ball.move(0, d); y += d; ret = true;corry += 1;}
    break;
  case FL_Left:
    if (blockset[corrx-1][corry].east == 0 && corrx != 0)
    {ball.move(-d, 0); x -= d; ret = true;corrx -= 1;}
    break;
  case FL_Right:
    if (blockset[corrx][corry].east == 0 && corrx != width-1)
    {ball.move(d, 0); x += d; ret = true;corrx += 1;}
    break;
  }
  if (ret) Fl::redraw();
  return ret;
}

/*bool My_window::handle_mousepush(int button, int ex, int ey)
{
  if (button != FL_LEFT_MOUSE) return false;
  ball.move(ex-x, ey-y);
  x = ex;
  y = ey;
  Fl::redraw();
  return true;
}*/

int My_window::handle(int event)
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
  /*case FL_PUSH:
    if (handle_mousepush(Fl::event_button(), Fl::event_x(), Fl::event_y())) ret = 1;
    break;*/

  }
  return ret;
}


/*My_window::My_window(Point xy, int w, int h, const string& title)
  : Graph_lib::Window{xy, w, h, title},
    up_button{Point{0, 0}, 50, 20, "up", cb_up},
    down_button{Point{0, 20},50, 20, "down", cb_down},
    left_button{Point{0, 40}, 50, 20, "left", cb_left},
    right_button{Point{0, 60}, 50, 20, "right", cb_right},

 ball{Point{int(x),int(y)}, 3}
{
  attach(up_button);
  attach(down_button);
  attach(left_button);
  attach(right_button);
  ball.set_style(Line_style{Line_style::solid, 4});
  ball.set_fill_color(Color::red);
  ball.set_color(Color::red);
  attach(ball);
}

void My_window::down()
{
  constexpr double downline = 5;

  ball.move(0, downline);
  x = x;
  y = y+downline;
  Fl::redraw();
}
void My_window::up()
{
  constexpr double upline = -5;

  ball.move(0, upline);
  x = x;
  y = y+upline;
  Fl::redraw();
}
void My_window::right()
{
  constexpr double rightline = 5;
  ball.move(rightline, 0);
  x = x+rightline;
  y = y;
  Fl::redraw();
}
void My_window::left()
{
  constexpr double leftline =- 5;
  ball.move(leftline, 0);
  x = x+leftline;
  y = y;
  Fl::redraw();
}*/



/*int main()
{
  My_window win {Point{100,100}, 600, 400, "Move a ball"};

  return Graph_lib::gui_main();
}*/
