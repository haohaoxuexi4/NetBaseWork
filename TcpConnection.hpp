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

class TcpConnection;
typedef enum{connecting,Connected,disConnecting,disConnected} StateType; //准备连接，连接上了，去除连接中，去除了
typedef std::function<void(TcpConnection*)> RemoveConnection;
typedef std::function<void (TcpConnection*,Buffer&)>  MessageCallback;
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
    
    void setMessageCallback(MessageCallback& back){MessageCallback_=back;};
    void setRemoveConnection(RemoveConnection remconn){removeConnection_=remconn;};
    void Shutdownbyown();//主动关闭连接
    void DestoryConnection();//完全移除
    Buffer& getInputBuffer(){return iputbuffer;};
    Buffer& getOutBudder(){return outbuffer;}
private:
    const int fd_;    //拥有的fd
    char* name_;        //链接名字
    StateType  stat_;
    EventLoop* loop_;
    Channel    chan;
    Buffer    iputbuffer; //从客户端读出来的数据
    Buffer    outbuffer; //往客户端写的数据
    MessageCallback     MessageCallback_;  //inputbuffer 读到的缓冲数据处理
    RemoveConnection    removeConnection_; 
};
#endif /* TcpConnection_hpp */
