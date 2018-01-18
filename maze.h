#ifndef MAZE_H
#define MAZE_H
#include"time.h"
#include<vector>
#include<cmath>
using namespace std;

struct block{
    bool east;
    bool north;
    bool footprint;
};

struct coor{
    int x;
    int y;
    coor *next;
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
    int pgpairs;
    vector<vector<block> > block_list;
    vector<PG> PG_list;
    vector<vector<coor>> area_list;
    int zones;
    maze (int h=0,int w=0,char difficulty='N',bool pg = 0) {
        height=h;
        width=w;
    if (pg==0){
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
    } else {
        height=h;
        width=w;
        switch (difficulty){
        case 'E':
            zones=log(height*width)/3;
            break;
        case 'N':
            zones=log(height*width)/2.5;
            break;
        case 'H':
            zones=log(height*width)/2;
            break;
        }
            pgpairs=zones*(zones-1)/2;
            pgrandom_construct();
            for(int i=0;i<zones;++i){
            for(int j=0;j<i;++j){
            PG pgate = passing_gates(i,j);
            PG_list.push_back(pgate);
            }
            }
    }
    }
    private:
    void random_construct1();
    void random_construct2();
    void random_construct3();
    void pgrandom_construct();
    PG passing_gates(int a,int b);//a function to generate passing gates
    void division(int x1,int x2,int y1,int y2);
};
#endif
