#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;

int main() {
    double step = 1.0/(double)num_steps;
    
    double sum = 0.0;
#pragma omp parallel
    {
        double sum_local = 0.0;
        #pragma omp for
        for (int i = 0; i < num_steps; i++) {
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
