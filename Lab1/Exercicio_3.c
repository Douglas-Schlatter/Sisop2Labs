/** Codigos feitos pro Douglas e Jorge
 * 
 * Comando para compilar e executar
 * gcc -pthread exercicio_3.c -o ex3
 *./ex3
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000000
#define T 10

int A[N];
long long int SUM = 0;

void *rotina_soma(void *arg){
    int threadId = *(int *)arg;
    int inicio = (N / T) * threadId;
    int fim = 0;

    if(threadId == T - 1){
        fim = N;
    } else {
        fim = (N / T) * (threadId + 1);
    }

    for(int i = inicio; i < fim; i++){
        SUM += A[i]; // Soma
    }
}

int main(){
    pthread_t thr[T];
    int status = 0;
    int id[T] = { 0 };
    printf("Calculando com um total de %d fatias\n", T);
    for(int i = 0; i < N; i++){
        A[i] = 1;
    }

    for(int i = 0; i < T; i++){
        id[i] = i; // Deixa um id na thread
        status = pthread_create(&thr[i], NULL, rotina_soma, &id[i]); // Rotina de soma
    }

    for(int i = 0; i < T; i++){
        status = pthread_join(thr[i], NULL); // Join
    }

    // Soma sequencial correta
    long long SUM_seq = 0;
    for (int i = 0; i < N; i++) {
        SUM_seq += A[i];
    }

    // Resultados
    printf("Sum Paral. = %lld\n", SUM);
    printf("Soma Seq = %lld\n", SUM_seq);
    if (SUM == SUM_seq) {
        printf("OK\n");
    } else {
        printf("ERRO\n");
    }

    return 0;
}
