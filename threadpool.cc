#include "syncqueue.h"
#include <list>
#include <funtional>
#include <thread>
//add
class threadpool
{
public:
    using Task = std::function<void()>;
    threadpool(int poolsize, int maxqueuesize):m_poolsize(poolsize)
    {
        m_syncqueue(maxqueuesize);                
        init();
    }
    void executeTask(T &Task) 
    {
        m_syncqueue.put(Task);
    }

    void stopPool()
    {
        m_isrunning = false;
        destroy();
    }
//add
    ~threadpool()
    {
        stopPool();
    }
   
    
private:
    runTask()
    {
        while(m_isrunning)
        {
            m_syncqueue.take(Task);
            Task();
        }
    }
    void init()
    {
        m_isrunning = true;
        for(int i = 0 ;i < m_poolSize; i++)
        {
            m_threadqueue.push_back(std::thread(&threadpool::runTask,this);
        }
    }
    destroy()
    {
        for(int i = 0 ;i < m_poolSize; i++)
        {
            auto thread = m_threadqueue.pop_back();
            thread.join();
        }
     //add
        m_threadqueue.clear();

    }
    int m_poolSize;
    std::list<std::thread> m_threadqueue;
    syncqueue m_syncqueue;
    bool m_isrunning;
       
};
