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
  const float* data;
} Matrix_t;

typedef Matrix_t* SMatrix;

int inputMatrix(float** matrix);
int allocMatrix(SMatrix* matrix, size_t dim);

int main(void) {
  printf("= Two dimension matrix processing. =\n");

  SMatrix matrix;

  allocMatrix(&matrix, 10);

  exit(EXIT_SUCCESS);
}


int allocMatrix(SMatrix* matrix_p, const size_t dim) {
  const SMatrix matrix = (SMatrix) malloc(sizeof(Matrix_t));
  const float *data = (float *) calloc(dim * dim, sizeof(float));

  if (matrix == NULL || data == NULL) {
    fail(strerror(errno));
  }

  *(size_t *) &matrix->dim = dim;
  matrix->data = data;

  return 0;
}
