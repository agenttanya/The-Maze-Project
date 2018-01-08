#ifndef WETRY_H
#define WETRY_H

#include <cmath>
#include "maze.h"
#include "GUI.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "Vector_ref.h"
#include "fltk.h"

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
