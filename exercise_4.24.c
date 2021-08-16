#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Jose Pablo Fernández Cubillo
// Roberto Vidal Patiño

void *primeNumbers(void *param){
  int isPrime;
  
  for(int num = *((int *) param); num > 1; num--){
    isPrime = 1;
    for(int i = 2; i <= num/2; i++){
      if(num % i == 0){
        isPrime = 0;
      }
    }
    if(isPrime){
      printf("%d ", num);
    }
  }
  printf("\n");
  pthread_exit(0);
}

int main(){
  int n;
  int * num;
  printf("Ingrese un número entero positvo: ");
  scanf("%d", &n);
  num = &n;
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, primeNumbers, num);
  pthread_join(thread_id, NULL);
  return 0;
}