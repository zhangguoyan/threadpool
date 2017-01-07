#include <mutex>
#include <condition_variable>
class semaphores
{
public:
    void set(int value);
    void sem_wait();
    void sem_post();

private:
    std::mutex m_mutex;
    std::condition_variable m_sem;
    int signal;
};
