#include "threadpool.h"
threadpool::threadpool(int poolsize, int maxqueuesize):m_poolSize(poolsize)
{
    m_syncqueue.setMaxSize(maxqueuesize);                
    init();
}

void threadpool::executeTask(Task&& task) 
{
    m_syncqueue.put(task);
}

void threadpool::stopPool()
{
    m_isrunning = false;
    destroy();
}

threadpool::~threadpool()
{
    stopPool();
}
   
void threadpool::runTask()
{
    while(m_isrunning)
    {
        Task task;
        m_syncqueue.take(task);
        task();
    }
}

void threadpool::init()
{
    m_isrunning = true;
    for(int i = 0 ;i < m_poolSize; i++)
    {
        m_threadqueue.push_back(std::make_shared<std::thread>(&threadpool::runTask,this));
    }
}

void threadpool::destroy()
{
    for(auto thread : m_threadqueue)
    {
        if(thread)
        {
            thread->join();
        }
    }
    m_threadqueue.clear();

}

