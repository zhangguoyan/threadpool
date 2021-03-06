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
//debug-mutex
    std::mutex m_mutex;
    std::mutex m_queue_mutex;
    std::list<T> m_queue;
    semaphores m_sem_full;
    semaphores m_sem_empty;
    int m_maxsize;
};

template<typename T>
SyncQueue<T>::SyncQueue()
{}
template<typename T>
void SyncQueue<T>::setMaxSize(int maxsize)
{
    m_maxsize = maxsize;
    m_sem_full.set(m_maxsize);
}

template<typename T>
void SyncQueue<T>::put(const T& item)
{
    //debug
    //hasSpaceToPut();
    m_sem_full.sem_wait();
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push_back(item);
    }
    m_sem_empty.sem_post();
}

template<typename T>
void SyncQueue<T>::take(T & item)
{
    //debug
    //thereIsAnItemToTake();
    m_sem_empty.sem_wait();
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        item = m_queue.front();
        m_queue.pop_front();
    }
    m_sem_full.sem_post();
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
        std::cout<<"the buffer is full now, waiting... ... async thread is "<<std::this_thread::get_id() << " value "<< m_sem_full.get_sigval()<<"\n";
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
        std::cout<<"there is no item in the buff, waiting... async thread is "<<std::this_thread::get_id() <<" value "<< m_sem_empty.get_sigval() <<"\n";
        return false;
    }
    return true;
}

#endif
