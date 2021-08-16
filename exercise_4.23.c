#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Jose Pablo Fernández Cubillo
// Roberto Vidal Patiño

int main(int argc, char *argv[]){
    int pointsInCircle;
    int points = 1000;
    float pointX;
    float pointY;
    pointsInCircle = 0;
    float d;
    srand(time(0));
    #pragma omp parallel for
    for(int i = 0; i < points ; i++){
        pointX = 2 * (random() / ((float)RAND_MAX + 1)) - 1;
        pointY = 2 * (random() / ((float)RAND_MAX + 1)) - 1;
        d = pointX * pointX + pointY * pointY;
        if(d <= 1)
            pointsInCircle++;
    }
    float pi_value = 4 * (float)pointsInCircle / points;
    printf("The calculated value of Pi is: %f\n", pi_value);
    return 1;
}
