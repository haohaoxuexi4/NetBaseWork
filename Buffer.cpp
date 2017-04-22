//
//  Buffer.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/10.
//  Copyright © 2017年 仙女. All rights reserved.
/*
------------------------------------
|               |                   |
readpostion     writepositon        size()
 */
//

#include "Buffer.hpp"

Buffer::Buffer():data(1024),readposition(0),writeposition(0)
{
}

Buffer::~Buffer()
{
    data.clear();
    readposition=0;
    writeposition=0;
}

ssize_t Buffer::readableSize()
{

    return writeposition-readposition;
}

ssize_t Buffer::writeableSize()
{

    return  data.size()-writeposition;
}
char*  Buffer::readbegin()
{
    return data.data()+readposition;
}
char* Buffer::writebegin()
{
    return data.data()+writeposition;
}
void Buffer::makespace(ssize_t len)
{
    //分两种情况考虑
    if(readposition+writeableSize()<len)
    {
       // 第一种 读取掉的数据空间（readposition）加上现在可写(writeablesize()) 小于要加入的数据len resize
        //先保存之前的数据  然后resize , 然后复制进去
        std::vector<char> datatmp(writeposition);
        //int writeposiontmp=writeposition;
        memcpy(datatmp.data(), data.data(),writeposition);
        data.resize(writeposition+len);
        memcpy(data.data(), datatmp.data(), writeposition);
    }
    else
    {
    //数据往前移动
        ssize_t readable=readableSize();
        std::copy(data.data()+readposition,data.data()+writeposition,data.data());
        readposition=0;
        writeposition=readable;
    }
}
void Buffer::append(const char* d,const int len) //数据插入到data中
{
    if (writeableSize()<len) {
        makespace(len);
    }
    std::copy(d,d+len,data.data()+writeposition);
    writeposition+=len;
    //return 0;
}

ssize_t Buffer::readDataFromFD(const int fd,int* backerror)
{
    char extbuf[65536]={0};
    const ssize_t writeable=writeableSize();
    struct iovec vec[2];
    vec[0].iov_base=&(*data.begin())+writeposition;
    vec[0].iov_len=writeable;
    vec[1].iov_base=extbuf;
    vec[1].iov_len=65536;
    const int cnt=(writeable<sizeof(extbuf))? 2:1;
    ssize_t n=readv(fd,vec,cnt);
    if (n<0) {
       // *backerror=errno_t;
    }
    else if (n<=writeable)
    {
        writeposition+=n;
    }
    else    //n> writeable
    {
        writeposition=data.size();
        append(extbuf, n-writeable);
    }
    return n;
}


