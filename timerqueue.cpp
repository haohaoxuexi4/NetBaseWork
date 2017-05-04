#include "timerqueue.h"
//#include <sys/time.h>
Timerqueue::Timerqueue()
{

}
Timerqueue::~Timerqueue()
{
    Timervector.clear();
}

void Timerqueue::add(const Timer& timer)
{
    //assert(timer!=nullptr);
    Timervector.push_back(timer);
}

void Timerqueue::handelontime()
{
    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t seconds = tv.tv_sec;
    uint64_t now=seconds * 1000*1000 + tv.tv_usec;

    //printf("now=%ld\n",now);
    for(auto iter=Timervector.begin();iter!=Timervector.end();)
    {
        long long int  n=(now-(*iter).gettime());
    
        if ((*iter).isrunevery()) {
                                    //always
            if (n>=0) {
                (*iter).run();
                (*iter).settime(now+(*iter).getintervaltime());
            }
            iter++;
        }
                                    //nowt always
        else
        {
           
            if (n<0) {              //
                iter++;
            }
            else                    //on tiem
            {
                printf("now=%ld,itertime=%ld,n=%ld\n",now,(*iter).gettime(),n);
                (*iter).run();
                Timervector.erase(iter);
            }
        
        }
        
        
    }
     
}