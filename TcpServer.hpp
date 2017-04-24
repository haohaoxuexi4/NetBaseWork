//
//  TcpServer.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/5.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef TcpServer_hpp
#define TcpServer_hpp

#include <stdio.h>
#include "noncopy.h"
#include <map>
#include <string>
#include "Accepter.hpp"
#include "EventLoop.hpp"
#include "TcpConnection.hpp"

typedef std::function<void(TcpConnection*,Buffer&)> MessageCallback;
class TcpServer:noncopy
{
public:
    TcpServer(EventLoop* loop,const char* ip,const int port);
    ~TcpServer();
    void start();
    void newTcpConnection(const int fd);
    void remove_connection_from_connectionMap(TcpConnection* conn);
    void setMessageCallback(MessageCallback& back){messagecallback=back;};
    
    //void destoryConnection(TcpConnection* conn);//彻底的毁灭掉连接
    //void ShutdownbyOwn(TcpConnection* conn);  //拥有者主动关闭连接
private:
    
    EventLoop* loop_;
    std::map<std::string, TcpConnection*> connectionMap;
    std::unique_ptr<Accepter> unique_accepter;
    MessageCallback  messagecallback;  //消息处理函数
    
};

#endif /* TcpServer_hpp */
