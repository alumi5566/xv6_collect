
#include "types.h"
#include "stat.h"
#include "user.h"
#include "threadlib.h"
#define DEBUG 0

struct lock_t *lock;
// number of pass
static int pass =0;
// number of thread we wanna wreate
static int numofthread;
// how many pass we wanna see
static int MAXpass;
// every thread check turn, if match, pass to next thread
// initialize as thread 0
static int turn=0;
void* frisbee();

int main ( int argc , char * argv []){
    
    if(argc != 3){
        printf(1, "Usage: firsbee #ofThread #ofPass");
        exit();
    }
    
    numofthread =atoi(argv[1]);
    MAXpass = atoi(argv[2]);
    
    int i = 0;
    lock_init(lock);
    for(i=0;i<numofthread;i++){
        thread_create(frisbee,(void *)i);
    }
    //wait();
    for(i = 0; i < numofthread; i++){
        wait();
    }
    exit();

}

void* frisbee(void *arg){

    //lock_init(lock);
    int pidnum = (int)arg; // each thread has a unique pid
    //int flag = 0;
#if DEBUG
    printf(1,"child's pid = %d\n",pidnum);
#endif
    
    while(pass < MAXpass)//when pass time  bigger than it should be passed
    {
        lock_acquire(lock);
        
        if(pass==MAXpass){
            sleep(1);
            break;
        }
        if(numofthread == 0)
            break;
        if(pidnum == turn){
            pass++;
            printf(2,"(%d)pass number no:%d is thread %d is passing the token to ",numofthread,pass,pidnum);
            
            // pass to next thread
            turn = pidnum + 1;
            // pass to thread 0
            if(turn ==  numofthread){
                turn = 0 ;
            }

            printf(2,"%d\n",turn);
            sleep(1);
            lock_release(lock);
            sleep(1);
        }else{
            printf(2,"this is not a correct workpid\n");
            lock_release(lock);
            sleep(1);
        }
    }
    
    lock_release(lock);
    exit();

}
