#include <stdio.h>
#include <pthread.h>

void *thread_rountine(void *arg)
{
    int n = *(int*)arg;
    printf("");
}


int main( int argc, char **argv) {
    //printf("%s",argv[1]);
    const int T = atoi (argv[1]);

    pthread_t thr[T]; //-> cria um array de threads
    int status = 0;

    printf("%i", T); 
    return 0;
}
