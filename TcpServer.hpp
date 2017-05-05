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

typedef std::function<void(std::shared_ptr<TcpConnection>,Buffer*)> MessageCallback;
class TcpServer:noncopy
{
public:
    TcpServer(EventLoop* loop,const char* ip,const int port);
    ~TcpServer();
    void start();
    void newTcpConnection(const int fd);
    void remove_connection_from_connectionMap(std::shared_ptr<TcpConnection> conn);
    void setMessageCallback(MessageCallback back){messagecallback=back;};
    
private:
    
    EventLoop* loop_;
    std::map<std::string, std::shared_ptr<TcpConnection>> connectionMap;
    std::unique_ptr<Accepter> unique_accepter;
    MessageCallback  messagecallback;  //消息处理函数
    
};

#endif /* TcpServer_hpp */
