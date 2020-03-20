#include <stdio.h>
#include <pthread.h>

int isPrime(int p) {
    for (int i = 2; i * i <= p; i++)
        if (p%i==0)
            return 0;
    return 1;
}

void *printPrime() {
    for (int p = 2; p < 1000000; p++) {
        if(isPrime(p))
            printf("%d\n", p);
    }
}

void *printFibonacci() {
    int t1 = 0, t2 = 1, fib = t1 + t2;
    while (fib <= 1000000) {
        printf("%d\n", fib);
        t1 = t2;
        t2 = fib;
        fib = t1 + t2;
    }
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, printPrime, NULL);
    pthread_create(&tid, NULL, printFibonacci, NULL);

    pthread_exit(NULL);
}