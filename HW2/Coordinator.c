#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

    if (argc != 6){
        printf("Incorrect number of arguments\n");
        return -1;
    }

    int numP = 4;
    int numArg = 2;

    while(numP > 0){
        pid_t pid = fork();


        if (pid < 0){
            printf("Fork failed\n");
        }
        else if (pid == 0){
            execlp("Checker", "Checker", argv[1], argv[numArg], NULL);
        }
        else{
            printf("Coordinator: forked process with ID %d\n", pid);
            printf("Coordinator: waiting for process [%d]\n", pid);
            int status;
            wait(&status);
            int result = WEXITSTATUS(status);
            printf("Coordinator: child process %d returned %d\n", pid, result);
            numP--;
            numArg++;
        }
    }

    printf("Coordinator: exiting\n");
    return 0;
}