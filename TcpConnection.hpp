//
//  TcpConnection.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/5.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef TcpConnection_hpp
#define TcpConnection_hpp

#include <stdio.h>
#include "noncopy.h"
#include "Channel.hpp"
#include "EventLoop.hpp"
#include "socketer.hpp"
#include "Buffer.hpp"
#include <assert.h>

typedef enum{connecting,Connected,disConnecting,disConnected} StateType; //准备连接，连接上了，去除连接中，去除了
class TcpConnection:noncopy
{
public:
    TcpConnection(EventLoop* loop,int fd);
    ~TcpConnection();
    void ChannelReadEvent();
    void ChannelWriteEvent();
    void ChannelCloseEvent();
    void send(char* d,int len);
    
    bool isConnected(){return Connected==stat_;};
    bool isDisconnected(){return disConnected==stat_;};
    void setStat(StateType type){stat_=type;};
    
    void   setname(char* name,int len){memcpy(name_, name,len);};
    char* getname(){return name_;};
private:
    const int fd_;    //拥有的fd
    char* name_;        //链接名字
    StateType  stat_;
    EventLoop* loop_;
    Channel    chan;
    Buffer    iputbuffer; //从客户端读出来的数据
    Buffer    outbuffer; //往客户端写的数据
};
#endif /* TcpConnection_hpp */
