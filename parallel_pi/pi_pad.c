#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
#define NUM_THREADS 8

int main() {
    double step = 1.0/(double)num_steps;
    int nthreads;
    
    double sum[NUM_THREADS][8] = {{0.0}};
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        if (id == 0) {
            nthreads = nthrds;
        }
        for (int i = id; i < num_steps; i += nthrds) {
            double x = (i + 0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x*x);
        }
    }
    double sum_total = 0.0;
    for (int i = 0; i < nthreads; i++) {
        sum_total += sum[i][0];
    }

    double pi = step * sum_total;

    printf("pi = %.15lf\n", pi);

    return 0;
}
