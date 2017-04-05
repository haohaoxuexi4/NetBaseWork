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
class EventLoop;
typedef std::function<void ()> Fun;
class Channel:public noncopy{
public:
    Channel(EventLoop* loop,int fd);
    ~Channel();
    void handleReadyEvent(); //channel核心函数，根据事件，调用相关的处理函数
    
    void   addtoloop();
    void   removetoloop();
    int    getmask(){ return mask_;};
    void   setmask(int mask) {mask_=mask;};
    int    getflag(){ return flags;};
    void   setflag(int flag) {flags=flag;};
    int             getfd(){return fd_;};
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
    int  flags;//事件标识
    int   mask_;    //事件标识
    Fun  readevent;   //可读
    Fun   writeEvent;  //可写
    Fun  closeEvent;  //关闭
    EventLoop* eventloop;
};

#endif /* Channel_hpp */
