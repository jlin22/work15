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


int main(int argc, char * argv[]){
  if(argc==2){
    if (strcmp(argv[1],"-c")==0){
      int semid =semget(SEMKEY,1, IPC_CREAT | IPC_EXCL | 0644);
      int shmid =shmget(SHMKEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0600);
      if (semid < 0){
	printf("semaphore already exists\n");
      }
      if (shmid < 0){
	printf("shared memory already exists\n");
      }
      else{
	semctl(semid, 0, SETVAL, 1);	
	int fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
	close(fd);
	printf("shared memory, semaphore, and file successfully created\n");
      }
    }
    else if (strcmp(argv[1], "-v")==0){
      
      printf("story : \n");
      execlp("cat","cat","story.txt",NULL);
    }
    else if (strcmp(argv[1],"-r")==0){
      int semid = semget(SEMKEY,1,0600);
      int r = semctl(semid,0,IPC_RMID);
      if (r < 0){
	printf("semaphore doesn't exist\n");
      }
      else{
	printf("semaphore removed : %d\n", r);
      }
      int shmid = shmget(SHMKEY, sizeof(int), 0644);
      int s= shmctl(shmid, IPC_RMID,0);
      if (s < 0){
	printf("shared memory doesn't exist\n");
      }
      else{
      printf("shared memory removed : %d\n", s);
      }
      int f = fork();
      int status;
      if (f==0){
	int fd = open("story.txt", O_RDONLY);
        if (fd < 0){
	  printf("story doesn't exist \n");
	}
	else{
	  close(fd);
	  printf("story : \n");
	  execlp("cat","cat","story.txt",NULL);
	}
      }
      else{
	wait(&status);
	remove("story.txt");
      }
    }
    else{
      printf("invalid arguments\n");
    }
    
  }
  else{
    printf("invalid arguments\n");
  }
  return 0;
}
  
