//
//  TcpServer.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/5.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "TcpServer.hpp"

TcpServer::TcpServer(EventLoop* loop,const char* ip,const int port):loop_(loop),
                                                            unique_accepter(new Accepter(loop,ip,port))
{
    unique_accepter->setInitTcpConnectionFun(std::bind(&TcpServer::newTcpConnection, this,std::placeholders::_1));
}

TcpServer::~TcpServer()
{
    loop_=nullptr;
}

void TcpServer::start()
{
    
    unique_accepter->listen();
    loop_->loop();
}

void TcpServer::newTcpConnection(const int fd)
{
    char buf[100];
    sprintf(buf,"newconnectionfd=%d",fd);
    TcpConnection* newcon(new TcpConnection(loop_,fd));
    newcon->setname(buf,sizeof(buf));
    
    connectionMap[buf]=newcon;
}

void TcpServer::remove_connection_from_connectionMap(TcpConnection *conn)
{
    assert(conn!=nullptr);
    char* name=conn->getname();
    connectionMap.erase(name);
    //conn->setStat(disConnecting); //断连接中
}

