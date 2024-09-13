#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv) {

    if (argc != 6){
        printf("Coordinator: Incorrect number of arguments\n");
        return -1;
    }

    int fd[4][2];
    pid_t pid[4];
    char* divisor = argv[1];
    int sharedMemoryId[4];

    for(int i = 0; i < 4; i++){
        pipe(fd[i]);
        pid[i] = fork();

        if (pid[i] == -1){
            printf("Fork failed\n");
        }
        else if (pid[i] == 0){
            close(fd[i][1]);
            char buffer[8];
            sprintf(buffer, "%d", fd[i][0]);
            execlp("Checker", "Checker", divisor, argv[i+2], buffer, NULL);
        }
        else{
            printf("Coordinator: forked process with ID %d\n", pid[i]);
            close(fd[i][0]);

            sharedMemoryId[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

            printf("Coordinator: wrote shm ID %d to pipe (%ld bytes)\n", sharedMemoryId[i], sizeof(int));
            write(fd[i][1], &sharedMemoryId[i], sizeof(int));
            close(fd[i][1]);
        }
    }

    for(int i = 0; i < 4; i++){
        printf("Coordinator: waiting on child process ID %d...\n", pid[i]);
        
        int status;
        waitpid(pid[i], &status, 0);

        int *result = (int *)shmat(sharedMemoryId[i], NULL, 0);
        read(fd[i][0], &result, sizeof(int));
        printf("Coordinator: result %d read from shared memory: %d %s divisible by %d.\n", *result, atoi(argv[i+2]), *result ? "is" : "is not", atoi(argv[1]));

        shmctl(*result, IPC_RMID, NULL);
        close(fd[i][0]);
    }


    printf("Coordinator: exiting\n");
    return 0;
}