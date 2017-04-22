//
//  TcpConnection.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/5.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "TcpConnection.hpp"

TcpConnection::TcpConnection(EventLoop* loop,int fd):fd_(fd),loop_(loop),chan(loop,fd),stat_(connecting)
{
    chan.setreadEvent(std::bind(&TcpConnection::ChannelReadEvent,this));
    chan.setwriteEvent(std::bind(&TcpConnection::ChannelWriteEvent,this));
    chan.setcloseEvent(std::bind(&TcpConnection::ChannelCloseEvent,this));
    
    chan.enableReading();
    setStat(Connected);
}
TcpConnection::~TcpConnection()
{
    loop_=nullptr;
    close(fd_);
}
void TcpConnection::send(char* d,int len)
{
    assert(d!=nullptr);
    if(outbuffer.readableSize()>0)
    {
        //输出buffer里有数据，直接插入到outbuffer里
        outbuffer.append(d,len);
    }
    else if(outbuffer.readableSize()==0)
    {
        //
        ssize_t n=write(chan.getfd(), d, len);
        if (n<0) {
            //write 错误，数据插入到outbuffer ,并注册写事件
            outbuffer.append(d, len);
            chan.enableWriting();
        }
        else if (n>0&&n<len)
        {
            //多余部分，插入到outbuffer 并注册写事件
            outbuffer.append(d+n, len-(int)n);
            chan.enableReadingWriting();
        }
        //n=len  一次写完，ok
    }
    
}

/*
void Buffer::send(string sd,int len)
{

}
 */

void TcpConnection::ChannelCloseEvent()
{
    //首先把自己从TcpServer  connectionmap 中移除
    
}
void TcpConnection::ChannelReadEvent()
{
    //从fd中read 数据，
    //reader(chan.getfd());
    int backerror;
    ssize_t n=iputbuffer.readDataFromFD(chan.getfd(), &backerror);
    if (n>0)
    {
        // message callback
        
    }else if (n==0)
    {
        //socket read 返回0 客户端断了连接
        ChannelCloseEvent();
    }
    else
    {
        //error
        printf("ChannelReadEvent  read error\n");
    }
}

void TcpConnection::ChannelWriteEvent()
{
    //kqueue 触发的写事件的处理函数  主要处理outbuffer

    ssize_t n=write(chan.getfd(), outbuffer.readbegin(), outbuffer.readableSize());
    if (n>0)
    {
        outbuffer.changereadposition(n);
        if (outbuffer.readableSize()==0)
        {
            outbuffer.changereadposition(n);
            //取消 关注write 事件
            chan.disableWriting();
        }
        else
        {
            //改变readpostion位置
            outbuffer.changereadposition(n);
            //没有一次写完，持续关注write 事件
        }
    }
    else
    {
        //  write 错误
        printf("ChannelWriteEvent  write error\n");
    }
    
    printf("tcpconnection write event\n");
    return ;
    
}