/*
 * (c) 2015-2018 Rahmat M. Samik-Ibrahim
 * http://rahmatm.samik-ibrahim.vlsm.org/
 * This is free software.
 * REV05 Wed Apr 11 17:00:36 WIB 2018
 * REV02 Tue Apr 18 15:28:19 WIB 2017
 * REV01 Wed Nov  2 11:49:30 WIB 2016
 * START Xxx Sep 30 XX:XX:XX UTC 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "99-myutils.h"

#define  LOOP0     5
#define  LOOP1   500
#define  LOOP2  1000
#define  LOOP3 20000

volatile int loop = LOOP0;
int          share;

void* thread1 (void* a) {
   int ii, jj, kk;
   printf("I am a thread no 1\n");
   sleep(1);
   share = 1000;
   while (loop > 0) {
      for (ii=0;ii<LOOP1;ii++) {
         for (jj=0;jj<LOOP2;jj++) {
              ;
         }
      }
      share++;
   }
}

void* thread2 (void* a) {
   int ii, jj, kk;
   printf("I am a thread no 2\n");
   sleep(1);
   share = 2000;
   while (loop > 0) {
      for (ii=0;ii<LOOP1;ii++) {
         for (jj=0;jj<LOOP2;jj++) {
              ;
         }
      }
      share--;
   }
}

void* thread3 (void* a) {
   int ii, jj, kk;
   printf("I am a thread no 3\n");
   sleep(1);
   while (loop-- > 0) {
      for (ii=0;ii<LOOP3;ii++) {
         for (jj=0;jj<LOOP3;jj++) {
              ;
         }
      }
      printf("SHARE = %4.4d\n", share);
   }
}

void main(void) {
   daftar_trit   (thread1);
   daftar_trit   (thread2);
   daftar_trit   (thread3);
   jalankan_trit ();
   printf        ("I am MAIN\n");
   beberes_trit  ("Done...");
}

