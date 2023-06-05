#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <iostream>
#include "Queue.h"
using namespace std;
// In this version, server is blocked after activating the pflow 

// use integer to simulate Token
#define Token int

// argument and mutex initialization
struct Thread_arg {
    Queue<Token>* buffer;
    int max_token;
    double flow_interval;
    Thread_arg(Queue<Token>* b, int m, double f) {
        buffer = b;
        max_token = m;
        flow_interval = f;
    }
};

// shared resources
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
int flow_generate, fetched_token, dropped_token, pflow_generate;
int seq_num;

// semaphores
// The value of the empty is initialized as zero to block the pflow thread
// Server_permission is used to make sure server can only call pflow for one time
sem_t empty , server_permission;

// get random number
int getRand(int a, int b) {
    return rand() % (b - a + 1) + a;
}

// encapsulated library functions with error handling
void try_sem_init(sem_t* sem, int pshared, unsigned int value){
    int rc = sem_init(sem, pshared, value);
    if(rc){
        printf("Error when initialize the semaphore!\n");
        exit(-1);
    }
}

void try_sem_wait(sem_t* sem){
    int rc = sem_wait(sem);
    if(rc){
        printf("Error when waiting for the semaphore!\n");
        exit(-1);
    }
}

void try_sem_post(sem_t* sem){
    int rc = sem_post(sem);
    if(rc){
        printf("Error when posting the semaphore!\n");
        exit(-1);
    }
}

void try_sem_destroy(sem_t* sem){
    int rc = sem_destroy(sem);
    if(rc){
        printf("Error when destroying the semaphore!\n");
        exit(-1);
    }
}

void try_pthread_create(pthread_t* thread, const pthread_attr_t* attr,
                        void *(*start_routine)(void *), void* arg){
    int rc = pthread_create(thread, attr, start_routine, arg);
    if(rc){
        printf("Error when creating the thread, error number: %d\n", rc);
        exit(-1);
    }
}

void try_pthread_join(pthread_t thread, void **retval){
    int rc = pthread_join(thread, retval);
    if(rc){
        printf("Error when joining the thread, error number: %d\n", rc);
        exit(-1);
    }
}

void try_pthread_mutex_lock(pthread_mutex_t* mutex){
    int rc = pthread_mutex_lock(mutex);
    if(rc){
        printf("Error when locking the mutex, error number: %d\n", rc);
        exit(-1);
    }
}

void try_pthread_mutex_unlock(pthread_mutex_t* mutex){
    int rc = pthread_mutex_unlock(mutex);
    if(rc){
        printf("Error when unlocking the mutex, error number: %d\n", rc);
        exit(-1);
    }
}


// pflow thread
void *Pflow(void *threadarg){
    Thread_arg* my_data;
    my_data = (Thread_arg*)threadarg;
    const int max_token = my_data->max_token;
    Queue<Token>* buffer = my_data -> buffer;

    while(fetched_token + dropped_token < max_token){
        try_sem_wait(&empty);
        if(fetched_token + dropped_token >= max_token) break;   // quit when the max_token is reached
        
        try_pthread_mutex_lock(&my_mutex);
            /*critical section*/
            
            #ifdef AVOID
                // This piece of codes can prevent the situation that pflow generate the token after flow did it
                if(buffer -> size() !=0 ){
                    try_sem_post(&server_permission); 
                    try_pthread_mutex_unlock(&my_mutex);
                   continue;
                }
            #endif

            int added_token = getRand(1, 5);
            pflow_generate += added_token;
            for(int i = 0; i < added_token; i++,seq_num++) {
                if(dropped_token + fetched_token >= max_token)break;
                if(!buffer->push(seq_num)) {
                    dropped_token++;
                }
            }
            printf("%3d(pflow)   %3d                    %3d\n", added_token, seq_num - 1, buffer->size());
        try_pthread_mutex_unlock(&my_mutex);

        try_sem_post(&server_permission);       // pflow has already respond to the request, and allows the server to continue;
    }
    // avoid deadlock
    try_sem_post(&server_permission);
    pthread_exit(NULL);
}


