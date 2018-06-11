#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "threadlib.h"

struct lock_t lock;

void thread_create(void *(*start_routine)(void*), void *arg){
  // allocate a free space in Heap for thread stack
  void *stack = malloc(PGSIZE*2);
  if((uint)stack % PGSIZE)
      stack = stack + (PGSIZE - (uint)stack % PGSIZE);
  int id;
  id = clone(stack, PGSIZE*2);

  if(id == 0){
    (*start_routine)(arg);
    free(stack);
    exit();
  }
}

// set lcok = 0
void lock_init(struct lock_t *lk){
    lk->locked = 0;
}

// if lock == 0, passby while loop
// if lock == 1, trap in this loop until it become 0 and exchangable
void lock_acquire(struct lock_t *lk){
  while(xchg(&lk->locked, 1) != 0)
      ;
}

// release by set lock = 0
void lock_release(struct lock_t *lk){
  xchg(&lk->locked, 0);
}
