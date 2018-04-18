/*
 * Copyright (C) 2015-2018 CC BY-SA 3.0 adapted from https://stackoverflow.com/
 *            questions/32205396/share-posix-semaphore-among-multiple-processes
 * Copyright (C) 2018 Rahmat M. Samik-Ibrahim (slightly modified)
 * You are free to SHARE (copy and redistribute the material in any medium or 
 * format) and to ADAPT (remix, transform, and build upon the material for any 
 * purpose, even commercially).  This program is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * REV01 Wed Apr 18 20:26:40 WIB 2018
 * REV00 Wed Apr 18 19:50:01 WIB 2018
 * START Xxx Xxx XX XX:XX:XX WIB 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SEM_NAME "/semaphore20"
#define ITERS 3

int main(void) {
    sem_t *semaphore = sem_open(SEM_NAME, O_RDWR);
    if (semaphore == SEM_FAILED) {
        perror("sem_open(3) failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ITERS; i++) {
        if (sem_wait(semaphore) < 0) {
            perror("sem_wait(3) failed on child");
            continue;
        }
        printf("PID %ld acquired semaphore\n", (long) getpid());

        if (sem_post(semaphore) < 0) {
            perror("sem_post(3) error on child");
        }
        sleep(1);
    }
    if (sem_close(semaphore) < 0)
        perror("sem_close(3) failed");
    return 0;
}

