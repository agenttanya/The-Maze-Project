#ifndef MAZE_H
#define MAZE_H

#include<vector>
using namespace std;

struct block{
    bool east;
    bool north;
    bool footprint;
};

struct coor{
    int x;
    int y;
};

struct maze{
    int height;
    int width;
    vector<vector<block> > block_list;
    int pass_gate1;
    int pass_gate2;
    int num_of_walls;
    int num_walls0;
    bool pg1east;
    bool pg2east;
    int pg1corx;
    int pg1cory;
    int pg2corx;
    int pg2cory;
    maze (int h=0,int w=0,char difficulty='N') {
        height=h;
        width=w;
        switch (difficulty){
        case 'E':
            random_construct3();
            break;
        case 'N':
            random_construct1();
            break;
        case 'H':
            random_construct2();
            break;
        }
        passing_gates();
    }
    private:
    void random_construct1();
    void random_construct2();
    void random_construct3();
    void passing_gates();//a function to generate passing gates
    void division(int x1,int x2,int y1,int y2);
};
#endif
