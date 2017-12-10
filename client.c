#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define SEMKEY 4761
#define SHMKEY 7921

int main(){
  int semid = semget(SEMKEY, 1,0644);
  struct sembuf buf;
  buf.sem_num =0;
  buf.sem_op =-1;
  buf.sem_flg=SEM_UNDO;
  printf("semid before access : %d \n", semid);
  semop(semid,&buf, 1);
  printf("semid after access : %d \n", semid);
  int fd = open("story.txt", O_RDWR | O_APPEND, 0644);
  if (fd <0){
    buf.sem_op = 1;
    printf("file doesn't exist\n");
    semop(sem_id, &direct, 1);
    return 1;
  }
    
  return 0;
}
