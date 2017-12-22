#ifndef WETRY_H
#define WETRY_H

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

class My_window : public Graph_lib::Window {

public:

  My_window(Point xy, int w, int h, const maze& firstmaze, const string& title);

private:

  int x;
  int y;
  vector<vector<block>> blockset;
  int width;
  int height;
  Graph_lib::Circle ball;

  bool handle_keydown(int key);

  int handle(int event);

};
#endif
