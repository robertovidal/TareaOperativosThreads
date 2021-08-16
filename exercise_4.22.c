#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int pointsInCircle;
int points = 1000;

void *generatePoints(void){
    float pointX;
    float pointY;
    pointsInCircle = 0;
    float d;
    srand(time(0));
    for(int i = 0; i < points ; i++){
        pointX = 2 * (random() / ((float)RAND_MAX + 1)) - 1;
        pointY = 2 * (random() / ((float)RAND_MAX + 1)) - 1;
        d = pointX * pointX + pointY * pointY;
        if(d <= 1)
            pointsInCircle++;
    }
}

int main(int argc, char *argv[]){
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, generatePoints, NULL);
    pthread_join(tid, NULL);
    float pi_value = 4 * (float)pointsInCircle / points;
    printf("The calculated value of Pi is: %f\n", pi_value);
    return 1;
}
