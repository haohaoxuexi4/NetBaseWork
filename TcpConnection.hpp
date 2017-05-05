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
typedef std::shared_ptr<TcpConnection> Share_tcpconnection;
typedef enum{connecting,Connected,disConnecting,disConnected} StateType; //准备连接，连接上了，去除连接中，去除了
typedef std::function<void(std::shared_ptr<TcpConnection>)> RemoveConnection;
typedef std::function<void (std::shared_ptr<TcpConnection>,Buffer*)>  MessageCallback;
class TcpConnection:noncopy,public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop* loop,int fd,char* name,int namelen);
    ~TcpConnection();
    void ChannelReadEvent();
    void ChannelWriteEvent();
    void ChannelCloseEvent();
    
    void send(char* d,int len);     //发送数据
    void send(void* d,int len);
    
    bool isConnected(){return Connected==stat_;};
    bool isDisconnected(){return disConnected==stat_;};
    void setStat(StateType type){stat_=type;};
    void  ConnectionRead();
    
    void   setname(char* name,int len){memcpy(name_, name,len);};
    char* getname(){return name_;};
    
    void setMessageCallback(MessageCallback& back){MessageCallback_=back;};
    void setRemoveConnection(RemoveConnection remconn){removeConnection_=remconn;};
    void Shutdownbyown();//主动关闭连接
    void DestoryConnection();//完全移除
    Buffer* getInputBuffer(){return &iputbuffer;};
    Buffer* getOutBudder(){return &outbuffer;}
    
    Channel* getchannel(){return chan;};
private:
    const int fd_;    //拥有的fd
    char name_[64];        //链接名字
    StateType  stat_;
    EventLoop* loop_;
    Channel* chan;
    //std::unique_ptr<Channel> chan;
    Buffer   iputbuffer; //从客户端读出来的数据
    Buffer    outbuffer; //往客户端写的数据
    MessageCallback     MessageCallback_;  //inputbuffer 读到的缓冲数据处理
    RemoveConnection    removeConnection_; 
};
#endif /* TcpConnection_hpp */
