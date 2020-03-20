#include <stdio.h>
#include <unistd.h>

int main() {
    if (fork() == 0) {
        printf("[child] pid %d running ps -ef\n", getpid());
        char *args[]= { "/bin/ps", "-ef" , NULL};
        execvp("/bin/ps", args);
    }

    if (fork() == 0) {
        printf("[child] pid %d running free -h\n", getpid());
        char *args[]= { "/bin/free", "-h" , NULL};
        execvp("/bin/free", args);
    }

    printf("[parent] %d\n", getppid());

    return 0;
}