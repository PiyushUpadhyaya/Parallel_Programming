//First Input size.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char*argv[])
{
    int i;
    double x,x_parallel;
    int size = atoi(argv[1]);
    int input_size[size];
    for(i=0;i<size;i++)
    {
        input_size[i] = (2*i + 1)%23;
        if(i==1)
            input_size[1] = 1;
    }
    int num_threads;
    num_threads = 2;
    double time_start = 0.0;
    double time_end = 0.0;
    struct timeval tv;
    printf("\n\t\t Threads     : %d \n",num_threads);


    int height = 0;
    gettimeofday(&tv, 0);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    omp_set_num_threads(num_threads);
    while(height != 3)
    {
        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            for(i=id; i<13; i = i + 2)
            {
                if (input_size[i]!= 1)
                    input_size[i] = input_size[input_size[i]];

            }

        }
        height++;
    }
    gettimeofday(&tv, 0);
	time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
	double result_parallel = time_end - time_start;
	printf("\nParallel Time is %f\n",result_parallel);
    for(i=0; i<13; i++)
    {
        printf("\t%d",input_size[i]);
    }
    exit(0);
}

