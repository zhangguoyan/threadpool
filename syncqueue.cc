#include <iostream>
#include <mutex>
#include <thread>
#include <list>
#include "signal/signal.h"
template<typename T>
class SyncQueue
{
public:
    SyncQueue(int maxsize):m_maxsize(maxsize)
    {}
    void put(const T& item)
    {
        if(hasSpaceToPut())
        {
            m_queue.push_back(item);
        }
        else
        {
            m_sem.sem_wait();
            std::cout<<"the buffer is full now, waiting..."<<"\n";
        }
    }
    void take(T & item)
    {
        if(thereIsAnItemToTake())
        {
            item = m_queue.front();
            m_queue.pop_front();
            m_sem.sem_post();
        }
        else
        {
            std::cout<<"there is no item in the buff, waiting..."<<"\n";
        }
    }
    int size()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

private:
    bool hasSpaceToPut()
    {
        if(size() == m_maxsize)
        {
            return false;
        }
        return true;
    }
    bool thereIsAnItemToTake()
    {
        if(m_queue.empty())
        {
            return false;
        }
        return true;
    }
private:
    std::mutex m_mutex;
    std::list<T> m_queue;
    semaphores m_sem;
    int m_maxsize;
};
