#include<iostream>
#include<stdlib.h>
#include<stack>
#include"maze.h"
using namespace std;

//深度优先

void maze::random_construct1(){
    for (int i=0;i<width;++i){
        block_list.push_back(vector<block> {});
        for (int j=0;j<height;++j){
            block_list[i].push_back({1,1,0});
        }
    }
    coor temp {0,0};
    block_list[temp.x][temp.y].footprint=1;
    stack<coor> history;
    vector<int> dir;
    int dirtemp;
    srand((unsigned)time(0));
    ////cout<<"Initialized!\n";
    do {
        if  (temp.x<width-1 && block_list[temp.x+1][temp.y].footprint==0){
            dir.push_back(0);
            //cout<<"E is available.\n";
        }
        if  (temp.y<height-1 && block_list[temp.x][temp.y+1].footprint==0){
            dir.push_back(1);
            //cout<<"N is available.\n";
        }
        if  (temp.x>0 && block_list[temp.x-1][temp.y].footprint==0){
            dir.push_back(2);
            //cout<<"W is available.\n";
        }
        if  (temp.y>0 && block_list[temp.x][temp.y-1].footprint==0){
            dir.push_back(3);
            //cout<<"S is available.\n";
        }
        //cout<<"Direction size is: "<<dir.size()<<endl;
        //cout<<"Available directions are: ";
        if (dir.size()!=0){
            for (int i=0;i<dir.size()-1;++i){
                //cout<<dir[i]<<' ';
            }
        }
        //cout<<endl;
        if (!dir.empty()){
            history.push(temp);
            //cout<<"Stack size is: "<<history.size()<<endl;
            dirtemp=dir[rand()%dir.size()];
            //cout<<dirtemp<<" is chosen.\n";
            //cout<<dir.empty()<<endl;
            switch(dirtemp){
                case 0:
                block_list[temp.x][temp.y].east=0;
                temp={temp.x+1,temp.y};
                break;
                case 1:
                block_list[temp.x][temp.y].north=0;
                temp={temp.x,temp.y+1};;
                break;
                case 2:
                block_list[temp.x-1][temp.y].east=0;
                temp={temp.x-1,temp.y};
                break;
                case 3:
                block_list[temp.x][temp.y-1].north=0;
                temp={temp.x,temp.y-1};
                break;
            }
            block_list[temp.x][temp.y].footprint=1;
            //use rand to generate random numbers for the position of transfer gates
            //cout<<"Run to "<<temp.x<<","<<temp.y<<'\n';
        } else {
            temp=history.top();
            history.pop();
            //cout<<"Stack size is: "<<history.size()<<endl;
            //cout<<"No availble direction, run to "<<temp.x<<","<<temp.y<<'\n';
        }
        dir.clear();
    } while (!history.empty());
    //cout<<"Construction complete!";
}

//随机Prim

void maze::random_construct2(){
    for (int i=0;i<width;++i){
        block_list.push_back(vector<block> {});
        for (int j=0;j<height;++j){
            block_list[i].push_back({1,1,0});
        }
    }
    vector<coor> visited;
    vector<int> dir;
    int dirtemp;
    srand((unsigned)time(0));
    coor temp {0,0};
    visited.push_back(temp);
    block_list[temp.x][temp.y].footprint=1;
    while (visited.size()!=width*height){
        temp=visited[rand()%visited.size()];
        //cout<<temp.x<<","<<temp.y<<" chosen"<<endl;
        if  (temp.x<width-1 && block_list[temp.x+1][temp.y].footprint==0){
            dir.push_back(0);
            //cout<<"E is available.\n";
        }
        if  (temp.y<height-1 && block_list[temp.x][temp.y+1].footprint==0){
            dir.push_back(1);
            //cout<<"N is available.\n";
        }
        if  (temp.x>0 && block_list[temp.x-1][temp.y].footprint==0){
            dir.push_back(2);
            //cout<<"W is available.\n";
        }
        if  (temp.y>0 && block_list[temp.x][temp.y-1].footprint==0){
            dir.push_back(3);
            //cout<<"S is available.\n";
        }
        if (dir.size()!=0){
            for (int i=0;i<dir.size()-1;++i){
                //cout<<dir[i]<<' ';
            }
        }
        //cout<<endl;
        if (!dir.empty()){
            dirtemp=dir[rand()%dir.size()];
            //cout<<dirtemp<<" is chosen.\n";
            //cout<<dir.empty()<<endl;
            switch(dirtemp){
                case 0:
                block_list[temp.x][temp.y].east=0;
                temp={temp.x+1,temp.y};
                break;
                case 1:
                block_list[temp.x][temp.y].north=0;
                temp={temp.x,temp.y+1};;
                break;
                case 2:
                block_list[temp.x-1][temp.y].east=0;
                temp={temp.x-1,temp.y};
                break;
                case 3:
                block_list[temp.x][temp.y-1].north=0;
                temp={temp.x,temp.y-1};
                break;
            }
            dir.clear();
            block_list[temp.x][temp.y].footprint=1;
            visited.push_back(temp);
            //cout<<"Visited "<<temp.x<<","<<temp.y<<'\n';
        }
    }
}

//递归分割

int random(int a,int b){
    return rand()%(b-a+1)+a;
}

