#include <pthread.h>
#include <stdio.h>
#include <string.h>
float average;
int minimum;
int maximum;

struct arg_struct {
    int amount;
    char **numbers;
};

void *getAverage(void *param){
    struct arg_struct *args = param;
    char **numbers = args->numbers;
    int amount = args->amount;
    int sum = 0;
    for(int i = 1; i < amount; i++){
        sum += atoi(numbers[i]);
    }
    average = sum / (amount - 1);
}

void *getMaximum(void *param){
    struct arg_struct *args = param;
    char **numbers = args->numbers;
    int amount = args->amount;
    maximum = atoi(numbers[1]);
    for(int i = 2; i < amount; i++){
        if(atoi(numbers[i]) > maximum)
            maximum = atoi(numbers[i]);
    }
}

void *getMinimum(void *param){
    struct arg_struct *args = param;
    char **numbers = args->numbers;
    int amount = args->amount;
    minimum = atoi(numbers[1]);
    for(int i = 2; i < amount; i++){
        if(atoi(numbers[i]) < minimum)
            minimum = atoi(numbers[i]);
    }
}

int check_numbers(char **numbers, int amount){
    int length;
    int isNumber;
    for(int i = 1; i < amount; i++){
        length = strlen(numbers[i]);
        isNumber = 1;
        for(int j = 0; j < length; j++){
            if(!isdigit(numbers[i][j]))
                isNumber = 0;
        }
        if(!isNumber){
            printf("The input in the position %d is not a number\n", i);
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]){
    pthread_t tid_average;
    pthread_attr_t attr_average;
    pthread_t tid_maximum;
    pthread_attr_t attr_maximum;
    pthread_t tid_minimum;
    pthread_attr_t attr_minimum;
    if (argc < 2){
        printf("The input numbers are missing");
        return -1;
    }
    int numbersChecked = check_numbers(argv, argc);
    if(!numbersChecked)
        return -1;
    struct arg_struct args;
    args.amount = argc;
    args.numbers = argv;
    pthread_attr_init(&attr_average);
    pthread_attr_init(&attr_maximum);
    pthread_attr_init(&attr_minimum);
    pthread_create(&tid_average, &attr_average, getAverage, (void *)&args);
    pthread_create(&tid_maximum, &attr_maximum, getMaximum, (void *)&args);
    pthread_create(&tid_minimum, &attr_minimum, getMinimum, (void *)&args);
    pthread_join(tid_average, NULL);
    pthread_join(tid_maximum, NULL);
    pthread_join(tid_minimum, NULL);
    printf("The average is %.2f\n", average);
    printf("The minimum is %d\n", minimum);
    printf("The maximum is %d\n", maximum);
    return 0;
}
