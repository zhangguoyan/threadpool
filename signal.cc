#include "signal.h"
#include <iostream>
semaphores::semaphores(int value)
{
    signal = value;
}
void semaphores::set(int value)
{
    signal = value;
}
void semaphores::sem_wait()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    while(signal == 0)
    {
        m_sem.wait(lock);
    }
    signal--;
}
void semaphores::sem_post()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    signal++;
    m_sem.notify_one();
}
