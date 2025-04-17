#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
#define NUM_THREADS 4

int main() {
    double step = 1.0/(double)num_steps;
    
    double sum = 0.0;
#pragma omp parallel num_threads(NUM_THREADS)
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        double sum_local = 0.0;
        for (int i = id; i < num_steps; i += nthrds) {
            double x = (i + 0.5) * step;
            sum_local += 4.0 / (1.0 + x*x);
        }
#pragma omp atomic
        sum += sum_local;
    }

    double pi = step * sum;

    printf("pi = %.15lf\n", pi);

    return 0;
}
