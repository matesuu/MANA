#ifndef MANA_H
#define MANA_H

typedef struct matrix Matrix;

struct matrix* create_matrix();
void init_matrix(struct matrix* m, int r, int c);
struct matrix* row_mult(struct matrix* m, int row, float scalar);
struct matrix* row_swap(struct matrix* m, int row_o, int row_d);
struct matrix* row_add(struct matrix* m, int row_o, int row_d, float scalar);
struct matrix* add(struct matrix* one, struct matrix* two);
struct matrix* subtract(struct matrix* one, struct matrix* two);
struct matrix* multiply_scalar(struct matrix* one, int val);
struct matrix* multiply_matrix(struct matrix* one, struct matrix* two);
int determinant(struct matrix* m);
struct matrix* transpose(struct matrix* m);
void MtxNormalizeRow(struct matrix* m, int rix, int lead);
void MtxSwapRows(struct matrix* m, int row1, int row2);
void MtxMulAndAddRows(struct matrix* m, int dest_row, int src_row, float scalar);
void rref(struct matrix* m);
void visualize(struct matrix* m);



#endif
