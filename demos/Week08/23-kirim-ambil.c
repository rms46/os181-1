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

#define PROTECTION \
                (PROT_READ | PROT_WRITE)
#define VISIBILITY \
            (MAP_ANONYMOUS | MAP_SHARED)
#define SEM_PERMS  \
 (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

#define KIRIM 0
#define AMBIL 1
#define LOOP  2

typedef struct {
   int produk;
   int turn;
}  buffer;

buffer* persiapan(buffer* shrbuf) {
   shrbuf = (buffer* ) mmap(NULL, 
            sizeof(buffer), PROTECTION, 
            VISIBILITY, 0, 0);
   shrbuf->produk = 0;
   shrbuf->turn    = KIRIM;
   return shrbuf;
}

void kirim (buffer* shrbuf) {
   printf("KIRIM PID[%d]\n", getpid());
   for (int ii=0; ii<LOOP; ii++) {
      while(shrbuf->turn != KIRIM)
         ;
      printf("KIRIM %d\n", 
                   ++(shrbuf->produk));
      shrbuf->turn = AMBIL;
      fflush(NULL);
   }
}

void ambil (buffer* shrbuf) {
   sleep(1);
   printf("AMBIL PID[%d]\n", getpid());
   for (int ii=0; ii<LOOP; ii++) {
      while(shrbuf->turn != AMBIL)
         ;
      printf("AMBIL %d\n", 
               shrbuf->produk);
      shrbuf->turn = KIRIM;
   }
}

void main(void) {
   printf("START PID[%d]\n", getpid());
   buffer* share_buf=persiapan(share_buf);
   if (fork()) kirim (share_buf);
   else        ambil (share_buf);
   wait(NULL);
   printf("STOP PID[%d]\n", getpid());
}

//       1         2         3         4
// 4567890123456789012345678901234567890

