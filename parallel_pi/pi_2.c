#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
#define NUM_THREADS 4

int main() {
    double step = 1.0/(double)num_steps;
    int nthreads;
    
    double sum[NUM_THREADS] = {0.0};
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        if (id == 0) {
            nthreads = nthrds;
        }
        double sum_thread = 0.0;
        for (int i = id; i < num_steps; i += nthrds) {
            double x = (i + 0.5) * step;
            sum_thread += 4.0 / (1.0 + x*x);
        }
        sum[id] += sum_thread;
    }
    double sum_total = 0.0;
    for (int i = 0; i < nthreads; i++) {
        sum_total += sum[i];
    }

    double pi = step * sum_total;

    printf("pi = %.15lf\n", pi);

    return 0;
}
