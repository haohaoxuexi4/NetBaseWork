//
//  Timer.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/8.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "Timer.hpp"

Timer::Timer()
{
    gettimeofday(&time, NULL);
}

Timer::~Timer()
{

}
void Timer::settimecallback(Timercallback& timecallback)
{
    callback=timecallback;
}

void Timer::settime(struct timeval ti)
{
    time.tv_sec=ti.tv_sec;
    time.tv_usec=ti.tv_usec;
}
struct timeval Timer::gettime()
{
    return time;
}