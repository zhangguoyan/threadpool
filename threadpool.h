#ifndef _THREAD_POOL_HH
#define _THREAD_POOL_HH
#include "syncqueue.h"
#include <list>
#include <functional>
#include <thread>
using Task = std::function<void()>;
template class SyncQueue<Task>;
class threadpool
{
public:
    threadpool(int poolsize, int maxqueuesize);
    void executeTask(Task&& task);
    void stopPool();
    ~threadpool();
    
private:
    void runTask();
    void init();
    void destroy();
    int m_poolSize;
    std::list<std::shared_ptr<std::thread>> m_threadqueue;
    SyncQueue<Task> m_syncqueue;
    bool m_isrunning;
};
#endif
