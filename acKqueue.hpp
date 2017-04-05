//
//  acKqueue.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/27.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef acKqueue_hpp
#define acKqueue_hpp

#include <stdio.h>
#include "Channel.hpp"
#include <vector>

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <map>
#endif /* acKqueue_hpp */

class EventLoop;

typedef std::vector<Channel*> channellist;
class acKqueue
{
public:
    acKqueue(EventLoop* loop);
    ~acKqueue();
    const char *aeApiName(void);
    //int aeApiAddEvent(EventLoop *eventLoop, int fd, int mask);
   // void aeApiDelEvent(EventLoop *eventLoop, int fd, int mask);
    int aeApiAddEvent(Channel* chan);
    void aeApiDelEvent(Channel* chan);
    int aeApiPoll(channellist* activechannel );
    
private:
    const int kqfd;
    std::vector<struct kevent>  events;
    EventLoop* eventloop;
    //std::map<const int,Channel* >  channelmap;
};