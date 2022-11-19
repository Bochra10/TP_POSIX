#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

pthread_mutex_t AB,BC,CD,BF,EC;

void occuper_segment(){
    int milli_seconds = 1000 * 6;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}


void occuper_AB(int nMetro){
    pthread_mutex_lock(&AB);
    printf("Metro %d occupying AB\n",nMetro);
    occuper_segment();
    pthread_mutex_unlock(&AB);
    printf("AB is available\n");
}

void occuper_BC(int nMetro){
    pthread_mutex_lock(&BC);
    printf("Metro %d occupying BC\n",nMetro);
    occuper_segment();
    pthread_mutex_unlock(&BC);
    printf("BC is available\n");
}
void occuper_CD(int nMetro){
    pthread_mutex_lock(&CD);
    printf("Metro %d occupying CD\n",nMetro);
    occuper_segment();
    pthread_mutex_unlock(&CD);
    printf("CD is available\n");
}
void occuper_BF(int nMetro){
    pthread_mutex_lock(&BF);
    printf("Metro %d occupying FB\n",nMetro);
    occuper_segment();
    pthread_mutex_unlock(&BF);
    printf("FA is available\n");
}
void occuper_EC(int nMetro){
    pthread_mutex_lock(&EC);
    printf("Metro %d occupying EC\n",nMetro);
    occuper_segment();
    pthread_mutex_unlock(&EC);
    printf("EB is available\n");
}

void* ligne_MR1(void* arg){
    int nMetro = *((int*) arg);
    occuper_AB(nMetro);
    occuper_BC(nMetro);
    occuper_CD(nMetro);
    printf("Metro MR1 has arrived to D!\n");
    pthread_exit(NULL);
}
void* ligne_MR2(void* arg){
    int nMetro = *((int*) arg);
    occuper_BF(nMetro);
    occuper_AB(nMetro);
    printf("Metro MR2 has arrived to A!\n");
    pthread_exit(NULL);
}
void* ligne_MR3(void* arg){
    int nMetro = *((int*) arg);
    occuper_EC(nMetro);
    occuper_BC(nMetro);
    occuper_AB(nMetro);
    printf("Metro MR3 has arrived to B!\n");
    pthread_exit(NULL);
}

int main(){
    int counter;
    pthread_t id;
    printf("Welcome to Berlin Metro Stations!\n");
    for(counter=0;counter<3;counter++){
        int* j=(int*)malloc(sizeof(int));
        *j=counter+1;
        pthread_create(&id,NULL,ligne_MR1,j);
        pthread_create(&id,NULL,ligne_MR2,j);
        pthread_create(&id,NULL,ligne_MR3,j);
    }
    pthread_exit(NULL);
}
