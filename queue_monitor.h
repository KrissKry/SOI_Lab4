#ifndef QUEUE_MONITOR_H
#define QUEUE_MONITOR_H

#include "monitor.h"
#include <deque>
#include <random>
#include <iostream>
#include <thread>
#define R_WAIT_TIME 10      //max sleep time for reader
#define P_WAIT_TIME 30      //max sleep time for producer
#define C_WAIT_TIME 30      //max sleep time for consumer
#define S           10      //max queue size
#define P 5                 //producer count    
#define C 2                 //consumer count
#define R 2                 //reader count


/* Class designed for generating random values for all objects using it */
class RandomGen {
    private:
        std::mt19937 m_mt;
    public:
        RandomGen();
        ~RandomGen() {};

        time_t getSleepTime(int max_wait_time);         //generates sleep time in seconds for every person
        int genQueueId();                               //generates and returns either '1' or '2'

};

/* struct stored in queues */
struct message
{
    int queue_id;
    int prod_id;
    int msg_id;
};


class Monitor_Q : Monitor
{
    private:
        Condition Q1_has_empty, Q1_has_elements;
        Condition Q2_has_empty, Q2_has_elements;
        std::deque<message> Q1;
        std::deque<message> Q2;
        RandomGen rg;
        int p_id = 0;
        int c_id = 0;
        int r_id = 0;
        //int m_id = 0;
        pthread_mutex_t ostream;
    public:
        Monitor_Q() {};
        ~Monitor_Q() {};

        /* Invoker is needed as cos tam */
        static void* producerInvoker(void* context);
        void* produce();
        
        static void* consumerInvoker(void* context);
        void* consume();
  
        static void* readerInvoker(void* context);
        void* read();

        static void* printInvoker(void* context);
        void* printQ();

};


#endif