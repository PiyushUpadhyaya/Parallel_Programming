//First Input size of matrix and second number of threads.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char*argv[])
{
    int i, sum = 0;
    double x,x_parallel;
    int input_size,num_threads,split_size;
    float *input,sum_seq = 0.0;
    double time_start = 0.0;
    double time_end = 0.0;
    struct timeval tv;
    if(argc!=3)
    {
        printf("\nVery Few Arguments\n");
        exit(-1);
    }
    input_size = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    printf("\n\t\t Threads     : %d ",num_threads);
    printf("\n\t\t Array Size  : %d\n",input_size);
    input = (float *)malloc(sizeof(float)*input_size);
    for(i=0; i<input_size; i++)
    {
        input[i] = i+2;
      //  printf("%f ",input[i]);
    }
    gettimeofday(&tv, 0);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    for(i=0; i<input_size; i++)
    {
        sum_seq = input[i] + sum_seq ;
    }
    gettimeofday(&tv, 0);
	time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
	double result_seq = time_end - time_start;

    omp_set_num_threads(num_threads);
    gettimeofday(&tv, 0);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        for(i=id; i<input_size; i = i + 2)
        {
            sum = sum + input[i];

        }
    }
    gettimeofday(&tv, 0);
    time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    double result_parallel = time_end - time_start;
    printf("\nParallel Time is %f \n Sequential Time is %f\n",result_parallel,result_seq);
    free(input);
    printf("\nThe sum is %d\n",sum);

    exit(0);
}

