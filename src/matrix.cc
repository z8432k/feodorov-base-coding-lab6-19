#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <iostream>

using namespace std;

void fail(const char* msg) {
  fprintf(stderr, "FAIL: %s\n", msg);
  exit(EXIT_FAILURE);
}

typedef struct {
  const gsize dim;
  float* data;
} Matrix_t;

typedef Matrix_t* Matrix;

Matrix allocMatrix(const gsize dim);
int inputMatrix(Matrix matrix);
void freeMatrix(Matrix matrix);
template <typename T>
static void inputValue(T *value, const char* errStr);

int main(void) {
  printf("= Two dimension matrix processing. =\n");

  Matrix matrix;

  inputMatrix(matrix);

  exit(EXIT_SUCCESS);
}

int inputMatrix(Matrix matrix) {
  gsize dim;

  cout << "Input matrix dimension: ";
  inputValue(&dim, "Wrong dimension value. Try again.");

  matrix = allocMatrix(dim);

  cout << "Input all matrix values in С style (by rows) one by one and press enter after each." << endl;

  gsize i = 0, j = 0, k = 0;
  do {
    cout << "Input cell ["<< i <<"][" << j << "]"<< endl;
    inputValue(&matrix->data[k], "Wrong matrix value. Try again.");

    if (j == matrix->dim - 1) {
      i++;
      j = 0;
    }
    else {
      j++;
    }

    k++;
  } while (k < matrix->dim * matrix->dim);

  return 0;
}

Matrix allocMatrix(const gsize dim) {
  Matrix matrix = g_new(Matrix_t, 1);
  float *data = g_new0(float, dim * dim);

  *(gsize *) &matrix->dim = dim;
  matrix->data = data;

  return matrix;
}

void freeMatrix(Matrix matrix) {
  g_free(matrix->data);
  g_free(matrix);
}

template <typename T>
static void inputValue(T *value, const char* errStr) {
  cin >> *value;

  while (!cin.good()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cerr << errStr;
    cin >> *value;
  }
}
