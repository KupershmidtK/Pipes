#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parent.h"

extern int PROCESS_ID;
extern int*** pipe_array;

void errExit(const char* message) {
    printf("%s\n", message);
    exit(1);
}

int main(int argv, char* argc[]) {
    create_pipe_array();
    fill_pipe_array();

    create_processes();

    return 0;
}


// #define BUF_SIZE 10

// int main(int argc, char* argv[]) {
//     int pfd[2];
//     char buf[BUF_SIZE];
//     size_t numRead;

//     char* send_string = "Test string";

    
//     if (pipe(pfd) == -1)
//         errExit("pipe");
    
//     /* Создаем канал */
//     switch (fork()) {
//         case -1:
//             errExit("fork");
    
//         case 0:
//             /* Потомок читает из канала */
//             if (close(pfd[1]) == -1) /* Записывающий конец не используется */
//                 errExit("close — child");

//             for (;;) { /* Считываем данные из канала и направляем их в стандартный вывод */
//                 numRead = read(pfd[0], buf, BUF_SIZE);
//                 if (numRead == -1)
//                     errExit("read");
            
//                 if (numRead == 0)
//                     break;
            
//                 /* Конец файла */
//                 if (write(STDOUT_FILENO, buf, numRead) != numRead)
//                     printf("child — partial/failed write");
//             }

//             write(STDOUT_FILENO, "\n", 1);
            
//             if (close(pfd[0]) == -1)
//                 errExit("close");

//             _exit(EXIT_SUCCESS);
   
//         default:
//             /* Родитель записывает в канал */
//             if (close(pfd[0]) == -1) /* Считывающий конец не используется */
//              errExit("close — parent");
    
//             if (write(pfd[1], send_string, strlen(send_string)) != strlen(send_string))
//                 printf("parent — partial/failed write");
        
//             if (close(pfd[1]) == -1)
//                 /* Потомок увидит символ завершения файла */
//                 errExit("close");
        
//             wait(NULL);
//             /* Ждем завершения потомка */
//             exit(EXIT_SUCCESS);
//     }
// }