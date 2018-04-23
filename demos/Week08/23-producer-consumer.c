/*
 * Copyright (C) 2013-2018 CC BY-SA 3.0 adapted from https://stackoverflow.com/
 *            questions/5656530/how-to-use-shared-memory-with-linux-in-c
 * Copyright (C) 2018 Rahmat M. Samik-Ibrahim (modified)
 * You are free to SHARE (copy and redistribute the material in any medium or 
 * format) and to ADAPT (remix, transform, and build upon the material for any 
 * purpose, even commercially).  This program is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * REV02 Mon Apr 23 11:54:46 WIB 2018
 * REV00 Wed Apr 18 19:50:01 WIB 2018
 * START Xxx Xxx XX XX:XX:XX WIB 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>

#define PROTECTION PROT_READ     | PROT_WRITE
#define VISIBILITY MAP_ANONYMOUS | MAP_SHARED

int main() {
  int  mypid = getpid();
  int* shmem = mmap(NULL, sizeof(int), PROTECTION, VISIBILITY, 0, 0);
  *shmem = 0;
  printf("HELLO, this is PID[%d]\n",mypid);
  int pid = fork();
  if (pid == 0) {
    mypid = getpid();
    printf("Consumer[%d] reads:  %d\n", mypid, *shmem);
    *shmem = 1; 
    printf("Consumer[%d] writes: %d\n", mypid, *shmem);
  } else {
    printf("Producer[%d] reads:  %d\n", mypid, *shmem);
    sleep(1);
    printf("(After 1s)\nProduces[%d] reads:  %d\n", mypid, *shmem);
  }
}

