
#ifndef TIME_H
#define TIME_H
#include<ctime>
#include <iostream>
using namespace std;

class Time{

public:
   int hour;
   int min;
   int sec;
   string timeline{" "};
   Time(int a,int b,int c)
    {
        hour=a;
        min=b;
        sec=c;
    }
   void show();

   void tick();

   void run();
};
#endif

