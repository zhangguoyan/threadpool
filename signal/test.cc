#include <iostream>
#include <thread>
#include <stdio.h>
#include <string.h>
#include "signal.h"
class test
{
public:
    void setItems(int items)
    {
        nitems = items;
        memset(buff,0,nitems);
    }

    void producer()
    {
        int i;
        for(i = 0; i < nitems; i++)
        {
         //  sem.sem_wait();
           buff[i % NUMBER] = i;
           sem.sem_post();
        }  
   } 

   void consumer()
   {
       int i ;
       for(i = 0; i < nitems; i++)
       {
           sem.sem_wait();
           if(buff[i % NUMBER] != i)
           {
               std::cout<<"buff["<<i<<"]="<<buff[i % NUMBER]<<"\n";
           }
       //    sem.sem_post();
       }
   }

   void run()
   {
       sem.set(0);
       std::thread produce(&test::producer,this);
       std::thread consume(&test::consumer,this);
       produce.join();
       consume.join();
   }
private:
    semaphores sem;
    static const int NUMBER = 10;
    int buff[NUMBER];
    int nitems;
};

int main(int argc, char* argv[])
{
    std::cout<<"starting......"<<"\n";
    test t;
    t.setItems(10);
    t.run();
    return 0;
}
