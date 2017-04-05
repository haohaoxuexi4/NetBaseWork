//
//  Accepter.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/3/2.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "Accepter.hpp"
//#include "EventLoop.cpp"
#include <functional>
Accepter::Accepter(EventLoop* loop,const char* ip,int port):eventloop_(loop),socker_(ip,port),                                                           accepetChannel(loop,socker_.getsocketfd())
{
    accepetChannel.setreadEvent(std::bind(&Accepter::handleAccetpEvent, this));
    //accepetChannel.setwriteEvent(std::bind(&Accepter::handleAccetpEvent,this));
    //accepetChannel.addtoloop(); //自己加入到loop中
}

Accepter::~Accepter()
{

}


void Accepter::listen()
{
    socker_.binder();
    socker_.listener();
    accepetChannel.addtoloop(); //自己加入到loop中
   // size_t clientfd=socker_.accetper();
    
}
void Accepter::handleAccetpEvent()
{
    if(int clientfd=socker_.accetper()>0)
    {
        printf("fd=%d\n",clientfd);
    }

    
}
