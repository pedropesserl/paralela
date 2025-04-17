#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;

int main() {
    double step = 1.0/(double)num_steps;
    
    double sum = 0.0;
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x*x);
    }

    double pi = step * sum;

    printf("pi = %.15lf\n", pi);

    return 0;
}
