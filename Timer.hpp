//
//  Timer.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/8.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include "noncopy.h"
#include <functional>
#include <sys/time.h>
typedef std::function<void()> Timercallback;
class Timer:noncopy
{
public:
    Timer();
    ~Timer();
    void settimecallback(Timercallback& timecallback);
    
    void settime(struct timeval ti);
    struct timeval gettime();
private:
    Timercallback callback;
    struct timeval time;
};

#endif /* Timer_hpp */
