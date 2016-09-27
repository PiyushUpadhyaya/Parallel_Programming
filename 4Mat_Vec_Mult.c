#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char*argv[])
{
    int i, j,sum = 0;
    double x,x_parallel;
    int input_size,num_threads,split_size;
    float **matrix,*vector,*result;
    double time_start = 0.0;
    double time_end = 0.0;
    struct timeval tv;
    if(argc!=4)
    {
        printf("\nVery Few Arguments\n");
        exit(-1);
    }
    int row_size = atoi(argv[1]);
    int col_size = atoi(argv[2]);
    num_threads = atoi(argv[3]);
    printf("\n\t\t Threads     : %d ",num_threads);
    printf("\n\t\t Array Size  : %dX%d\n",row_size,col_size);
    printf("\nMatrix is :: \n");
    matrix = (float **)malloc(sizeof(float *)*row_size);
    for(i=0; i<row_size; i++)
    {
        printf("\n");
        matrix[i] = (float *)malloc(sizeof(float)*col_size);
        for(j=0; j<col_size; j++)
        {
            matrix[i][j] = i+2*j;
            printf("%f  ",matrix[i][j]);
        }
    }
    vector = (float *)malloc(sizeof(float) * col_size);
    result = (float *)malloc(sizeof(float) * col_size);
    printf("\nVector is :: \n");
    for(i=0; i<col_size; i++)
    {
            vector[i] = 2*i+1;
            printf("%f  ",vector[i]);
            result[i] = 0.0;
    }
    gettimeofday(&tv, 0);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    ///////////SEQUENTIAL
    for(i=0; i<row_size; i++)
    {
        for(j=0; j<col_size; j++)
            {
                result[i] = result[i] + matrix[i][j]*vector[j];
            }
    }
    gettimeofday(&tv, 0);
    time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    double result_seq = time_end - time_start;
    ////////////////PARALLEL
    omp_set_num_threads(num_threads);
    printf("\nResult is :: \n");
    gettimeofday(&tv, 0);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    #pragma omp parallel for private(j)
    for(i=0; i<row_size; i++)
    {
        for(j=0; j<col_size; j++)
            {
                result[i] = result[i] + matrix[i][j]*vector[j];
            }
    }
    gettimeofday(&tv, 0);
    time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    double result_parallel = time_end - time_start;

    for(i=0; i<row_size; i++)
    {
        printf("%f  ",result[i]);
    }
    printf("\nParallel Time is %f \n Sequential Time is %f\n",result_parallel,result_seq);
    free(matrix);
    free(vector);
    exit(0);
}

