#include <stdio.h>
#include <functional>
#include <sys/time.h>
using namespace::std;


class Timerstamp
{
public:
    Timerstamp(int64_t us){uicrosecond_=us;}
    ~Timerstamp(){};
    int64_t getmicro(){return uicrosecond_;};
    
    
private:
    int64_t uicrosecond_; //微妙
};

static uint64_t Now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    return seconds * 1000*1000 + tv.tv_usec;
}

////////////////
//typedef enum{runAftertime,runEverytime} Timertype;  //定时器类型  ，运行一次，马上运行，每次都运行
typedef std::function<void()> Timercallback;
class Timer
{
public:
    Timer(Timercallback callback,uint64_t micros,bool isevery=false):callback_(callback),isRunevery(isevery),interval_time(micros*1000),time_(Now()+micros*1000)
    {
        printf("timer init time_=%lluu\n",time_);
    }
    ~Timer(){};
    
    void run(){callback_();};
    bool isrunevery(){return isRunevery;};
    uint64_t gettime(){return time_;};
    void  settime(uint64_t time){time_=time;};
    
    uint64_t getintervaltime(){return interval_time;};
    /*
    uint64_t Now(){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        int64_t seconds = tv.tv_sec;
        return seconds * 1000*1000 + tv.tv_usec;};
     */
private:
    bool  isRunevery;
    uint64_t time_;
    uint64_t interval_time;//间隔时间
    Timercallback callback_;//回调函数 callback
};
