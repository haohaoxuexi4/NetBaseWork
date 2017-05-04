//timerqueue

#include "timer.h"
#include <vector>
#include <assert.h>
#include <sys/time.h>
class Timerqueue
{
public:
    Timerqueue();
    ~Timerqueue();
    void add(const Timer& timer);
    //void cancel();
    
    void handelontime();
private:
    std::vector<Timer> Timervector;
};