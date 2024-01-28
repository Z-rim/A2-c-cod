#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

void readMatrixFromFile(const char *filename, int matrix[MAX_SIZE][MAX_SIZE], int *rows, int *cols)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols); // Read number of rows and columns

    for (int i = 0; i < *rows; ++i)
    {
        for (int j = 0; j < *cols; ++j)
        {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
}

void writeMatrixToFile(const char *filename, int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fprintf(file, "%d %d\n", rows, cols); // Write number of rows and columns

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void generateRandomMatrix(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrix[i][j] = rand() % 100; // Generating random numbers between 0 and 99
        }
    }
}

void multiplyMatrices(int result[MAX_SIZE][MAX_SIZE], int matrix1[MAX_SIZE][MAX_SIZE], int rows1, int cols1,
                      int matrix2[MAX_SIZE][MAX_SIZE], int rows2, int cols2)
{
    if (cols1 != rows2)
    {
        printf("Matrix multiplication not possible: Number of columns in the first matrix "
               "is not equal to the number of rows in the second matrix.\n");
        exit(1);
    }

    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < cols1; ++k)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int rows1, cols1, rows2, cols2;
    int matrix1[MAX_SIZE][MAX_SIZE], matrix2[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];

    if (argc == 3)
    {

        readMatrixFromFile(argv[1], matrix1, &rows1, &cols1);
        readMatrixFromFile(argv[2], matrix2, &rows2, &cols2);
    }
    else
    {

        int size;
        printf("Enter the size of the square matrices: ");
        scanf("%d", &size);

        if (size <= 0 || size > MAX_SIZE)
        {
            printf("Invalid size\n");
            return 1;
        }

        rows1 = cols1 = rows2 = cols2 = size;

        generateRandomMatrix(matrix1, size);
        generateRandomMatrix(matrix2, size);

        writeMatrixToFile("matrix1.txt", matrix1, rows1, cols1);
        writeMatrixToFile("matrix2.txt", matrix2, rows2, cols2);

        printf("Generated matrices written to files matrix1.txt and matrix2.txt\n");
    }

    printf("Matrix 1:\n");
    printMatrix(matrix1, rows1, cols1);
    printf("\nMatrix 2:\n");
    printMatrix(matrix2, rows2, cols2);

    multiplyMatrices(result, matrix1, rows1, cols1, matrix2, rows2, cols2);

    printf("\nResult of Matrix Multiplication:\n");
    printMatrix(result, rows1, cols2);

    // Save result to matrix3.txt
    writeMatrixToFile("matrix3.txt", result, rows1, cols2);
    printf("Result of matrix multiplication written to matrix3.txt\n");

    return 0;
}
