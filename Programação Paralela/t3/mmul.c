// TRABALHO3: CI316 1o semestre 2023 (mmul.c)
// Aluno: Paulo Mateus Luza Alves - GRR: GRR20203945
// Aluno: Luis Felipe Risch - GRR: GRR20203940

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "chrono.c"
#include <assert.h>

// defines
#define DEBUG 0
#define EPSILON 1e-9
#define GIGA 1e9

// Global variables
const double SEED = 0.1;

int nla, ncb, m;
int nproc, process_id;
chronometer_t myBroadcastChrono;

/* ============================== Auxiliary Functions ============================== */
double **alloc_matrix(int lines, int columns)
{
    double **matrix = (double **)calloc(lines, sizeof(double *));
    matrix[0] = (double *)calloc(lines * columns, sizeof(double));
    for (int i = 0; i < lines; ++i)
        matrix[i] = matrix[0] + i * columns;
    return matrix;
}

void free_matrix(double **matrix)
{
    free(matrix[0]);
    free(matrix);
}

int is_equal_double(double a, double b)
{
    return fabs(a - b) < EPSILON;
}
/* ============================== Auxiliary Functions ============================== */

void sequential_mult_matrix(double **matrix_a, double **matrix_b, double **matrix_c)
{
    int i, j, k;

    for (i = 0; i < nla; i++)
        for (j = 0; j < ncb; j++)
            for (k = 0; k < m; k++)
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
}

