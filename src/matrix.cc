#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void fail(const char* msg) {
  fprintf(stderr, "FAIL: %s\n", msg);
  exit(EXIT_FAILURE);
}

typedef struct {
  const size_t dim;
  float* data;
} Matrix_t;

typedef Matrix_t* SMatrix;

int inputMatrix(SMatrix matrix);
SMatrix allocMatrix(const size_t dim);
void freeMatrix(SMatrix matrix);

int main(void) {
  printf("= Two dimension matrix processing. =\n");

  SMatrix matrix = allocMatrix(10);

  if (matrix == NULL) {
    fail(strerror(errno));
  }

  exit(EXIT_SUCCESS);
}

int inputMatrix(SMatrix matrix) {
  return 0;
}

SMatrix allocMatrix(const size_t dim) {
  const SMatrix matrix = (SMatrix) malloc(sizeof(Matrix_t));
  float *data = (float *) calloc(dim * dim, sizeof(float));

  if (matrix == NULL || data == NULL) {
    return NULL;
  }

  *(size_t *) &matrix->dim = dim;
  matrix->data = data;

  return matrix;
}

void freeMatrix(SMatrix matrix) {
  free(matrix->data);
  free(matrix);
}
