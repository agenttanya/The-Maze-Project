#ifndef MAZE_H
#define MAZE_H
#include"time.h"
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

struct PG{
    int pg1corx;
    int pg1cory;
    int pg2corx;
    int pg2cory;
};

struct maze{
    int height;
    int width;
    vector<vector<block> > block_list;
    vector<PG> PG_list;
    maze (int h=0,int w=0,char difficulty='N',int pgpairs = 0) {
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
        for(int i=0;i<pgpairs;++i){
        PG pgate = passing_gates();
        PG_list.push_back(pgate);
        }
    }
    private:
    void random_construct1();
    void random_construct2();
    void random_construct3();
    PG passing_gates();//a function to generate passing gates
    void division(int x1,int x2,int y1,int y2);
};
#endif
