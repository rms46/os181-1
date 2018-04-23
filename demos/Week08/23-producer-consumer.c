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
 * START Xxx Xxx XX XX:XX:XX WIB 2015
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#define PROTECTION PROT_READ     | PROT_WRITE
#define VISIBILITY MAP_ANONYMOUS | MAP_SHARED

int main() {
  int* shmem = mmap(NULL, sizeof(int), PROTECTION, VISIBILITY, 0, 0);
  *shmem = 0;
  int pid = fork();
  if (pid == 0) {
    printf("Consumer reads:  %d\n", *shmem);
    *shmem = 1; 
    printf("Consumer writes: %d\n", *shmem);
  } else {
    printf("Producer reads:  %d\n", *shmem);
    sleep(1);
    printf("(After 1s)\nProduces reads:  %d\n", *shmem);
  }
}