// flow thread
void *Flow(void *threadarg) {
    Thread_arg* my_data;
    my_data = (Thread_arg*)threadarg;
    const int max_token = my_data->max_token;
    const double flow_interval = my_data->flow_interval;
    Queue<Token>* buffer = my_data -> buffer;

    while(fetched_token + dropped_token < max_token) {
        usleep((unsigned int)(flow_interval * 1e6));

        try_pthread_mutex_lock(&my_mutex);
            /*critical section*/
            int added_token = getRand(1, 10);
            flow_generate += added_token;
            // use a for loop to simulate
            for(int i = 0; i < added_token; i++,seq_num++) {
                if(dropped_token + fetched_token >= max_token)break;
                if(!buffer->push(seq_num)) {
                    dropped_token++;
                }
            }
            printf("%3d(flow)    %3d                    %3d\n", added_token, seq_num - 1, buffer->size());
        try_pthread_mutex_unlock(&my_mutex);
    }
    pthread_exit(NULL);
}

// server thread
void *Server(void *threadarg) {
    Thread_arg* my_data;
    my_data = (Thread_arg*)threadarg;
    int max_token = my_data->max_token;
    Queue<Token>* buffer = my_data -> buffer;

    while(fetched_token + dropped_token < max_token) {
        usleep(2000000);

        try_pthread_mutex_lock(&my_mutex);
            /*critical section*/
            int deleted_token = getRand(1, 20);

            int cnt;
            for(cnt = 0; cnt < deleted_token; cnt++) {
                if(dropped_token + fetched_token >= max_token)break;
                if(!buffer->pop())break;
                fetched_token++;
            }
            printf("                                    %3d             %3d          %3d\n"
                   , buffer->size(), cnt, fetched_token);

            // when the queue is emptied by the server, the server will call p_flow 
            if(buffer -> size() == 0 && seq_num > 0){
                try_sem_post(&empty);
                try_pthread_mutex_unlock(&my_mutex);    // unlock the mutex to make sure the flow or pflow can execute as normal
                try_sem_wait(&server_permission);       // block the server until the pflow is finished
                continue;                           // make sure that the mutex will not be unlocked twice
            }

        try_pthread_mutex_unlock(&my_mutex);

    }
    // avoid deadlock
    try_sem_post(&empty);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Usage: $ ./Filename max_token flow_interval(only accept 2 variables)\n");
    } else {

        // initialization and create the argument needed by the threads
        fetched_token = dropped_token = flow_generate = pflow_generate = seq_num = 0;
        int max_token = atoi(argv[1]);
        double flow_interval = atof(argv[2]);
        // check the input value
        if(!max_token||flow_interval == 0){
            printf("Input error!\n");
            exit(-1);
        }
        try_sem_init(&empty,0,0);
        try_sem_init(&server_permission,0,0);

        Thread_arg arg(new Queue<Token>(), max_token, flow_interval);
        printf("Flow         Queue                                  Server\n");
        printf("Token added  Latest sequence number Current Length  Token served Total Token fetched\n");
        srand((unsigned)time(NULL));    // feed a seed

        // create 2 threads to do the simulation
        pthread_t flow_thread, server_thread, pflow_thread;
        // start client thread at first
        try_pthread_create(&flow_thread, NULL, Flow, (void*)&arg);
        try_pthread_create(&server_thread, NULL, Server, (void*)&arg);
        try_pthread_create(&pflow_thread, NULL, Pflow, (void*)&arg);

        // wait for 2 thread to finish
        try_pthread_join(flow_thread, NULL);
        try_pthread_join(server_thread, NULL);
        try_pthread_join(pflow_thread, NULL);

        printf("The total number of tokens that have been fetched by the server is %d.\n", fetched_token);
        printf("The total number of tokens that have been generated by the flow is %d.\n", flow_generate);
        printf("The total number of tokens that have been generated by the pflow is %d.\n", pflow_generate);
        printf("The total number of tokens that have been dropped by the queue is %d.\n", dropped_token);
        
        try_sem_destroy(&empty);
        try_sem_destroy(&server_permission);
    }
    return 0;
}
