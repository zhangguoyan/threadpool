#include "threadpool.h"
#include "syncqueue.h"
#include <thread>
#include <chrono>
void testpool();
int main(int argc, char *argv[])
{
    testpool();
    return 0;    
}

void testpool()
{
 
   threadpool pool(5,10);
   std::thread thd1([&pool]{
       for(int i =0;i < 100; i++)
       {
           auto thdId = std::this_thread::get_id();
           pool.executeTask([thdId]
              { 
                  std::cout<<"sync layer thread 1 ID: "<< thdId <<"\n";
              });
         
       }
     });

   std::thread thd2([&pool]{
       for (int i = 0; i < 100; i++)
       {
           auto thdId = std::this_thread::get_id();
           pool.executeTask([thdId]
              { 
                  std::cout<<"sync layer thread 2 ID: "<< thdId <<"\n";
              });
       }
     });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    pool.stopPool();
    thd1.join();
    thd2.join();
         
}
