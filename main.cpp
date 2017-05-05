//
//  main.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/22.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include <iostream>
#include "EventLoop.hpp"
#include "Accepter.hpp"
#include "fastjson.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "TcpServer.hpp"

int main(int argc, const char * argv[]) {
    
    FastJson json3("{\"serverip\":\"192.168.0.6\",\"serverport\":8080}");
    printf("parseconde=%d\n",json3.fastjson_parse());

    jsonValue* ip=json3.fastjson_getobjectone(0);
    jsonValue* port=json3.fastjson_getobjectone(1);
    char* ip1=ip->u.s.addr;
    int port1=port->u.number;
    //printf("ip1=%s,port=%d","192.168.0.6",port1);
    
    
    EventLoop goloop;
    
    //Accepter accept(&goloop,"192.168.0.6",port1);
    //accept.listen();
    //goloop.loop();

    TcpServer server(&goloop,"192.168.0.6",port1);
    server.start();
    json3.valuefree();
    

    return 0;
}
