#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int compare (const void *_a, const void *_b) {
    double a = *(double*)_a;
    double b = *(double*)_b;
    return (a > b) ? 1 : -1;
}

void print_histogram(int* histogram, int n, char* title) {
    int i, j;
    double max = 0;

    fprintf(stderr, "%s\n", title);
    for (i = 0; i<n; i++) if (max < histogram[i]) max = histogram[i];
    for (i = 0; i<n; i++) {
        int v = histogram[i] / max * 80;
        for (j = 0; j<v; j++) fprintf(stderr, "*");
        fprintf(stderr, "\n");
    }
}

int main(int argc, char *argv[]) {

    double N = 0;
    double n = 0;
    int i;
    

    if(argc != 3) exit(1);
    sscanf(argv[1], "%le", &N);
    sscanf(argv[2], "%le", &n);

    double *rand_arr = malloc(sizeof(double)*N);
    int *histogram = malloc(sizeof(int)*n);

    srand48(time(NULL));

    for (i = 0; i<n; i++) histogram[i] = 0;
    for (i = 0; i<N; i++) {
        double rand = drand48();
        rand_arr[i] = rand;
        histogram[(int)(n*rand)] += 1;
    }

    /* print_histogram(histogram, n, "\nRozkład wartości:"); */

    clock_t start = clock();
    qsort(rand_arr, N, sizeof(double), compare);
    clock_t end = clock();

    /* fprintf(stderr, "Czas wykonywania sortowania (stdlib qsort):\n"); */
    printf("%e\t%e\n", N, ((double)(end-start))/CLOCKS_PER_SEC*1e3);

    for (i = 0; i<n; i++) histogram[i] = 0;
    for (i = 1; i<N; i++) {
        double d = rand_arr[i]-rand_arr[i-1];
        histogram[(int)(n*d)] += 1;
    }

    /* print_histogram(histogram, n, "\nRozkład różnic sąsiadów:"); */

    free(rand_arr);
    free(histogram);

    return 0;
}
