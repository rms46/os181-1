// https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

char parent_message[] = "You say Hello";  // parent process will write this message
char child_message[]  = "And I say Goodbye"; // child process will then write this one

int main() {
  printf("%d\n", (int) sizeof(parent_message));
  printf("%d\n", (int) sizeof(child_message));
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_ANONYMOUS | MAP_SHARED;
  char* shmem = mmap(NULL, 128, protection, visibility, 0, 0);
  memcpy(shmem, parent_message, sizeof(parent_message));
  int pid = fork();
  if (pid == 0) {
    printf("Child read:  %s\n", shmem);
    memcpy(shmem, child_message, sizeof(child_message));
    printf("Child wrote: %s\n", shmem);
  } else {
    printf("Parent read: %s\n", shmem);
    sleep(1);
    printf("After 1s, parent read: %s\n", shmem);
  }
}

