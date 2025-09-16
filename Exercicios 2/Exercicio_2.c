/** Codigos feitos pro Douglas e Jorge
 * 
 * Comando para compilar e executar
 * gcc -pthread Exerc_5.c -o ex5
 *./ex5
 * 
*/

#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t vagas; // global

// Função da thread (carro)
void *carro_func(void *arg){
    int id = *(int *)arg;
    srand(time(NULL) + id * 100); // A seed tem que iniciar aqui pra ser randomica de verdade
    // e se tirar a soma ela deixa de ser randômica dnv.

    //(1 a 4 segundos)
    int chegada = rand() % 4 + 1; // segundos
    sleep(chegada);
    printf("[CHEGOU] Carro %d chegou depois de %d segundos\n", id, chegada);

    sem_wait(&vagas); // P() - espera vaga
    printf("[ESTACIONOU] Carro %d entrou no estacionamento\n", id);

    //(1 a 3 segundos)
    int uso = rand() % 3 + 1; // segundos
    sleep(uso);
    printf("[SAIU] Carro %d saindo depois de %d segundos\n", id, uso);

    sem_post(&vagas); // V() - libera vaga
}

int main(int argc, char *argv[]){
    int value = 0;
    int value2 = 0;
    if(argv[1] == NULL || argv[2] == NULL){
        value = 3; // Evita erro de compilação
        value2 = 1;
        printf("Uso: ./<nome>.exe <quantidade_carros> <quantidade_vagas> \n");
        printf("===================================================\n\n");
        printf("inicializando com valores padrao Carros = 3, Vagas = 1 \n");
    } else {
        value = atoi(argv[1]);
        value2 = atoi(argv[2]);
    }
    const int N = value;
    const int S = value2;
    printf("Numero de Carros a ser iniciada %i \n", N);
    printf("Numero de Vagas %i \n", S);
    //===================================================
    // Código efetivo:
    pthread_t carros[N]; // vrum vrum
    int id[N]; // placa
    int status = 0; // situação do carro

    sem_init(&vagas, 0, S); // ini semaforo

    for(int i = 0; i < N; i++){
        id[i] = i + 1; // define a placa dos carros
        pthread_create(&carros[i], NULL, carro_func, &id[i]);
    }

    for(int i = 0; i < N; i++){
        pthread_join(carros[i], NULL);
    }

    sem_destroy(&vagas); // Destruir semaforo pew pew

    return 0;
}