void parallel_mult_matrix(double **matrix_a, double **matrix_b, double **matrix_c)
{
    // int i, j, k;
    // int scatter_size;
    // double **submatrix;

    // scatter_size = nla / nproc;
    // submatrix = alloc_matrix(scatter_size, m);

    // MPI_Bcast(matrix_b[0], m * ncb, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // MPI_Scatter(matrix_a[0], scatter_size * m, MPI_DOUBLE, submatrix[0], scatter_size * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // for (i = 0; i < scatter_size; i++)
    //     for (j = 0; j < ncb; j++)
    //         for (k = 0; k < m; k++)
    //             matrix_c[i + (process_id * scatter_size)][j] += submatrix[i][k] * matrix_b[k][j];

    // // if (process_id == 0)
    // //     MPI_Gather(MPI_IN_PLACE, scatter_size * m, MPI_DOUBLE, matrix_c[0], scatter_size * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // // else
    // // MPI_Gather(matrix_c[scatter_size * process_id], scatter_size * m, MPI_DOUBLE, matrix_c[scatter_size * process_id], scatter_size * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // free_matrix(submatrix);

    int i, j, k;
    int scatter_size;
    double **submatrix;

    scatter_size = nla / nproc;
    submatrix = alloc_matrix(scatter_size, m);

    MPI_Bcast(matrix_b[0], m * ncb, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(matrix_a[0], scatter_size * m, MPI_DOUBLE, submatrix[0], scatter_size * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (i = 0; i < scatter_size; i++)
        for (j = 0; j < ncb; j++)
            for (k = 0; k < m; k++)
                matrix_c[0][j] += submatrix[i][k] * matrix_b[k][j];

    // if (process_id == 0)
    //     MPI_Gather(MPI_IN_PLACE, scatter_size * m, MPI_DOUBLE, matrix_c[0], scatter_size * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // else
    MPI_Gather(matrix_c[scatter_size * process_id], scatter_size * m, MPI_DOUBLE, matrix_c[scatter_size * process_id], scatter_size * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    free_matrix(submatrix);
}

int verify_mult(double **matrix_a, double **matrix_b, double **matrix_c)
{
    int is_equal, i, j;
    double **result;

    is_equal = 1;

    result = alloc_matrix(nla, ncb);
    sequential_mult_matrix(matrix_a, matrix_b, result);

    for (i = 0; i < nla && is_equal; i++)
        for (j = 0; j < ncb && is_equal; j++)
            if (!is_equal_double(matrix_c[i][j], result[i][j]))
            {
                fprintf(stderr, "Erro no calculo: posiçao matrix_c[%d][%d] = %f, porem deveria ser %f\n", i, j, matrix_c[i][j], result[i][j]);
                is_equal = 0;
            }

    // printf("\nmatrix_c: %d\n", process_id);
    // for (int i = 0; i < nla; ++i)
    // {
    //     for (int j = 0; j < m; ++j)
    //         printf("%f ", matrix_a[i][j]);
    //     printf("\n");
    // }
    // printf("\nresult: %d\n", process_id);
    // for (int i = 0; i < nla; ++i)
    // {
    //     for (int j = 0; j < ncb; ++j)
    //         printf("%f ", result[i][j]);
    //     printf("\n");
    // }
    // printf("\nmatrix_c: %d\n", process_id);
    // for (int i = 0; i < nla; ++i)
    // {
    //     for (int j = 0; j < ncb; ++j)
    //         printf("%f ", matrix_c[i][j]);
    //     printf("\n");
    // }

    free_matrix(result);
    return is_equal;
}

int main(int argc, char *argv[])
{
    int is_verify, name_lenght;
    unsigned long long flops_qty;
    double total_time, throughput;
    double **matrix_a, **matrix_b, **matrix_c;
    char host_name[MPI_MAX_PROCESSOR_NAME];

    // Parser function
    is_verify = 0;
    if (argc < 4)
    {
        fprintf(stderr, "usage: mpirun -np <np> %s <nla> <m> <lcb> (-v)\n", argv[0]);
        return 0;
    }
    else
    {
        nla = atoi(argv[1]);
        m = atoi(argv[2]);
        ncb = atoi(argv[3]);
        if (nla % 3 != 0 || nla % 4 != 0)
        {
            fprintf(stderr, "nla deve ser multiplo de 3 e 4\n");
            return 0;
        }
        if (argc == 5 && !strcmp(argv[argc - 1], "-v"))
            is_verify = 1;
    }

    // allocate memory for the matrix
    matrix_a = alloc_matrix(nla, m);
    matrix_b = alloc_matrix(m, ncb);
    matrix_c = alloc_matrix(nla, ncb);
    if (!matrix_a || !matrix_b || !matrix_c)
    {
        fprintf(stderr, "Erro de alocacao\n");
        return 0;
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Get_processor_name(host_name, &name_lenght);

    // filling the matrix
    if (process_id == 0)
    {
        // for (int i = 0; i < nla; ++i)
        //     for (int j = 0; j < m; ++j)
        //         matrix_a[i][j] = i + j + SEED;
        // for (int i = 0; i < m; ++i)
        //     for (int j = 0; j < ncb; ++j)
        //         matrix_b[i][j] = (i * 2) + j + SEED;
        for (int i = 0; i < nla; ++i)
            for (int j = 0; j < m; ++j)
                matrix_a[i][j] = 1;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < ncb; ++j)
                matrix_b[i][j] = 1;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // startting counting the time
    if (process_id == 0)
    {
        chrono_reset(&myBroadcastChrono);
        chrono_start(&myBroadcastChrono);
    }

    printf("rank: %d, host: %s\n", process_id, host_name);
    if (nproc == 1)
        sequential_mult_matrix(matrix_a, matrix_b, matrix_c);
    else
        parallel_mult_matrix(matrix_a, matrix_b, matrix_c);

    if (process_id == 0)
    {
        chrono_stop(&myBroadcastChrono);

        flops_qty = 1;
        flops_qty *= nla * ncb * m;
        flops_qty *= 2;
        total_time = (double)chrono_gettotal(&myBroadcastChrono) / ((double)1000 * 1000 * 1000);
        throughput = (double)(flops_qty / (GIGA * total_time));
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (process_id == 0)
    {
        printf("\n");
        if (!is_verify)
        {
            printf("total_time: %lf s\n", total_time);
            printf("Throughput: %lf GFLOPS\n", throughput);
        }
        else
        {
            if (!verify_mult(matrix_a, matrix_b, matrix_c))
                printf("Um erro na resolução foi encontrado!\n");
            else
                printf("Resultado calculado corretamente!\n");
        }
    }

#if DEBUG == 1
    printf("matrix_a: %d\n", process_id);
    for (int i = 0; i < nla; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("%f ", matrix_a[i][j]);
        printf("\n");
    }
    printf("\nmatrix_b: %d\n", process_id);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < ncb; ++j)
            printf("%f ", matrix_b[i][j]);
        printf("\n");
    }
    printf("\nmatrix_c: %d\n", process_id);
    for (int i = 0; i < nla; ++i)
    {
        for (int j = 0; j < ncb; ++j)
            printf("%f ", matrix_c[i][j]);
        printf("\n");
    }
#endif

    free_matrix(matrix_a);
    free_matrix(matrix_b);
    free_matrix(matrix_c);
    MPI_Finalize();
    return 0;
}