#ifndef _SYNC_QUEUE_HH
#define _SYNC_QUEUE_HH
#include <iostream>
#include <mutex>
#include <thread>
#include <list>
#include "signal.h"
template<typename T>
class SyncQueue
{
public:
    SyncQueue();
    void setMaxSize(int maxsize);
    void put(const T& item);
    void take(T & item);

private:
    bool hasSpaceToPut();
    bool thereIsAnItemToTake();
    int size();
private:
    std::mutex m_mutex;
    std::list<T> m_queue;
    semaphores m_sem_notfull;
    semaphores m_sem_notempty;
    semaphores m_sem_mutex;
    int m_maxsize;
};

template<typename T>
SyncQueue<T>::SyncQueue()
{}
template<typename T>
void SyncQueue<T>::setMaxSize(int maxsize)
{
    m_maxsize = maxsize;
}

template<typename T>
void SyncQueue<T>::put(const T& item)
{
    if(hasSpaceToPut())
    {
        m_queue.push_back(item);
        m_sem_notempty.sem_post();
    }
    else
    {
        std::cout<<"the buffer is full now, waiting... ... async thread is "<<std::this_thread::get_id() <<"\n";
        m_sem_notfull.sem_wait();
        m_queue.push_back(item);
    }
}

template<typename T>
void SyncQueue<T>::take(T & item)
{
    m_sem_notempty.sem_wait();
    if(thereIsAnItemToTake())
    {
        item = m_queue.front();
        m_queue.pop_front();
        m_sem_notfull.sem_post();
    }
   // else
   // {
   //     std::cout<<"there is no item in the buff, waiting... async thread is "<<std::this_thread::get_id() <<"\n";
   //     m_sem_notempty.sem_wait();
   //     item = m_queue.front();
   //     std::cout<<"SyncQueue take m_queue.pop_front"<<"\n";
   //     m_queue.pop_front();
   // }
}

template<typename T>
int SyncQueue<T>::size()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.size();
}

template<typename T>
bool SyncQueue<T>::hasSpaceToPut()
{
    //dead lock when want use the m_mutex here ....... notice
    if(size() == m_maxsize)
    {
        return false;
    }
    return true;
}


template<typename T>
bool SyncQueue<T>::thereIsAnItemToTake()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if(m_queue.empty())
    {
        std::cout<<"there is no item in the buff, waiting... async thread is "<<std::this_thread::get_id() <<"\n";
        return false;
    }
    return true;
}

#endif
