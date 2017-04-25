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
void TcpServer::remove_connection_from_connectionMap(TcpConnection *conn)
{
    assert(conn!=nullptr);
    char* name=conn->getname();
    connectionMap.erase(name);
    if ((conn->getOutBudder())->readableSize()==0) { //TcpConnection 中待发送的数据(Buffer outbufrer)全部发完
        conn->DestoryConnection();                //彻底毁灭
    }
    else
    {
        conn->setStat(disConnecting); //断连接中 等待缓冲区数据发送完
        
    }
}

void TcpServer::newTcpConnection(const int fd)
{
    char buf[64];
    sprintf(buf,"newconnectionfd=%d",fd);
    std::shared_ptr<TcpConnection> newcon((new TcpConnection(loop_,fd,buf,sizeof(buf))));
    newcon->setMessageCallback(messagecallback);
    newcon->setRemoveConnection(std::bind(&TcpServer::remove_connection_from_connectionMap,this,std::placeholders::_1));
    loop_->addFunInloop(std::bind(&TcpConnection::ConnectionRead,newcon));
    connectionMap[buf]=newcon;

    
}


