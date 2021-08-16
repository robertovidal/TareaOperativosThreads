#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>

#define MIN_PID 300
#define MAX_PID 5000

// Jose Pablo Fernández Cubillo
// Roberto Vidal Patiño

int *bitmap;
int used = 0;
int tot = MAX_PID - MIN_PID + 1;

void *createThread(void *param);
int allocate_map();
int allocate_pid();
void release_pid(int pid);

void *createThread(void *param){
  int r = rand() % 20 + 1;
  int pid = allocate_pid();
  if(pid == -1){
    printf("Could not allocate pid");
  } else {
    printf("Thread going to sleep for %d, with pid: %d\n", r, pid);
    sleep(r);
    release_pid(pid);
    printf("pid %d released\n", pid);
  }
  pthread_exit(0);
}

int allocate_map(){
  bitmap = malloc((tot) * sizeof(int));
  if(bitmap){
    return 1;
  }
  return -1;
}

int allocate_pid(){
  if(used == tot){
    return -1;
  }
  int pid;
  if(bitmap[used] == 0){
    bitmap[used] = 1;
    pid = MIN_PID + used;
  } else {
    for(int i = 0; i < tot; i++){
      if(bitmap[i] == 0){
        bitmap[i] = 1;
        pid = MIN_PID + i;
        break;
      }
    }
  }
  used++;
  return pid;
}

void release_pid(int pid){
  if(pid < MIN_PID || pid > MAX_PID){
    printf("Invalid pid");
    return;
  }
  used--;
  bitmap[pid-300] = 0;
}

int main(){
  time_t t;
  srand((unsigned) time(&t));
  if(allocate_map() == 1){
    for(int i = 0; i < 100; i++){
      pthread_t thread_id;
      pthread_create(&thread_id, NULL, createThread, NULL);
      pthread_join(thread_id, NULL);
    }
    free(bitmap);
  } else {
    printf("Could not allocate map");
  }
  return 0;
}