#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t lock;

int isPrime(int p) {
    for (int i = 2; i * i <= p; i++)
        if (p%i==0)
            return 0;
    return 1;
}

void *printPrime() {
    for (int p = 2; p < 1000000; p++) {
        if(isPrime(p)) {
            sem_wait(&lock);
            printf("%d\n", p);
            sem_post(&lock);
        }
    }
}

void *printFibonacci() {
    int t1 = 0, t2 = 1, fib = t1 + t2;
    while (fib <= 1000000) {
        sem_wait(&lock);
        printf("%d\n", fib);
        sem_post(&lock);

        t1 = t2;
        t2 = fib;
        fib = t1 + t2;
    }
}

int main() {

    sem_init(&lock, 0, 1);

    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL, printPrime, NULL);
    pthread_create(&tid2, NULL, printFibonacci, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&lock);

    return 0;
}
