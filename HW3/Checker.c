#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv) {

    if (argc != 4){
        printf("Checker: Incorrect number of arguments\n");
        return -1;
    }

    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]);
    int fd = atoi(argv[3]);

    int sharedMemoryId;
    read(fd, &sharedMemoryId, sizeof(sharedMemoryId));

    printf("Checker process [%d]: starting.\n", getpid());
    printf("Checker process [%d]: read %ld bytes containing shm ID %d\n", getpid(), sizeof(sharedMemoryId), sharedMemoryId);

    int *result = shmat(sharedMemoryId, NULL, 0);

    if(dividend % divisor == 0){
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), dividend, divisor);
        printf("Checker process [%d]: wrote result (1) to shared memory.\n", getpid());
        *result = 1;
    }
    else{
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), dividend, divisor);
        printf("Checker process [%d]: wrote result (0) to shared memory.\n", getpid());
        *result = 0;
    }

    shmdt(result);
    close(fd);

    return 0;
}
