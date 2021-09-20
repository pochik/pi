#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
struct ctx {
        int thread_number;
        double loc_res;
};

int num_steps;
int nthreads;

void * Pi(void *arg) {
        double localpi = 0.0;
        int i = ((struct ctx *) arg)->thread_number;
        for (i; i < num_steps ; i += nthreads) {
                localpi += 1.0/(i*4.0 + 1.0);
                localpi -= 1.0/(i*4.0 + 3.0);
        }
        ((struct ctx *)arg)->loc_res = localpi;
}

int main(int argc, char** argv) {

    double pi = 0;
    int i;
    pthread_t * ids;
    struct ctx * params;

    num_steps = atol(argv[1]);
    nthreads = atol(argv[2]);

    params = malloc(nthreads*sizeof(struct ctx));
    ids = malloc(nthreads*sizeof(pthread_t));
    time_t start = clock();
    for(i = 0; i < nthreads; i++) {
            params[i].thread_number = i;
            pthread_create(ids + i, NULL, Pi, (void*)(params + i));
    }

    for(i = 0; i < nthreads; i++) {
            struct ctx * res;
            pthread_join(ids[i], (void **)&res);
            pi += res->loc_res;
    }
    time_t end = clock();
    printf("Elapsed time is %lf seconds\n",(double)(end - start) / (double) (CLOCKS_PER_SEC));
    pi *= 4.0;
    printf ("Результат ПИ = %.26f\n", pi);
    return 0;
}
