#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int cityA = 0, cityB = 0;
int bridgeA = 0, bridgeB = 0;

pthread_cond_t move = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex_A, mutex_B;
pthread_mutex_t bridge;

void *moveAtoB(void *carNr);
void *moveBtoA(void *carNr);
void *queueA(void *carNr);
void *queueB(void *carNr);

void *moveAtoB(void *carNr) {
    pthread_mutex_lock(&bridge);
    pthread_cond_signal(&move);
    pthread_cond_wait(&move, &bridge);	

    bridgeA--;
    printf("A - %d %d>>> [>>%d>>] <<<%d %d - B\n", cityA, bridgeA, carNr, bridgeB, cityB);
    cityB++;

    sleep(1);
    pthread_mutex_unlock(&bridge);
    sleep(1);
    
    queueB(carNr);
    return 0;
}
    
void *moveBtoA(void *carNr) {
    pthread_mutex_lock(&bridge);
    pthread_cond_signal(&move);
    pthread_cond_wait(&move, &bridge);
    
    bridgeB--;
    printf("A - %d %d>>> [<<%d<<] <<<%d %d - B\n", cityA, bridgeA, carNr, bridgeB, cityB);
    cityA++;
    
    sleep(1);
    pthread_mutex_unlock(&bridge);
    sleep(1);
    queueA(carNr);
    return 0;
}
    
void *queueA(void *carNr) {
    pthread_mutex_lock(&mutex_A);
    sleep(1);
    cityA--;
    bridgeA++;
    printf("A - %d %d>>> [<<-<<] <<<%d %d - B\n", cityA, bridgeA, bridgeB, cityB);
    pthread_mutex_unlock(&mutex_A);
    moveAtoB(carNr);
    return 0;
}
    
void *queueB(void *carNr) {
    while(1) {
        pthread_mutex_lock(&mutex_B);
        sleep(1);

        cityB--;
        bridgeB++;
        printf("A - %d %d>>> [<<-<<] <<<%d %d - B\n", cityA, bridgeA, bridgeB, cityB);

        pthread_mutex_unlock(&mutex_B);
        moveBtoA(carNr);
    }
    return 0;
}
    
int main(int argc, char *argv[]) {
    int carsAmount = 0;
    
    while (carsAmount < 4) {
        printf ("\nHow many cars? (minimum 4) ");
        scanf ("%d", &carsAmount);
        printf ("\n");
    }

    int carNr = 0;
    int randomValue;
    time_t actualTime;
    pthread_t car[carsAmount + 1];

    srand((unsigned) time(&actualTime));

    pthread_mutex_init(&bridge, NULL);
    pthread_mutex_init(&mutex_A, NULL);
    pthread_mutex_init(&mutex_B, NULL);

    pthread_mutex_lock(&bridge);
    pthread_mutex_lock(&mutex_A);
    pthread_mutex_lock(&mutex_B);
    
    for (carNr = 1; carNr <= carsAmount; carNr++) {
        randomValue = rand() % (carsAmount / 4);

        if (randomValue % 4 == 0) {
            cityA++;
            pthread_create(&car[carNr], NULL, &queueA, (void*) carNr);
        }
    
        if (randomValue % 4 == 1) {
            cityB++;
            pthread_create(&car[carNr], NULL, &queueB, (void*) carNr);
        }
        
        if (randomValue % 4 == 2) {
            bridgeA++;
            pthread_create(&car[carNr], NULL, &moveAtoB, (void*) carNr);
        }
    
        if (randomValue % 4 == 3) {
            bridgeB++;
            pthread_create(&car[carNr], NULL, &moveBtoA, (void*) carNr);
        }
    }

    pthread_mutex_unlock(&mutex_A);
    pthread_mutex_unlock(&mutex_B);
    pthread_mutex_unlock(&bridge);
    
    for (carNr = 1; carNr <= carsAmount; carNr++) 
        pthread_join(car[carNr], NULL);
    
    
    return 0;
}