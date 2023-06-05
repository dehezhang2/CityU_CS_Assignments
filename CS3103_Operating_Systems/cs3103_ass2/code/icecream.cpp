#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define NUM_SELLER  3

static long icecream = 3000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* seller(void *arg)
{
    int id = *(int *)arg;
    int done = 0;  /* 0 - not done; 1 - done */
    long mysell = 0;

    while (!done) {
        /* pthread_mutex_lock(&mutex); */
        if ( icecream > 0 ) {
            for (int i=0; i<100; i++) {}; // simulate selling duration
            icecream--;
            mysell++;
        }
        else
            done = 1;
        /*  pthread_mutex_unlock(&mutex); */
    }
    pthread_exit((void *) mysell);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_SELLER];
    int threadid[NUM_SELLER];
    int i, rc, jrc;
    long total_sold = 0;
    void *retval;

    for (i = 0; i < NUM_SELLER; i++) {
        threadid[i] = i;
        rc = pthread_create(&threads[i], NULL, seller, (void *)&threadid[i]);
        if (rc) {
            cout << "Error when creating thread!" << endl;
            exit(-1);
        }
        jrc = pthread_join(threads[i],&retval);
        if(jrc){
            cout << "Error when joining thread!\n";
            exit(-1);
        }
         cout << "Seller #" << threadid[i] << " sold " << (long) retval << " ice-creams" << endl;
         total_sold+=(long) retval;
    }

    /*  for (i = 0; i < NUM_SELLER; i++) { */
    // rc = pthread_join(threads[i], &retval);
    // if (rc) {
    //     cout << "Error when joining thread!" << endl;
    //     exit(-1);
    // }
    //     cout << "Seller #" << threadid[i] << " sold " << (long) retval << " ice-creams" << endl;
    // total_sold+=(long) retval;
    /* } */

    cout << "A total of " << total_sold << " ice-creams sold" << endl;
    pthread_exit(NULL);
}
