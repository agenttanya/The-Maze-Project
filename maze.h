#include<map>
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
    }
    private:
    void random_construct1();
    void random_construct2();
    void random_construct3();
    void division(int x1,int x2,int y1,int y2);
};
