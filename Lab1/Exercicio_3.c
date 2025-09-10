/** Codigos feitos pro Douglas e Jorge
 * 
 * Comando para compilar e executar
 * gcc -pthread exercicio_2.c -o ex1
 *./ex1
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define N 1000000

void *thread_routine(void *arg){
    int n = *(int*)arg;
    printf("Oi! Eu sou a thread %d \n", n);

}

int main(int argc, char *argv[]){
    const int T = atoi(argv[1]);
    printf("Numero de threads a ser iniciada %i \n", T);
    pthread_t thr[T];
    int status = 0;
    int id[N];

    for(int i = 0; i < T; i++){
        id[i] = 10 + i;
        status = pthread_create(&thr[i], NULL, thread_routine, &id[i]);
    }

    for(int i = 0; i < T; i++){
        status = pthread_join(thr[i], NULL);
    }

    return 0;
}
