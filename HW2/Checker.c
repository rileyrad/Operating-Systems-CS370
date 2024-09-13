#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int argOne = atoi(argv[1]);
    int argTwo = atoi(argv[2]);
    printf("Checker process [%d]: Starting.\n", getpid());
    if(argTwo % argOne == 0){
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), argTwo, argOne);
        printf("Checker process [%d]: Returning 1.\n", getpid());
        return 1;
    }
    else{
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), argTwo, argOne);
        printf("Checker process [%d]: Returning 0.\n", getpid());
        return 0;
    }
}
