#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int compare (const void *_a, const void *_b) {
    double a = *(double*)_a;
    double b = *(double*)_b;
    return (a > b) ? 1 : -1;
}

int main(int argc, char *argv[]) {

    int N = 0;
    int n = 0;
    int i;
    int j;
    double max = 0;
    clock_t t;

    if(argc != 3) exit(1);
    sscanf(argv[1], "%d", &N);
    sscanf(argv[2], "%d", &n);

    double *rand_arr = malloc(sizeof(double)*N);
    int *histogram = malloc(sizeof(int)*n);

    srand48(time(NULL));

    for (i = 0; i<n; i++) histogram[i] = 0;
    for (i = 0; i<N; i++) {
        double rand = drand48();
        rand_arr[i] = rand;
        histogram[(int)(n*rand)] += 1;
    }

    for (i = 0; i<n; i++) if (max < histogram[i]) max = histogram[i];

    printf("Rozkład wartości:\n");
    for (i = 0; i<n; i++) {
        int v = histogram[i] / max * 80;
        for (j = 0; j<v; j++) printf("*");
        printf("\n");
    }

    t = clock();
    qsort(rand_arr, N, sizeof(double), compare);
    t = clock() - t;
    printf("Czas wykonywania sortowania (stdlib qsort): %fms\n", ((double)t)/CLOCKS_PER_SEC*1e3);

    for (i = 0; i<n; i++) histogram[i] = 0;
    for (i = 1; i<N; i++) {
        double d = rand_arr[i]-rand_arr[i-1];
        histogram[(int)(n*d)] += 1;
    }

    for (i = 0; i<n; i++) if (max < histogram[i]) max = histogram[i];

    printf("\nRozkład różnic sąsiadów:\n");
    for (i = 0; i<n; i++) {
        int v = histogram[i] / max * 80;
        for (j = 0; j<v; j++) printf("*");
        printf("\n");
    }

    return 0;
}