void maze::random_construct3(){
    srand((unsigned)time(0));
    for (int i=0;i<width;++i){
        block_list.push_back(vector<block> {});
        for (int j=0;j<height;++j){
            block_list[i].push_back({0,0,0});
        }
    }
    division(0,width-1,0,height-1);
    for (int i=0;i<width;++i){
        block_list[i][height-1].north=1;
    }
    for (int j=0;j<height;++j){
        block_list[width-1][j].east=1;
    }
    return;
}


    void maze::division(int x1,int x2,int y1,int y2){
        if (x1==x2 || y1==y2) return;
        int xm=rand()%(x2-x1)+x1;
        int ym=rand()%(y2-y1)+y1;
        //cout<<"divide point: "<<xm<<","<<ym<<endl;
        for (int i=x1;i<=x2;++i) {
            block_list[i][ym].north=1;
            //cout<<"wall built "<<i<<","<<ym<<endl;
        }
        for (int i=y1;i<=y2;++i) {
            block_list[xm][i].east=1;
            //cout<<"wall built "<<ym<<","<<i<<endl;
        }
        int xd1=rand()%(xm-x1+1)+x1;
        block_list[xd1][ym].north=0;
        int xd2=rand()%(x2-xm)+xm+1;
        block_list[xd2][ym].north=0;
        int yd1=rand()%(ym-y1+1)+y1;
        block_list[xm][yd1].east=0;
        int yd2=rand()%(y2-ym)+ym+1;
        block_list[xm][yd2].east=0;

        vector<int> a;
        for (int i=0;i<3;++i){
            a.push_back(1);
        }
        int wall;
        wall=rand()%a.size();
        int mmm=rand()%(block_list[width-1][height-1].east+4);

        //cout<<"wall is "<<mmm<<endl;
        switch (wall){
        case 0:
            block_list[xd1][ym].north=1;
            break;
        case 1:
            block_list[xd2][ym].north=1;
            break;
        case 2:
            block_list[xm][yd1].east=1;
            break;
        case 3:
            block_list[xm][yd2].east=1;
            break;
        }
        division(x1,xm,y1,ym);
        division(x1,xm,ym+1,y2);
        division(xm+1,x2,y1,ym);
        division(xm+1,x2,ym+1,y2);
    }


    //////////////////////
    void maze::pgrandom_construct(){
    int ifempty{0};
    vector<stack<coor>> history;
    for (int i=0;i<width;++i){
        block_list.push_back(vector<block> {});
        for (int j=0;j<height;++j){
            block_list[i].push_back({1,1,0});
        }
    }
    coor temp;
    srand((unsigned)time(0));
    for (int i=0;i<zones;++i){
    if(i==0) temp = {0,0};
    else if(i==1) temp = {width-1,height-1};
    else
    {    for (int j=0;j<area_list.size();++j){
         coor tempini = area_list[j][1];
         while(temp.x == tempini.x && temp.y == tempini.y)temp = {rand()%width,rand()%height};}
    }

    area_list.push_back(vector<coor> {});
    stack<coor> st{};
    history.push_back(st);
    area_list[i].push_back(temp);
    block_list[temp.x][temp.y].footprint=1;

    }
    vector<int> dir;
    int dirtemp;
    ////cout<<"Initialized!\n";
    do {
        for (int i=0;i<zones;++i){
            coor temp = area_list[i][area_list[i].size()-1];
            if  (temp.x<width-1 && block_list[temp.x+1][temp.y].footprint==0){
                dir.push_back(0);
                //cout<<"E is available.\n";
                }
            if  (temp.y<height-1 && block_list[temp.x][temp.y+1].footprint==0){
                dir.push_back(1);
                //cout<<"N is available.\n";
                }
            if  (temp.x>0 && block_list[temp.x-1][temp.y].footprint==0){
                dir.push_back(2);

                //cout<<"W is available.\n";
                }
            if  (temp.y>0 && block_list[temp.x][temp.y-1].footprint==0){
                dir.push_back(3);
                //cout<<"S is available.\n";
                }
            //cout<<"Direction size is: "<<dir.size()<<endl;
            //cout<<"Available directions are: ";
           // if (dir.size()!=0){
            //for (int i=0;i<dir.size()-1;++i){
                //cout<<dir[i]<<' ';
            //}
        //cout<<endl;
        if (!dir.empty()){
            history[i].push(temp);
            //cout<<"Stack size is: "<<history.size()<<endl;
            dirtemp=dir[rand()%dir.size()];
            //cout<<dirtemp<<" is chosen.\n";
            //cout<<dir.empty()<<endl;
            switch(dirtemp){
                case 0:
                block_list[temp.x][temp.y].east=0;
                temp={temp.x+1,temp.y};
                break;
                case 1:
                block_list[temp.x][temp.y].north=0;
                temp={temp.x,temp.y+1};;
                break;
                case 2:
                block_list[temp.x-1][temp.y].east=0;
                temp={temp.x-1,temp.y};
                break;
                case 3:
                block_list[temp.x][temp.y-1].north=0;
                temp={temp.x,temp.y-1};
                break;
            }
            block_list[temp.x][temp.y].footprint=1;
            area_list[i].push_back(temp);
            //use rand to generate random numbers for the position of transfer gates
            //cout<<"Run to "<<temp.x<<","<<temp.y<<'\n';
        } else {
            if(!history[i].empty()){
            temp=history[i].top();
            history[i].pop();
            area_list[i].push_back(temp);
            }
            //cout<<"Stack size is: "<<history.size()<<endl;
            //cout<<"No availble direction, run to "<<temp.x<<","<<temp.y<<'\n';
        }
        int emp = history[i].empty();
        ifempty += emp;
        dir.clear();
           }
    }while(ifempty != zones);
}

        PG maze::passing_gates(int a,int b){
            PG pg;
            int PG1 = rand()%(area_list[a].size());
            int PG2 = rand()%(area_list[b].size());
            pg.pg1corx = area_list[a][PG1].x;
            pg.pg1cory = area_list[a][PG1].y;
            pg.pg2corx = area_list[b][PG2].x;
            pg.pg2cory = area_list[b][PG2].y;
            return pg;
    }
