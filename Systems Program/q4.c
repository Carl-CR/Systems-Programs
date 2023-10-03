#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* runCommand(void* cmd) {
    system((char*)cmd);

    return NULL;
}

int main() {
    char cmd[258];

    printf("Enter a Linux command: ");
    fgets(cmd, 258, stdin);

    pthread_t thread;
    if (pthread_create(&thread, NULL, runCommand, (void*)cmd) != 0) {
        return 1;
    }

    if (pthread_join(thread, NULL) != 0) {
        return 1;
    }

    return 0;
}