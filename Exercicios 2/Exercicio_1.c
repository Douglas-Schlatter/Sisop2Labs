/** Codigos feitos pro Douglas e Jorge
 * 
 * Comando para compilar e executar
 * gcc -pthread Exercicio_1.c -o ex1
 *./ex1
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000000
#define T 10

// Estrutura global para agrupar as coisas
typedef struct {
    int A[N]; // Vetor para somar
    long long int SUM; // variável SOMA
    pthread_mutex_t mutex; // Mutex
} DataValues;

DataValues GLOBAL_STRUCT; // Criação da estrutura

void *rotina_soma(void *arg){
    int threadId = *(int *)arg;
    int inicio = (N / T) * threadId;
    int fim = 0;

    if(threadId == T - 1){
        fim = N; // Última fatia o fim é N
    } else {
        fim = (N / T) * (threadId + 1); // As outras fatias é N / T vezes a id da thread + 1 (pular o 0)
    }

    for(int i = inicio; i < fim; i++){
        // Não é eficiente -- a chamada de lock é feita a cada iteração do laço
        /* Quantidade de chamadas para T = 10
            10x Mutex_lock + 10x OperadorSoma + 10x Mutex_unlock;
        */
        pthread_mutex_lock(&GLOBAL_STRUCT.mutex); // seção crítica
        GLOBAL_STRUCT.SUM += GLOBAL_STRUCT.A[i];
        pthread_mutex_unlock(&GLOBAL_STRUCT.mutex); // encerra seção.
    }

    // Possível melhoria:
    /* Somar em uma variável local a soma e DEPOIS somar 1 vez no somador.
    Dessa forma fazendo apenas uma chamada da função de lock e unlock.
    Com essa melhoria: T = 10
        1x Mutex_lock + 11x OperadorSoma + 1x MutexUnlock

    pthread_mutex_lock(&GLOBAL_STRUCT.mutex); // seção crítica
    GLOBAL_STRUCT.SUM += SomaLocal; // Soma uma vez
    pthread_mutex_unlock(&GLOBAL_STRUCT.mutex); // encerra seção.
    */
}

int main(){
    pthread_t thr[T];
    int id[T];
    int status = 0;

    GLOBAL_STRUCT.SUM = 0; // Inicializa a variável de soma global
    pthread_mutex_init(&GLOBAL_STRUCT.mutex, NULL); // Inicializa mutex

    printf("Calculando com um total de %d fatias\n", T);

    for(int i = 0; i < N; i++){
        GLOBAL_STRUCT.A[i] = 1; // Coloca o valor de soma em toda posições do vetor
    }

    for(int i = 0; i < T; i++){
        id[i] = i;
        status = pthread_create(&thr[i], NULL, rotina_soma, &id[i]); // Falta verificação de erro
    }

    // Aguarda threads
    for(int i = 0; i < T; i++){
        pthread_join(thr[i], NULL);
    }

    
    long long int SUM_seq = 0;
    for(int i = 0; i < N; i++){
        SUM_seq += GLOBAL_STRUCT.A[i]; // Conferencia final;
    }

    printf("Soma Paralela COM exclusao mutua = %lld\n", GLOBAL_STRUCT.SUM);
    printf("Soma Sequencial   = %lld\n", SUM_seq);
    if(GLOBAL_STRUCT.SUM == SUM_seq){
        printf("OK\n");
    } else {
        printf("ERRO\n");
    }

    pthread_mutex_destroy(&GLOBAL_STRUCT.mutex);

    return 0;
}