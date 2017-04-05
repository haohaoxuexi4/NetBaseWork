//
//  noncopy.h
//  Reactor_day1
//
//  Created by 仙女 on 17/2/23.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef noncopy_h
#define noncopy_h
class noncopy{
public:
    noncopy(){};
    ~noncopy(){};
    
private:
    noncopy(const noncopy&);
    const noncopy& operator=(const noncopy&);
    
};

#endif /* noncopy_h */
