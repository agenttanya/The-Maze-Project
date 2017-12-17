#include<iostream>
#include"maze.h"
#include"Simple_window.h"
#include"Graph.h"
#include"Vector_ref.h"
#include"wetry.h"
using namespace std;
using Graph_lib::Point;
using Graph_lib::Color;
using Graph_lib::Line_style;


int main()
{
    int height,width;
    char difficulty;
    cout<<"Please input the size and difficulty: ";
    cin>>width>>height>>difficulty;//cin �������Լ���Ƽ����ļ�������Ϊ�ص����Ѷȣ����⣬���û����뻹�ǻ���ָ��ָ�����bug���������Լ����ü����Ѷ����飬��Ϊ�����Ѷ�Ҳ�����Ȼ����ͼ�ν����ϸ��button����ʽ
    My_window win {Point{100,0}, x0+12*width, y0+12*height, "Move a ball"};
    maze firstmaze= {width,height,difficulty};
    Graph_lib::Line b1 {Point{x0,y0},Point{dx*width+x0,y0}};
    b1.set_style(Line_style{Line_style::solid,2});
    win.attach(b1);
    Graph_lib::Line b2 {Point{x0,y0},Point{x0,dy*height+y0}};
    b2.set_style(Line_style{Line_style::solid,2});
    win.attach(b2);
    Graph_lib::Vector_ref<Graph_lib::Line> l1,l2;
    for (int i=0;i<width;++i){
    for (int j=0;j<height;++j) {
        if (firstmaze.block_list[i][j].east==1){
            l1.push_back(new Graph_lib::Line{Point{x0+(i+1)*dx,y0+dy*j},Point{x0+dx*(i+1),y0+dy*(j+1)}});
            l1[l1.size()-1].set_style(Line_style{Line_style::solid, 2});
            win.attach(l1[l1.size()-1]);
        }
        if (firstmaze.block_list[i][j].north==1){
            l2.push_back(new Graph_lib::Line{Point{x0+(i+1)*dx,y0+(j+1)*dy},Point{x0+dx*i,y0+dy*(j+1)}});
            l2[l2.size()-1].set_style(Line_style{Line_style::solid, 2});
            win.attach(l2[l2.size()-1]);
        }
    }
    }
    return Graph_lib::gui_main();
}
