#ifndef _SEMAPHORES_HH
#define _SEMAPHORES_HH
#include <mutex>
#include <condition_variable>
class semaphores
{
public:
    explicit semaphores(int value = 0);
    void set(int value);
    void sem_wait();
    void sem_post();

private:
    std::mutex m_mutex;
    std::condition_variable m_sem;
    int signal;
};
#endif
