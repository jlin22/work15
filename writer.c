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
  printf("trying to access resources\n");
  int semid = semget(SEMKEY, 1,0644);
  int shmid = shmget(SHMKEY, sizeof(int), 0644);
  struct sembuf buf;
  buf.sem_num =0;
  buf.sem_op =-1;
  buf.sem_flg=SEM_UNDO;
  semop(semid,&buf,1);
  if (shmid < 0){
    printf("shared memory doesn't exist\n");
    return 1;
  }
  else if (semid< 0){
    printf("semaphore doesn't exist\n");
  }
  else{
    char * line = shmat(shmid,0,0);
    printf("last line : %s\n", line);
    printf("insert line : "); 
    char dest[256];
    fgets(dest,256 ,stdin);//change 100 later
    int fd = open("story.txt", O_WRONLY | O_APPEND, 0644);
    write(fd, dest, strlen(dest));
    close(fd);
    strcpy(line,dest);
    buf.sem_op=1;
    semop(semid, &buf, 1);
    printf("semaphore released\n");
  }
  return 0;
}
