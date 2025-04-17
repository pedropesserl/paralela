#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
#define MAX 64

int main() {
    double step = 1.0/(double)num_steps;
    
    double sum[MAX] = {0.0};
    #pragma omp parallel num_threads(MAX)
    {
        int ID = omp_get_thread_num();
        for (int i = 0; i < (num_steps / MAX); i++) {
            double x = ((ID * num_steps / MAX) + i + 0.5) * step;
            sum[ID] += 4.0 / (1.0 + x*x);
        }
    }
    double sum_total = 0.0;
    for (int i = 0; i < MAX; i++) {
        sum_total += sum[i];
    }

    double pi = step * sum_total;

    printf("pi = %.15lf\n", pi);

    return 0;
}
