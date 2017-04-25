//
//  Buffer.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/10.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <stdio.h>
#include <vector>
//#include "socketer.hpp"
#include <sys/uio.h>  
class Buffer
{
public:
    Buffer();
    ~Buffer();
    ssize_t readableSize();
    ssize_t writeableSize();
   // ssize_t getreadpostion(){return readposition;}
    //ssize_t getwriteposition(){return writeposition;}
    void changereadposition(ssize_t n){readposition+=n;}
    void changewriteposition(ssize_t n)
    {
        if (n+writeposition>=data.size()) {
            n=data.size();
        }
        else
        {
            writeposition+=n;
        }
        
    }
    
    char* readbegin();
    char* writebegin();
    ssize_t readDataFromFD(const int fd,int* backerror); //从fd中读取数据，
    void append(const char* d,const int len); //数据插入到data中
    //char*
    
private:
    void makespace(ssize_t len);  //空间不足，增加空间
    std::vector<char> data;
    ssize_t readposition;
    ssize_t writeposition;
};
ssize_t readDataFromFD(Buffer* buf,const int fd,int* backerror); //从fd中读取数据，
#endif /* Buffer_hpp */
