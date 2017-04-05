//
//  acKqueue.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/27.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "acKqueue.hpp"
#include <memory.h>
#include <string.h>
#include <unistd.h>

#define ININSIZE 500

acKqueue::acKqueue(EventLoop* loop):kqfd(kqueue()),eventloop(loop),events(ININSIZE)
{
   if(kqfd==-1)
   {
       printf("kqueue error kqfd==-1");
       return ;
   }
   // memset(&events,0,sizeof(struct kevent)*events.size());
}

acKqueue::~acKqueue()
{
    close(kqfd);
}
/*
static int aeApiCreate(aeEventLoop *eventLoop) {
    aeApiState *state = zmalloc(sizeof(aeApiState));
    
    if (!state) return -1;
    state->events = zmalloc(sizeof(struct kevent)*eventLoop->setsize);
    if (!state->events) {
        zfree(state);
        return -1;
    }
    state->kqfd = kqueue();
    if (state->kqfd == -1) {
        zfree(state->events);
        zfree(state);
        return -1;
    }
    eventLoop->apidata = state;
    return 0;
}

static int aeApiResize(aeEventLoop *eventLoop, int setsize) {
    aeApiState *state = eventLoop->apidata;
    
    state->events = zrealloc(state->events, sizeof(struct kevent)*setsize);
    return 0;
}

static void aeApiFree(aeEventLoop *eventLoop) {
    aeApiState *state = eventLoop->apidata;
    
    close(state->kqfd);
    zfree(state->events);
    zfree(state);
}
*/

/**************
int acKqueue::aeApiAddEvent(EventLoop *eventLoop, int fd, int mask) {
   // aeApiState *state = eventLoop->apidata;
    struct kevent ke;
    
    if (mask & EVFILT_READ) {
        EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        if (kevent(kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
        
        Channel* chan=new Channel(eventLoop,fd);
        channelmap.insert(make_pair(fd, chan));
    }
    if (mask & EVFILT_WRITE) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
        if (kevent(kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
        
        Channel* chan=new Channel(eventLoop,fd);
        channelmap.insert(make_pair(fd, chan));
    }
    return 0;
}

void acKqueue::aeApiDelEvent(EventLoop *eventLoop, int fd, int mask) {
    //aeApiState *state = eventLoop->apidata;
    struct kevent ke;
    
    if (mask & EVFILT_READ) {
        EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kevent(kqfd, &ke, 1, NULL, 0, NULL);
        
    }
    if (mask & EVFILT_WRITE) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        kevent(kqfd, &ke, 1, NULL, 0, NULL);
    }
    
    channelmap.erase(fd);
}


*/


int acKqueue::aeApiAddEvent(Channel* chan) {
    
    struct kevent ke;
    int mask=chan->getmask();
    int fd=chan->getfd();
    
    if (mask & EVFILT_READ) {
        EV_SET(&ke, fd, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, chan);
        if (kevent(kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
    }
    if (mask & EVFILT_WRITE) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD|EV_ENABLE, 0, 0, chan);
        if (kevent(kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
        
    }
    
    return 0;
}

void acKqueue::aeApiDelEvent(Channel* chan) {
    int mask=chan->getmask();
    int fd=chan->getfd();
    
    struct kevent ke;
    
    if (mask & EVFILT_READ) {
        EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kevent(kqfd, &ke, 1, NULL, 0, NULL);
        
    }
    if (mask & EVFILT_WRITE) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        kevent(kqfd, &ke, 1, NULL, 0, NULL);
    }
    

}
int acKqueue::aeApiPoll(channellist* activechannel) {
    
    int retval, numevents = 0;
    
    //if (tvp != NULL) {
        struct timespec timeout;
        timeout.tv_sec = 2;
        timeout.tv_nsec = 2 * 1000;
    
        retval=kevent(kqfd, NULL, 0, &(*events.begin()),(int)events.size(), &timeout);

    //} else {
      //  retval = kevent(kqfd, NULL, 0, &(*events.begin()),(int)events.size(),NULL);
   // }
    
    
    if (retval > 0) {
        
        printf("retval=%d\n",retval);
       // sleep(3);
        numevents = retval;
        
        for (auto iter=events.begin();iter!=events.end(); iter++) {
            if((*iter).filter==EVFILT_READ)
            {
                Channel* chan=(Channel*)((*iter).udata);
                chan->setflag(EVFILT_READ);
                //chan->flags=EVFILT_READ;
                //chan->handleReadyEvent();
                //chan->flags=EVFILT_READ;
                activechannel->push_back(chan);
                //printf("actie channelsize=%d",activechannel.size());
            }
            if((*iter).filter==EVFILT_WRITE)
            {
                Channel* chan= (Channel*)((*iter).udata);
                chan->setflag(EVFILT_WRITE);
                activechannel->push_back(chan);
            }
        }
       
    }
    return numevents;
}
/*
char* acKqueue::aeApiName(void) {
    return "kqueue";
}
*/