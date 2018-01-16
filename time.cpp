#include "time.h"
#include<string>
#include<iostream>
#include<ctime>
#include<sstream>
using namespace std;
void Time::show()
    {
        timeline.clear();
        ostringstream os;
        cout<< '\r';
        if(hour<10) os << 0;
        os << hour << ':';
        if(min<10) os<< 0;
        os << min << ':';
        if(sec<10) os<< 0;
         os<< sec << flush;
         timeline=os.str().c_str();
         cout<<timeline<<endl;
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
