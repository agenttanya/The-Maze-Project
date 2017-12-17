#include"wetry.h"
using namespace std;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Color;


My_window::My_window(Point xy, int w, int h, const string& title)
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
}



/*int main()
{
  My_window win {Point{100,100}, 600, 400, "Move a ball"};

  return Graph_lib::gui_main();
}*/
