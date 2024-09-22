#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "parent.h"

int create_child_process(int process_id);

const int PROCESS_CNT = 2;
int PROCESS_ID = 0;

int*** pipe_array = NULL;

int create_pipe_array() {
    pipe_array = (int***)malloc(sizeof(int) * PROCESS_CNT * PROCESS_CNT * 2);
    if(pipe_array == NULL)
        return -1;
    
    return 0;
}

int fill_pipe_array() {
    if(pipe_array == NULL) 
        return -1;

    for(int i = 0; i < PROCESS_CNT; i++) {
        for(int j = 0; j < PROCESS_CNT; j++) {
            if (i != j) {
                int rc = pipe(get_pipe(i, j));
                if (rc == -1)
                    return - 1;
            }
        }
    }
    return 0;
}

void delete_pipe_array() {
    if(pipe_array == NULL)
        return;

    free(pipe_array);
}

int create_processes() {
    for(int i = 1; i < PROCESS_CNT; i++) {
        if(create_child_process(i) == -1) {
            return -1;
        }
    }
    return 0;
}

int create_child_process(int process_id) {
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        printf("ERROR: create new process\n");
        return -1;
    
    case 0: // child process
        // handle childe
        PROCESS_ID = process_id;
        return 0;
    default: // parent process
        // handle parent
        return 0;
    }
}

int* get_pipe(int i, int j) {
    int offset = sizeof(int) * 2 * (i * PROCESS_CNT + j);
    return (int*)pipe_array + offset;
}

void close_unused_pipe() {

}

void close_unused_pipe_end() {

}