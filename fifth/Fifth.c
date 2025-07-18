#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// prototype
double **new_Matrix(int n);
void free_Matrix(double **matrix, int n); //
void read_file(const char *filename, double ***matrix, int *n);
double DET(double **matrix, int n);

void read_file(const char *filename, double ***matrix, int *n)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n);

    *matrix = new_Matrix(*n);

    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            fscanf(file, "%lf", &((*matrix)[i][j]));
        }
    }
    fclose(file);
}

void free_Matrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

double DET(double **matrix, int n)
{
    if (n == 1)
    {
        return matrix[0][0];
    }

    if (n == 2)
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    double det = 0.0;

    for (int i = 0; i < n; i++)
    {
        double **subM = new_Matrix(n - 1);

        for (int j = 1; j < n; j++)
        {
            int index = 0;
            for (int x = 0; x < n; x++)
            {
                if (x == i)
                    continue;

                subM[j - 1][index] = matrix[j][x];  
                index++;
            }
        }

        double temp_det = DET(subM, n - 1);

        int sign;
        if (i % 2 == 0)
        {
            sign = 1; // Even
        }
        else
        {
            sign = -1; //ODD
        }

        det += sign * matrix[0][i] * temp_det; 

        free_Matrix(subM, n - 1);
    }

    return det;
}

double **new_Matrix(int n)
{
    double **matrix = (double **)malloc(n * sizeof(double *));
    
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    return matrix;
}

int main(int argc, char **argv)
{
      if (argc < 2)
  {
    fprintf(stderr, "./third {text file}\n");
    exit(1);
  }

    double **matrix;
    int n;

    read_file(argv[1], &matrix, &n);

    double result = DET(matrix, n);
    printf("%.0lf\n", result);

    free_Matrix(matrix, n);

    return EXIT_SUCCESS;
}
