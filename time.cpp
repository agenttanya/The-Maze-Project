#include "time.h"
#include<string>
#include<iostream>
#include<ctime>
using namespace std;
void Time::show()
    {   timeline.clear();
        cout << '\r';
        if(hour<10) timeline="0";
            //cout << 0;
        //cout << hour << ':';
        timeline+=hour;timeline+=':';
        if(min<10) timeline+='0';
        //cout << 0;
        //cout << min << ':';
           timeline+=min;timeline+=':';
        if(sec<10)
        //cout << 0;
        //cout << sec << flush;
         timeline+=sec;
       }

//////////////////////////////////////////
 void Time::tick()
      {
           long t=time(NULL);
          while(time(NULL)==t);

          if(sec==0&&min==0&&hour==0)return;

            if(--sec<0)
            {
                sec=59;
                 if(--min<0)
                {
                   min=59;
                  --hour;

                }
            }
      }


///////////////////////////////
 void Time::run()
     {
            tick();
            show();


     }
