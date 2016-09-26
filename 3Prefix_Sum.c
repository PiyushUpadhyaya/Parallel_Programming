//First Input size of matrix and second number of threads.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char*argv[])
{
    int i,j, sum = 0;
    int input_size,num_threads;
    input_size = 64;
    num_threads = 2;
    double time_start = 0.0;
    double time_end = 0.0;
    struct timeval tv;

    int input[input_size],dummy[4][8];
    int k = log(input_size);

    printf("\n\t\t Threads     : %d ",num_threads);
    printf("\n\t\t Array Size  : %d\n",input_size);
    for(i=0; i<input_size; i++)
    {
        input[i] = i+1;
        //printf("%d ",input[i]);
        dummy[0][i] = input[i];
    }
    for(i=1; i<4; i++)
    {
        for(j=0; j<input_size; j++)
        {
            dummy[i][j] = 0;
        }
    }
    //up sweep
    gettimeofday(&tv, 0);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    for(i=1; i<4; i++)
    {
        #pragma omp parallel

        {
            for(j=pow(2,i); j<=input_size; j = j + pow(2,i))
            {
                dummy[i][j-1] = dummy[i-1][j-1] + dummy[i-1][j - (int)pow(2,i-1)-1];

            }
        }
    }
    /* for(i=0; i<4; i++)
    {
        for(j=0; j<8; j++)
        {
            printf("%d ",dummy[i][j]);

        }
            printf("\n");
    }*/
    //down sweep
    int dummy2[8]= {0,0,0,0,0,0,0,0};
    int w;
    for(i = 2; i>=0; i--)
    {

        for(j = pow(2,i); j<=8 ; j = w + pow(2,i))
        {

            for(w = j; w<j+pow(2,i); w++)
            {
                dummy2[w] = dummy[i][j-1] + dummy2[w];
            }
        }
    }
    gettimeofday(&tv, 0);
    time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    double result_seq = time_end - time_start;
    /* for(w = 0;w<8;w++)
                 {
                     //dummy2[w] = dummy[i][w] + dummy2[w] + dummy2[j-1];
                      printf("%d ", dummy2[w]+dummy[0][w]);
                 }

    */
    printf("\nParallel Time is %f \n",result_seq);

    exit(0);
}

