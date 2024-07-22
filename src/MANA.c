// MANA (Matrices and Numerical Algorithms) written by matesuu, 17 July, 2024
/*
This library provides an array of functionality revolving around matrix algebra for use in math and computer science. Designed for use primarily as a collection of tools for programmers using the C/C++, as well as for academic use via a calculator. Includes matrix initalization alongside elementary row operations, matrix multiplication, determinants, row echelon form, rank, and basic visualization.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "MANA.h"

#define MIN_SIZE 1
#define MAX_SIZE 12

typedef struct matrix // nice way to store matrix values
{
    int r_size, c_size; // row size and column size
    float** values; // 2d array to store values
} Matrix;

struct matrix* create_matrix()
{
    return malloc(sizeof(struct matrix)); // allocates memory for Matrix object
}

void init_matrix(struct matrix* m, int r, int c)
{
    if(r < MIN_SIZE && r > MAX_SIZE && c < MIN_SIZE && c > MAX_SIZE)
    {
        printf("ERROR: undefined input range"); // statement to check whether or not the arguments given for size are valid
                
        return ;
    }

    m->r_size = r; // sets size for rows
    m->c_size = c; // sets size for columns

    m->values = malloc(sizeof(float*) * m->r_size); // allocate memory for rows

    for(int i = 0; i < m->r_size; i++)
    {       
        m->values[i] = malloc(sizeof(float) * m->c_size); // allocate memory for columns
    }


    for(int i = 0; i < m->r_size; i++)
    {
        float f;
        
        for(int j = 0; j < m->c_size; j++)
        {
            printf("r");
            printf("%d", i + 1);
            printf("c");
            printf("%d", j + 1);
            printf(": ");

            scanf("%f", &f);
            
            m->values[i][j] = f;
        }
    }

    printf("\n");
}


struct matrix* row_mult(struct matrix* m, int row, float scalar)
{
    if(row - 1 < 0 || row - 1 > m->r_size - 1)
    {
        printf("ERROR: undefined input range"); // checks to see

        return NULL;
    }

    for(int i = 0; i < m->c_size; i++)
    {
        m->values[row - 1][i]*= scalar;
    }

    return m;
}

struct matrix* row_swap(struct matrix* m, int row_o, int row_d)
{
    if(row_o - 1 < 0 || row_o - 1 > m->r_size - 1 || row_d - 1 < 0 || row_d - 1 > m->r_size - 1 )
    {
        printf("ERROR: undefined input range"); // checks to see

        return NULL;
    }
        
    float* buffer = malloc(sizeof(float) * m->c_size);
    
    for(int i = 0; i < m->c_size; i++)
    {
        buffer[i] = m->values[row_o - 1][i];
        m->values[row_o - 1][i] = m->values[row_d - 1][i];
        m->values[row_d - 1][i] = buffer[i];
    }
    
    free(buffer);
    
    return m;
}

struct matrix* row_add(struct matrix* m, int row_o, int row_d, float scalar)
{
    if(row_o - 1 < 0 || row_o - 1 > m->r_size - 1 || row_d - 1 < 0 || row_d - 1 > m->r_size - 1 )
    {
        printf("ERROR: undefined input range"); // checks to see

        return NULL;
    }

    for (int i = 0; i < m->c_size; i++) 
    {
        m->values[row_d - 1][i] += scalar * m->values[row_o - 1][i];
    }

    return m;
}

struct matrix* add(struct matrix* one, struct matrix* two)
{
    if(one->r_size != two->r_size || one->c_size != two->c_size)
    {
        printf("ERROR: incompatible matrices");
                
        return NULL;
    }

    struct matrix* ans = create_matrix();
    ans->r_size = one->r_size;
    ans->c_size = two->c_size;

    ans->values = malloc(sizeof(float*) * ans->r_size);
    
    for(int i = 0; i < ans->r_size; i++)
    {
        ans->values[i] = malloc(sizeof(float) * ans->c_size);
    }

    for(int i = 0; i < ans->r_size; i++)
    {
        for(int j = 0; j < ans->c_size; j++)
        {
            ans->values[i][j] = one->values[i][j] + two->values[i][j];
        }
    }
        
    return ans;
}

struct matrix* subtract(struct matrix* one, struct matrix* two)
{
    if(one->r_size != two->r_size || one->c_size != two->c_size)
    {
        printf("ERROR: incompatible matrices");
                
        return NULL;
    }

    struct matrix* ans = create_matrix();
    ans->r_size = one->r_size;
    ans->c_size = two->c_size;

    ans->values = malloc(sizeof(float*) * ans->r_size);
    
    for(int i = 0; i < ans->r_size; i++)
    {
        ans->values[i] = malloc(sizeof(float) * ans->c_size);
    }

    for(int i = 0; i < ans->r_size; i++)
    {
        for(int j = 0; j < ans->c_size; j++)
        {
            ans->values[i][j] = one->values[i][j] - two->values[i][j];
        }
    }
        
    return ans;
}

struct matrix* multiply_scalar(struct matrix* one, int val)
{
    for(int i = 0; i < one->r_size; i++)
    {
        for(int j = 0; j < one->c_size; j++)
        {
            one->values[i][j] *= val;
        }
    }

    return one;
}

struct matrix* multiply_matrix(struct matrix* one, struct matrix* two)
{
    if(one->c_size != two->r_size)
    {
        printf("ERROR: incompatible matrices");
        
        return NULL;
    }
    
    struct matrix* ans = create_matrix();
    ans->r_size = one->r_size;
    ans->c_size = two->c_size;
    
    ans->values = malloc(sizeof(float*) * ans->r_size);
    
    for(int i = 0; i < ans->r_size; i++)
    {
        ans->values[i] = malloc(sizeof(float) * ans->c_size);
    }
    
    for(int i = 0; i < one->r_size; i++)
    {
        for(int j = 0; j < two->c_size; j++)
        {
            for(int k = 0; k < two->r_size; k++)
            {
                ans->values[i][j] += one->values[i][k] * two->values[k][j];
            }
        }
    }
    
    return ans;
}


int determinant(struct matrix* m)
{
    if (m->r_size != m->c_size)
    {
        printf("ERROR: determinant is only defined for square matrices");
        return 0;
    }

    int n = m->r_size; // n x n matrix

    
    if (n == 1)
    {
        return m->values[0][0];
    }

    
    if (n == 2)
    {
        return m->values[0][0] * m->values[1][1] - m->values[0][1] * m->values[1][0];
    }

    int det = 0;

    // Apply cofactor expansion along the first row
    for (int j = 0; j < n; j++)
    {
        
        struct matrix* submatrix = create_matrix();
        submatrix->r_size = n - 1;
        submatrix->c_size = n - 1;
        submatrix->values = malloc(sizeof(float*) * submatrix->r_size);

        for (int i = 0; i < submatrix->r_size; i++)
        {
            submatrix->values[i] = malloc(sizeof(float) * submatrix->c_size);
        }

        
        int sub_i = 0;
        
        for (int i = 1; i < n; i++)
        {
            int sub_j = 0;
            for (int k = 0; k < n; k++)
            {
                if (k == j)
                {
                    continue;
                }
                submatrix->values[sub_i][sub_j++] = m->values[i][k];
            }
            
            sub_i++;
        }

        
        int cofactor = (j % 2 == 0 ? 1 : -1) * m->values[0][j] * determinant(submatrix);
        det += cofactor;

        for (int i = 0; i < submatrix->r_size; i++)
        {
            free(submatrix->values[i]);
        }
        
        free(submatrix->values);
        free(submatrix);
    }

    return det;
}

struct matrix* transpose(struct matrix* m)
{
    struct matrix* buffer = create_matrix();
    
    buffer->r_size = m->c_size;
    buffer->c_size = m->r_size;
    
    
    buffer->values = malloc(sizeof(float*) * buffer->r_size);
    
    for (int i = 0; i < buffer->r_size; i++)
    {
        buffer->values[i] = malloc(sizeof(float) * buffer->c_size);
    }
    
    
    for (int i = 0; i < m->r_size; i++)
    {
        for (int j = 0; j < m->c_size; j++)
        {
            buffer->values[j][i] = m->values[i][j];
        }
    }
    
    // Update original matrix dimensions and values
    m->r_size = buffer->r_size;
    m->c_size = buffer->c_size;
    
    for (int i = 0; i < m->r_size; i++)
    {
        free(m->values[i]);
    }
    
    free(m->values);
    
    m->values = buffer->values;
    
    free(buffer);

    return m;
}

void MtxNormalizeRow(struct matrix* m, int rix, int lead) 
{
    float* drow = m->values[rix];
    float lv = drow[lead];

    for (int ix = 0; ix < m->c_size; ix++) 
    {
        drow[ix] /= lv;
    }

    // Print debug statement (optional)
    // printf("Normalize row %d\n", rix);
    // visualize(m);
}


void MtxSwapRows(struct matrix* m, int row1, int row2) 
{
    row_swap(m, row1 + 1, row2 + 1); // Adjusting for 1-based indexing in row_swap function
}


void MtxMulAndAddRows(struct matrix* m, int dest_row, int src_row, float scalar) 
{
    row_add(m, src_row + 1, dest_row + 1, scalar); // Adjusting for 1-based indexing in row_add function
}

void rref(struct matrix* m) 
{
    int lead = 0;
    int rowCount = m->r_size;
    int colCount = m->c_size;

    for (int rix = 0; rix < rowCount; rix++) 
    {
        if (lead >= colCount) 
        {
            return;
        }

        int iix = rix;
        
        while (m->values[iix][lead] == 0) 
        {
            iix++;
            
            if (iix == rowCount) 
            {
                iix = rix;
                lead++;
                
                if (lead == colCount) 
                {
                    return;
                }
            }
        }

        MtxSwapRows(m, iix, rix);
        MtxNormalizeRow(m, rix, lead);

        for (iix = 0; iix < rowCount; iix++) 
        {
            if (iix != rix) 
            {
                float lv = m->values[iix][lead];
                MtxMulAndAddRows(m, iix, rix, -lv);
            }
        }

        lead++;
    }
}

void visualize(struct matrix* m)
{
    printf("\n");
    
    for(int i = 0; i < m->r_size; i++)
    {
        printf("[");
                
        for(int j = 0; j < m->c_size; j++)
        {
            printf("%f", m->values[i][j]);
            
            if(j < m->c_size - 1)
            {
                printf(" ");
            }
        }

        printf("]\n");
    }

    printf("\n");
}