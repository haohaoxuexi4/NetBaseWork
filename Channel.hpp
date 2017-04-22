//
//  Channel.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/23.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef Channel_hpp
#define Channel_hpp

#include <stdio.h>
#include "noncopy.h"
#include <functional>

using namespace std;

const int KqNoneEvent=0;   //初始状态
const int KqReadEvent=-1; //EVFILT_READ;
const int KqWriteEvent=-2; //EVFILT_WRITE
class EventLoop;
typedef std::function<void ()> Fun;
class Channel:public noncopy{
public:
    Channel(EventLoop* loop,int fd);
    ~Channel();
    void handleReadyEvent(); //channel核心函数，根据事件，调用相关的处理函数
    
    void   addtoloop();
    void   removetoloop();
    int    getevents(){ return events_;};
    void   setevents(int event) {events_=event;};
    int    getflag(){ return flags;};
    void   setflag(int flag) {flags=flag;};
    int             getfd(){return fd_;};
    
    
    void enableReading() { events_ = KqReadEvent; addtoloop(); }
    void enableWriting() { events_ = KqWriteEvent; addtoloop(); }
    
    void enableReadingWriting(){events_=(KqReadEvent|KqWriteEvent);addtoloop();}
    
    void disableWriting() { events_ = KqWriteEvent; removetoloop(); }
    void disableReading() { events_ = KqReadEvent; removetoloop(); }
    
     /*
    void enableWriting() { events_ |= KqWriteEvent; addtoloop(); }
    void disableWriting() { events_ &= ~KqWriteEvent; removetoloop(); }
    void disableAll() { events_ = KqNoneEvent; removetoloop(); }
    */
    bool isWriting() const { return events_ & KqWriteEvent; }
    bool isReading() const { return events_ & KqReadEvent; }

   // void update(){}
    void setreadEvent(const Fun& cb)
    {
        readevent=cb;
    };
    
    void setwriteEvent(const Fun& cb)
    {
        writeEvent=cb;
    }
    void setcloseEvent(const Fun& cb)
    {
        closeEvent=cb;
    }
private:
    
    const int fd_;
    int  flags;//事件标识  // revents
    int   events_;    //事件标识
    Fun  readevent;   //可读
    Fun   writeEvent;  //可写
    Fun  closeEvent;  //关闭
    EventLoop* eventloop;
};

#endif /* Channel_hpp */
