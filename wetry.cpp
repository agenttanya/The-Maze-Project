#include"wetry.h"
using namespace std;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Color;

constexpr int x0 {60};
constexpr int y0 {80};
constexpr int dx {20};
constexpr int dy {20};
int corrx{0};
int corry{0};

My_window::My_window(Point xy, int w, int h, const maze& firstmaze, const string& title)
  : Graph_lib::Window{xy, w, h, title},
    x{x_max()/2}, y{y_max()/2}, ball{Point{65,85}, 5}
{
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
  }
  return ret;
}
