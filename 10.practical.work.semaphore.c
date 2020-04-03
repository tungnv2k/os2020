#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

int isPrime(int p) {
    for (int i = 2; i * i <= p; i++)
        if (p%i==0)
            return 0;
    return 1;
}

void *printPrime() {
    pthread_mutex_lock(&lock);
    for (int p = 2; p < 1000000; p++) {
        if(isPrime(p))
            printf("%d\n", p);
    }
    pthread_mutex_unlock(&lock);
}

void *printFibonacci() {
    pthread_mutex_lock(&lock);
    int t1 = 0, t2 = 1, fib = t1 + t2;
    while (fib <= 1000000) {
        printf("%d\n", fib);
        t1 = t2;
        t2 = fib;
        fib = t1 + t2;
    }
    pthread_mutex_unlock(&lock);
}

int main() {

    pthread_mutex_init(&lock, NULL);

    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL, printPrime, NULL);
    pthread_create(&tid2, NULL, printFibonacci, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}