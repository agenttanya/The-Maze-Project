
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
   string timeline{"start"};
   Time(int x)
    {
        hour=x / 3600;
        min=(x % 3600) / 60;
        sec=x % 60;
    }
   void show();

   void tick();

   void run();
};
#endif

