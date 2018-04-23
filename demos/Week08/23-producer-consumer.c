/*
 Copyright (C) 2013-2018 CC BY-SA 3.0
 adapted from https://stackoverflow.com/
 questions/5656530/
 how-to-use-shared-memory-with-linux-in-c

 Copyright 2018 Rahmat M. Samik-Ibrahim
 You are free to SHARE (copy and 
 redistribute the material in any medium
 or format) and to ADAPT (remix, 
 transform, and build upon the material 
 for any purpose, even commercially).
 This program is distributed in the hope 
 that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied 
 warranty of MERCHANTABILITY or FITNESS 
 FOR A PARTICULAR PURPOSE.

 * REV02 Mon Apr 23 11:54:46 WIB 2018
 * REV00 Wed Apr 18 19:50:01 WIB 2018
 * START Xxx Xxx XX XX:XX:XX WIB 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

//       1         2         3         4
// 4567890123456789012345678901234567890

#define PROTECTION \
                (PROT_READ | PROT_WRITE)
#define VISIBILITY \
            (MAP_ANONYMOUS | MAP_SHARED)
#define SEM_PERMS  \
 (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

#define PRODUCER 0
#define CONSUMER 1

typedef struct {
   int product;
   int turn;
}  buffer;

buffer* preparation(buffer* share_buf) {
   char* user = getenv("USER");
   printf("This is %s\n", user);
   share_buf = (buffer* ) mmap(NULL, sizeof(buffer), 
           PROTECTION, VISIBILITY, 0, 0);
   share_buf->product = 0;
   share_buf->turn    = PRODUCER;
   return share_buf;
}

void producer (buffer* share_buf) {
   int mypid = getpid();
   printf("Producer[%d] reads:  %d\n", 
            mypid, share_buf->product);
   sleep(1);
   printf("(After 1s)\n");
   printf("Produces[%d] reads:  %d\n", 
            mypid, share_buf->product);
}

void consumer (buffer* share_buf) {
   int mypid = getpid();
   printf("Consumer[%d] reads:  %d\n", 
            mypid, share_buf->product);
   share_buf->product = 1;
   printf("Consumer[%d] writes: %d\n",
            mypid, share_buf->product);
}

void main(void) {
   printf("START\n");
   buffer* share_buf;
   share_buf = preparation(share_buf);
   int pid = fork();
   if (pid == 0) consumer(share_buf);
   else          producer(share_buf);
   wait(NULL);
   printf("STOP\n");
}

